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
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuf, 4);
}

void Bsp_Adc_get_ADC(uint8_t AD_num)
{
    // if ( AD_num <3) {
    //     Volt[AD_num]=((adcBuf[AD_num]*3.3)/4096.0)*41.2/2.2;
    // }
    // else {
    //     Volt[AD_num]=(adcBuf[AD_num]*3.3)/4096.0;
    // }
    Volt[AD_num]=(adcBuf[AD_num]*3.3)/4096.0;
    Printf(USART1,"ADC_IN%d, val:%d, Volt:%.2f\r\n",AD_num,adcBuf[AD_num],Volt[AD_num]);
}


// void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
// {
//     /*定时器DMA启动多通道转换*/
//     uint32_t val=0;
//     float Volt=0.0;
//     for(uint8_t i=0;i<BATCH_DATA_LEN;i++)
//     {
//         val=adcBuf[i];
//         Volt=((val*3.3)/4096.0)*41.2/2.2;
//         Printf(USART1,"ADC_IN%d, val:%d, Volt:%f\r\n",i,val,Volt);
//     }
// }
