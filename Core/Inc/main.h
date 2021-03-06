/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define RELAY_2_Pin GPIO_PIN_0
#define RELAY_2_GPIO_Port GPIOF
#define RELAY_1_Pin GPIO_PIN_1
#define RELAY_1_GPIO_Port GPIOF
#define VR1_Pin GPIO_PIN_0
#define VR1_GPIO_Port GPIOA
#define VR2_Pin GPIO_PIN_1
#define VR2_GPIO_Port GPIOA
#define VR3_Pin GPIO_PIN_2
#define VR3_GPIO_Port GPIOA
#define H9_LED_Pin GPIO_PIN_3
#define H9_LED_GPIO_Port GPIOA
#define H8_Alarm_LED_Pin GPIO_PIN_4
#define H8_Alarm_LED_GPIO_Port GPIOA
#define H8_Sync_Pin GPIO_PIN_5
#define H8_Sync_GPIO_Port GPIOA
#define H2_Pin GPIO_PIN_6
#define H2_GPIO_Port GPIOA
#define H1_Pin GPIO_PIN_7
#define H1_GPIO_Port GPIOA
#define RELAY_5_Pin GPIO_PIN_1
#define RELAY_5_GPIO_Port GPIOB
#define RELAY_4_Pin GPIO_PIN_9
#define RELAY_4_GPIO_Port GPIOA
#define RELAY_3_Pin GPIO_PIN_10
#define RELAY_3_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
