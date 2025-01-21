/*
 * @Author: Li RF
 * @Date: 2024-03-12 15:26:10
 * @LastEditTime: 2024-03-14 15:57:44
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"


extern uint8_t count;
extern uint8_t tim_flag;
extern TIM_HandleTypeDef TIM3_Handler;

void TIM3_Init(u16 arr, u16 psc);




#endif



