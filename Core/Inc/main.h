/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Bsp_usart.h"
#include "Bsp_pwm.h"
#include "Bsp_drv8302.h"
#include "Bsp_rgb.h"
#include "Bsp_5600.h"
#include "Bsp_5048a.h"
#include "Bsp_adc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENS3_Pin GPIO_PIN_0
#define SENS3_GPIO_Port GPIOA
#define SENS2_Pin GPIO_PIN_1
#define SENS2_GPIO_Port GPIOA
#define SENS1_Pin GPIO_PIN_2
#define SENS1_GPIO_Port GPIOA
#define AD_XN_Pin GPIO_PIN_3
#define AD_XN_GPIO_Port GPIOA
#define BR_SO1_Pin GPIO_PIN_4
#define BR_SO1_GPIO_Port GPIOA
#define BR_SO2_Pin GPIO_PIN_5
#define BR_SO2_GPIO_Port GPIOA
#define DRV8302_EN_GATE_Pin GPIO_PIN_15
#define DRV8302_EN_GATE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
