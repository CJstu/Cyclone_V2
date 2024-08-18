//
// Created by 25230 on 24-8-19.
//
#include "Bsp_adc.h"
#include "adc.h"

uint16_t adcBuf[6];

void Bsp_Adc_Init(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuf, 6);
}
