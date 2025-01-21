/*
 * @Author: Li RF
 * @Date: 2024-03-14 09:45:23
 * @LastEditTime: 2024-03-14 09:46:59
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#ifndef __DAC_H
#define __DAC_H
#include "sys.h"


extern DAC_HandleTypeDef DAC1_Handler;

void DAC_Init(void);
void DAC_Set_Vol(u16 vol);



#endif


