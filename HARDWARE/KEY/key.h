/*
 * @Author: Li RF
 * @Date: 2024-03-12 15:26:10
 * @LastEditTime: 2024-03-14 10:34:24
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#ifndef _KEY_H
#define _KEY_H
#include "sys.h"


/*
	KEY0 	- PD10
	KEY1 	- PD9
	KEY2 	- PD8
	WK_UP 	- PC13
*/
#define KEY0        HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_10)
#define KEY1        HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_9)
#define KEY2        HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)
#define WK_UP       HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)

#define KEY0_PRES 		1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define WKUP_PRES   	4

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
