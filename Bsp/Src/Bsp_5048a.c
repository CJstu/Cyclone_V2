//
// Created by 25230 on 24-8-18.
//
#include "Bsp_5048a.h"

uint32_t Capture_Raise[IC_BufSize] = {0x00000000};  //CH1的DMA缓冲区，用于存放上升沿捕获数据
uint32_t Capture_Fall[IC_BufSize] = {0x00000000};   //CH2的DMA缓冲区，用于存放下降沿捕获数据

uint32_t Avg_Raise = 0x00000000;
uint32_t Avg_Fall = 0x00000000;

float Freq_Capture_Freq = 0.0;  //所测信号频率
float Freq_Capture_Duty = 0.0;  //所测信号占空比

float motorAbsAngle = 0.0;

void Freq_Meter_Init(void)
{
    //开始TIM2CH1的DMA传输
    HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, Capture_Raise, IC_BufSize);
    //还原TIM2状态，然后开始TIM2CH2的DMA传输
    htim2.State = HAL_TIM_STATE_READY;
    HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, Capture_Fall, IC_BufSize);
}

void Freq_Meter_DeInit(void)
{
    HAL_TIM_IC_Stop_DMA(&htim2, TIM_CHANNEL_1);
    HAL_TIM_IC_Stop_DMA(&htim2, TIM_CHANNEL_2);
}

void Freq_Calc(void)
{
    Avg_Raise = 0;
    Avg_Fall = 0;

    //取平均值
    for(uint16_t i = 0; i < IC_BufSize; i++)
    {
        Avg_Raise += Capture_Raise[i];
        Avg_Fall += Capture_Fall[i];
    }
    Avg_Raise /= IC_BufSize;
    Avg_Fall /= IC_BufSize;

    //计算频率及占空比
    if(Avg_Raise != 0)
    {
        Freq_Capture_Freq = (float)TIM2_Clock / (float)((TIM2_PSC + 1) * Avg_Raise);
        Freq_Capture_Duty = (float)Avg_Fall / (float)Avg_Raise;
    }
}

float get_angle(void)
{
    Freq_Calc();
    motorAbsAngle = 360.0/(4095.0/4119.0)*Freq_Capture_Duty;
    if (motorAbsAngle >= 360.0)
    {
        motorAbsAngle = 360.0;
    } else if (motorAbsAngle <= 0.0)
    {
        motorAbsAngle = 0.0;
    }
    return motorAbsAngle;
}