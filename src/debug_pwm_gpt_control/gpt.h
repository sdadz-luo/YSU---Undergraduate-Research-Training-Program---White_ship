#ifndef GPT_H_
#define GPT_H_

#include "headfile.h"

/** 运动方向枚举 */
typedef enum {
    MOVE_STOP      = 0,  // 停止
    MOVE_FORWARD   = 2,  // 前进
    MOVE_LEFT      = 4,  // 左转
    MOVE_BACKWARD  = 1,  // 后退
    MOVE_RIGHT     = 3,  // 右转
} move_direction_t;

void gpt0_init(void);
void time0_callback(timer_callback_args_t *p_args);

#endif