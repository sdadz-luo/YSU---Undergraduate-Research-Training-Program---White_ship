#include "ds18b20.h"
#include "hal_data.h"
#include <stdio.h>

/************************ 硬件引脚定义 ************************/
#define DS18B20_DQ_PIN    BSP_IO_PORT_00_PIN_01

/************************ DS18B20命令宏（和参考完全一致） ************************/
#define SKIP_ROM            0xCC
#define CONVERT_T           0x44
#define READ_SCRATCHPAD     0xBE

/************************ 底层GPIO操作（对齐参考IODrv驱动逻辑） ************************/
// 设置DQ引脚电平（自动切换为输出模式）
static void dq_write(unsigned char level)
{
    g_ioport.p_api->pinCfg(g_ioport.p_ctrl, DS18B20_DQ_PIN, IOPORT_CFG_PORT_DIRECTION_OUTPUT);
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, DS18B20_DQ_PIN, (bsp_io_level_t)level);
}

// 读取DQ引脚电平（自动切换为输入模式）
static unsigned char dq_read(void)
{
    bsp_io_level_t level;
    g_ioport.p_api->pinCfg(g_ioport.p_ctrl, DS18B20_DQ_PIN, IOPORT_CFG_PORT_DIRECTION_INPUT);
    g_ioport.p_api->pinRead(g_ioport.p_ctrl, DS18B20_DQ_PIN, &level);
    return (unsigned char)level;
}

/************************ 内部时序函数（和参考1:1一致） ************************/
// 发送复位脉冲
static void reset_pulse(void)
{
    dq_write(1);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
    dq_write(0);  // 主机拉低480us~960us
    R_BSP_SoftwareDelay(480, BSP_DELAY_UNITS_MICROSECONDS);
    dq_write(1);  // 释放总线等待应答
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
}

// 等待DS18B20存在应答脉冲
static int wait_presence(void)
{
    unsigned int time_out = 100;

    // 等待器件拉低总线
    time_out = 100;
    while((dq_read() == 1) && (time_out != 0))
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
        time_out--;
    }
    if(time_out == 0) return -1;

    // 等待器件释放总线
    time_out = 100;
    while((dq_read() == 0) && (time_out != 0))
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
        time_out--;
    }
    if(time_out == 0) return -1;

    return 0;
}

// 完整复位流程
static int ds18b20_reset(void)
{
    reset_pulse();
    if(wait_presence() != 0)
    {
        return -1;
    }
    return 0;
}

// 写入1个字节
static void write_byte(unsigned char cmd)
{
    for(unsigned char i = 0; i < 8; i++)
    {
        if((cmd & 0x01) == 0x01)   // 写1时序
        {
            dq_write(0);
            R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
            dq_write(1);
            R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
        }
        else    // 写0时序
        {
            dq_write(0);
            R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
            dq_write(1);
            R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
        }
        cmd = cmd >> 1;
    }
}

// 读取1个字节
static unsigned char read_byte(void)
{
    unsigned char tmp = 0;
    unsigned char time_out = 100;

    for(unsigned char i = 0; i < 8; i++)
    {
        dq_write(1);
        if(dq_read() == 0)
        {
            tmp = (tmp >> 1);
            time_out = 100;
            while((dq_read() == 0) && (time_out != 0))
            {
                R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
                time_out--;
            }
            if(time_out == 0) return 0xFF;
            R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
        }
        else
        {
            tmp = (tmp >> 1) | 0x80;
            R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
        }
    }
    return tmp;
}

/************************ 对外接口函数 ************************/
int ds18b20_init(void)
{
    // 初始化IOPORT外设（若工程已全局初始化可注释此行）
    fsp_err_t err = g_ioport.p_api->open(g_ioport.p_ctrl, g_ioport.p_cfg);
    if(FSP_SUCCESS != err)
    {
        printf("IOPORT init failed!\r\n");
        return -1;
    }

    // 总线初始状态拉高释放
    dq_write(1);

    // 复位测试，确认器件存在
    if(ds18b20_reset() != 0)
    {
        printf("DS18B20 not found!\r\n");
        return -1;
    }

    printf("DS18B20 init success\r\n");
    return 0;
}

float ds18b20_read_temp(void)
{
    unsigned char temp_l = 0, temp_h = 0;
    unsigned short temp_raw = 0;

    // 复位 + 启动温度转换
    if(ds18b20_reset() != 0)
    {
        return -999.0f;
    }
    write_byte(SKIP_ROM);
    write_byte(CONVERT_T);

    // 复位 + 读取温度暂存器
    if(ds18b20_reset() != 0)
    {
        return -999.0f;
    }
    write_byte(SKIP_ROM);
    write_byte(READ_SCRATCHPAD);
    temp_l = read_byte();
    temp_h = read_byte();
    temp_raw = (unsigned short)((temp_h << 8) | temp_l);

    // 温度计算（和参考代码逻辑完全一致）
    float temp_inter = 0, temp_dec = 0, temp_result = 0;
    temp_dec = (float)((temp_raw & 0xFF) * 0.0625);
    temp_inter = (temp_raw >> 4) & 0x7F;
    temp_result = temp_inter + temp_dec;

    // 负温处理（和参考代码逻辑完全一致）
    if(((temp_raw >> 12) & 0xF) == 0xF)
    {
        temp_result = -temp_result;
    }

    return temp_result;
}