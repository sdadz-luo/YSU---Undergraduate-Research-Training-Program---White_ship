/*
 * ws2812.h
 *
 *  Created on: 2023年10月31日
 *      Author: Administrator
 */

#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>

//            编码 0 : 11000000
#define CODE_0      0xc0
//            编码 1 : 11111000
#define CODE_1      0xF8
/*ws2812b灯珠数量*/
#define WS2812B_AMOUNT    80

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} tWs2812bCache_TypeDef;

extern tWs2812bCache_TypeDef gWs2812bDat[WS2812B_AMOUNT];

void WS2812b_Set(uint16_t Ws2b812b_NUM, uint8_t r,uint8_t g,uint8_t b);
void WS2812B_Task(void);

// 整串统一单色函数
void WS2812_AllRed(void);
void WS2812_AllCyan(void);
void WS2812_AllPurple(void);
void WS2812_AllGreen(void);
void WS2812_AllWhite(void);
void WS2812_StaticMultiColor(void);
void WS2812_AllOff(void);
#endif /* WS2812_H_ */
