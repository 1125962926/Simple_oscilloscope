/*
 * @Author: Li RF
 * @Date: 2024-03-12 15:26:10
 * @LastEditTime: 2024-03-15 13:06:03
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#include "timer.h"
#include "led.h"
#include "adc.h"

uint8_t count;//采集的数据个数
uint8_t tim_flag;//定时器计时

TIM_HandleTypeDef TIM3_Handler;      //定时器句柄


/**
 * @brief	通用定时器3中断初始化函数
 *			定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
 *			Ft=定时器工作频率,单位:Mhz
 *			这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK:80Mhz)
 *
 * @param   arr		自动重装值。
 * @param   psc		时钟预分频数
 *
 * @return  void
 */
void TIM3_Init(u16 arr, u16 psc)
{
    TIM3_Handler.Instance = TIM3;                          	//通用定时器3
    TIM3_Handler.Init.Prescaler = psc;                     	//分频系数
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;    	//向上计数器
    TIM3_Handler.Init.Period = arr;                        	//自动装载值
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);

    HAL_TIM_Base_Start_IT(&TIM3_Handler);					//使能定时器3和定时器3更新中断：TIM_IT_UPDATE
}


/**
 * @brief	定时器底册驱动，开启时钟，设置中断优先级
 *			此函数会被HAL_TIM_Base_Init()函数调用
 *
 * @param   htim	定时器句柄
 *
 * @return  void
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3);  //设置中断优先级，抢占优先级1，子优先级3
        HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断
    }
}

/**
 * @brief	定时器3中断服务函数
 *
 * @param   void
 *
 * @return  void
 */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

/**
 * @brief	回调函数，定时器中断服务函数调用
 *
 * @param   htim	定时器句柄
 *
 * @return  void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == (&TIM3_Handler))
    {
        count++;
        tim_flag = 1;
    }
}
