//
// Created by 25230 on 24-8-19.
//
#include "Bsp_adc.h"
#include "adc.h"

#define BATCH_DATA_LEN 4
#define FILTER_SIZE 10

uint16_t adcBuf[BATCH_DATA_LEN];
float Volt[BATCH_DATA_LEN];

void Bsp_Adc_Init(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuf, BATCH_DATA_LEN);
}

void Bsp_Adc_get_ADC(uint8_t AD_num)
{
    if (AD_num == 0) {
        Volt[AD_num]=(adcBuf[AD_num]*3.3)/4096.0;
    }else if (AD_num == 3) {
        Volt[AD_num] = (((adcBuf[AD_num]*3.3)/4096.0) - 0.76)/0.0025 + 25;	//根据公式算出温度值
    }else {
        Volt[AD_num]=(adcBuf[AD_num]*3.3)/4096.0;
    }
}

float Bsp_getTemp(void)
{
    Bsp_Adc_get_ADC(3);
    return Volt[3];
}

