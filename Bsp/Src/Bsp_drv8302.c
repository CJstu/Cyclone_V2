//
// Created by 25230 on 24-8-16.
//
#include "Bsp_drv8302.h"
#include "tim.h"

void Bsp_Drv8302_Init(void)
{
    HAL_GPIO_WritePin(DRV8302_EN_GATE_GPIO_Port, DRV8302_EN_GATE_Pin, GPIO_PIN_SET);
}