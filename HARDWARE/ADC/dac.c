/*
 * @Author: Li RF
 * @Date: 2024-03-14 09:45:09
 * @LastEditTime: 2024-03-14 10:14:06
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#include "dac.h"


DAC_HandleTypeDef DAC1_Handler;//DAC句柄

/**
 * @brief	初始化DAC
 *
 * @param   void
 *
 * @return  void
 */
void DAC_Init(void)
{
    DAC_ChannelConfTypeDef DACCH1_Config;
    
    DAC1_Handler.Instance=DAC;
    HAL_DAC_Init(&DAC1_Handler); 	//初始化DAC
    
    DACCH1_Config.DAC_Trigger=DAC_TRIGGER_NONE;             			//不使用触发功能
    DACCH1_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_DISABLE;			//DAC1输出缓冲关闭
	DACCH1_Config.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;		//DAC模式
	DACCH1_Config.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;//不连接到片内外设
    HAL_DAC_ConfigChannel(&DAC1_Handler, &DACCH1_Config, DAC_CHANNEL_1);//DAC通道1配置
    
    HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_1);  //开启DAC通道1
}


/**
 * @brief	DAC底层驱动，时钟配置，引脚 配置，此函数会被HAL_DAC_Init()调用
 *
 * @param   hdac	DAC句柄
 *
 * @return  void
 */
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
    GPIO_InitTypeDef GPIO_Initure;
	
    __HAL_RCC_DAC1_CLK_ENABLE();             //使能DAC时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_4;            //PA4
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //模拟
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}

/**
 * @brief	设置通道1输出电压
 *
 * @param   vol		0~3300,代表0~3.3V
 *
 * @return  void
 */
void DAC_Set_Vol(u16 vol)
{
	double temp = vol;
	temp *= (4096.0 / 3300.0);
    HAL_DAC_SetValue(&DAC1_Handler, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp);//12位右对齐数据格式设置DAC值
}
