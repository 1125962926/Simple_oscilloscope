/*
 * @Author: Li RF
 * @Date: 2024-03-12 15:26:10
 * @LastEditTime: 2024-03-14 17:26:10
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2024 by Li RF, All Rights Reserved. 
 */
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "adc.h"
#include "dac.h"
#include "timer.h"


int main(void)
{

    HAL_Init();
    SystemClock_Config();		//初始化系统时钟为80M
    delay_init(80); 			//初始化延时函数    80M系统时钟
    uart_init(115200);			//初始化串口，波特率为115200
    
    TIM3_Init(10 - 1, 80 - 1);//定时器3初始化 10us

    LED_Init();					//初始化LED
    LCD_Init();					//初始化LCD
    KEY_Init();					//初始化按键

    ADC_Init();				//初始化ADC1通道3
  
    Display_Voltage_Net();	

    float D_arr[LCD_Width];//存放D 电压数据的数组
    float max, min;	//电压量的最大值，最小值，最大最小的差值


    while(1)
    {   
        if(tim_flag == 1)//如果被中断 则记录一次数据
		{
			tim_flag = 0;
            D_arr[count] = Get_Adc();
        }

        if(count >= LCD_Width - 10)//如果显示的个数达到要求
        {
            HAL_TIM_Base_Stop_IT(&TIM3_Handler);//定时器暂时关闭，先处理数据
            Display_Voltage_Net();	

            max = D_arr[0] * 3300 / 4096;
            min = D_arr[0] * 3300 / 4096;
            for(count = 0; count < LCD_Width - 10; count++)//进行最大值和最小值等处理
			{
                D_arr[count] = D_arr[count] * 3300 / 4096;//模拟量换成数字量电压，1mV为量度 
				if(D_arr[count] > max)
                {
                    max = D_arr[count];
                }
				if(D_arr[count] < min)
                {
                    min = D_arr[count];
                }
			}

            //最大值和最小值显示
			POINT_COLOR = BLACK;//设置画笔为黑色
			LCD_ShowString(0, 15, 20, 12, 12, "max");
			LCD_ShowNum(0, 27, max, 4, 12);
			LCD_ShowString(0, LCD_Height - 30 - 12, 20, 12, 12, "min");
			LCD_ShowNum(0, LCD_Height - 30, min, 4, 12);

            //显示处理
			for(count = 0; count < LCD_Width - 10; count++)
			{
				D_arr[count] = D_arr[count] / 3300 * (LCD_Height - 20);//显示范围
			}
			
			//数据显示在LCD上
			for(count = 10; count < LCD_Width - 11; count++)
			{
				LCD_DrawLine(count, LCD_Height - 10 - D_arr[count], count + 1, LCD_Height - 10 - D_arr[count + 1]);
			}
			count = 0;//重新进行数据获取
            delay_ms(1000);
			HAL_TIM_Base_Start_IT(&TIM3_Handler);//定时器重新启动
        }
        





    }
}
 
