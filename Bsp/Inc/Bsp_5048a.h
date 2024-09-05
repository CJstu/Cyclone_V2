//
// Created by 25230 on 24-8-18.
//

#ifndef BSP_5048A_H
#define BSP_5048A_H
#include "main.h"
#include "tim.h"

#define TIM2_Clock  100000000
#define TIM2_PSC    10 - 1
#define TIM2_ARR    0xFFFFFFFF

#define IC_BufSize  32          //DMA缓冲区大小

extern float Freq_Capture_Freq;
extern float Freq_Capture_Duty;

extern float motorAbsAngle;

void Freq_Meter_Init(void);
void Freq_Meter_DeInit(void);
void Freq_Calc(void);
float get_angle(void);

#endif //BSP_5048A_H
