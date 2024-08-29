//
// Created by 25230 on 24-8-19.
//

#ifndef BSP_ADC_H
#define BSP_ADC_H
#include "main.h"

extern uint16_t adcBuf[];

void Bsp_Adc_Init(void);
void Bsp_Adc_get_ADC(uint8_t AD_num);
#endif //BSP_ADC_H
