/*
 * @Author: Li RF
 * @Date: 2024-03-12 15:26:10
 * @LastEditTime: 2024-03-13 15:04:28
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#ifndef __ADC_H
#define __ADC_H
#include "sys.h"


void ADC_Init(void); 			
u16  Get_Adc(void); 		      
u16 Get_Adc_Average(u8 times);

#endif






