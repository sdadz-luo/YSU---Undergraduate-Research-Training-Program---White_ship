#ifndef __DS18B20_H
#define __DS18B20_H

/* 
 * DS18B20初始化
 * 返回值：0 = 成功，-1 = 失败
 * DQ引脚：BSP_IO_PORT_04_PIN_06 (P406)
 */
int ds18b20_init(void);

/* 
 * 读取温度值
 * 返回值：正常返回实际温度（单位℃），读取失败返回 -999.0f
 */
float ds18b20_read_temp(void);

#endif