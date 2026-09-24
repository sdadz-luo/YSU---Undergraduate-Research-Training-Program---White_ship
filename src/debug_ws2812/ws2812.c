/*
 * ws2812.c
 *
 *  Created on: 2023年10月31日
 *      Author: Administrator
 */

#include "ws2812.h"
#include "hal_data.h"
extern fsp_err_t err ;
extern volatile bool g_transfer_complete ;
////p411
//灯条显存SPI数据缓存
uint8_t gWs2812bDat_SPI[WS2812B_AMOUNT * 24+88] = {0};
//灯条显存
tWs2812bCache_TypeDef gWs2812bDat[WS2812B_AMOUNT] = {

//R    G      B
0XFF, 0X00, 0X00,   //0
0X00, 0XFF, 0X00,   //1
0X00, 0X00, 0XFF,   //2
0X00, 0XFF, 0XFF,   //3
0XFF, 0X00, 0XFF,   //4
0XFF, 0XFF, 0X00,   //5
0XFF, 0XFF, 0XFF,   //6
0X00, 0X00, 0X00,   //7
};

void WS2812b_Set(uint16_t Ws2b812b_NUM, uint8_t r,uint8_t g,uint8_t b)
{
    uint8_t *pR = &gWs2812bDat_SPI[88+(Ws2b812b_NUM) * 24 + 8];
    uint8_t *pG = &gWs2812bDat_SPI[88+(Ws2b812b_NUM) * 24];
    uint8_t *pB = &gWs2812bDat_SPI[88+(Ws2b812b_NUM) * 24 + 16];

    for(uint8_t i = 0; i <  8; i++) {
        if(g & 0x80) {
            *pG = CODE_1;
        }
        else {
            *pG = CODE_0;
        }
        if(r & 0x80) {
            *pR = CODE_1;
        }
        else {
            *pR = CODE_0;
        }
        if(b & 0x80) {
            *pB = CODE_1;
        }
        else {
            *pB = CODE_0;
        }
        r <<= 1;
        g <<= 1;
        b <<= 1;
        pR++;
        pG++;
        pB++;
    }
}

void WS2812B_Task(void)
{
    //清空复位区88字节
    for(int i=0;i<88;i++)
    {
        gWs2812bDat_SPI[i]=0;
    }
    //将gWs2812bDat显存数据解析成SPI编码
    for(uint8_t iLED = 0; iLED < WS2812B_AMOUNT; iLED++)
    {
        WS2812b_Set(iLED, gWs2812bDat[iLED].R, gWs2812bDat[iLED].G, gWs2812bDat[iLED].B);
    }

   
    err = R_SCI_SPI_Write(&g_spi0_ctrl, gWs2812bDat_SPI, sizeof(gWs2812bDat_SPI), SPI_BIT_WIDTH_8_BITS);
    assert(FSP_SUCCESS == err);
    R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MILLISECONDS);
}

// 全部红色
void WS2812_AllRed(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        gWs2812bDat[i].R = 255;
        gWs2812bDat[i].G = 0;
        gWs2812bDat[i].B = 0;
        WS2812b_Set(i, 255, 0, 0);
    }
    WS2812B_Task();
}

// 全部青色
void WS2812_AllCyan(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        gWs2812bDat[i].R = 0;
        gWs2812bDat[i].G = 255;
        gWs2812bDat[i].B = 255;
        WS2812b_Set(i, 0, 255, 255);
    }
    WS2812B_Task();
}

// 全部紫色
void WS2812_AllPurple(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        gWs2812bDat[i].R = 255;
        gWs2812bDat[i].G = 0;
        gWs2812bDat[i].B = 255;
        WS2812b_Set(i, 255, 0, 255);
    }
    WS2812B_Task();
}

// 全部绿色
void WS2812_AllGreen(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        gWs2812bDat[i].R = 0;
        gWs2812bDat[i].G = 255;
        gWs2812bDat[i].B = 0;
        WS2812b_Set(i, 0, 255, 0);
    }
    WS2812B_Task();
}

// 全部白色
void WS2812_AllWhite(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        gWs2812bDat[i].R = 255;
        gWs2812bDat[i].G = 255;
        gWs2812bDat[i].B = 255;
        WS2812b_Set(i, 255, 255, 255);
    }
    WS2812B_Task();
}

void WS2812_StaticMultiColor(void)
{
    // 定义5种颜色：红、青、紫、绿、白
    uint8_t color_table[][3] = {
        {255, 0, 0},    // 红
        {0, 255, 255},  // 青
        {255, 0, 255},  // 紫
        {0, 255, 0},    // 绿
        {255, 255, 255} // 白
    };
    uint8_t color_num = sizeof(color_table) / sizeof(color_table[0]);

    // 遍历所有灯，循环分配颜色
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        uint8_t idx = i % color_num;
        uint8_t r = color_table[idx][0];
        uint8_t g = color_table[idx][1];
        uint8_t b = color_table[idx][2];

        // 同步更新显存数组，保证后续操作兼容
        gWs2812bDat[i].R = r;
        gWs2812bDat[i].G = g;
        gWs2812bDat[i].B = b;
        WS2812b_Set(i, r, g, b);
    }
    // 一次性刷新点亮
    WS2812B_Task();
}
void WS2812_AllOff(void)
{
    for(uint8_t i = 0; i < WS2812B_AMOUNT; i++)
    {
        // 显存清零
        gWs2812bDat[i].R = 0;
        gWs2812bDat[i].G = 0;
        gWs2812bDat[i].B = 0;
        // SPI编码缓存清零
        WS2812b_Set(i, 0, 0, 0);
    }
    // 刷新发送，真正熄灭
    WS2812B_Task();
}
extern tWs2812bCache_TypeDef gWs2812b;