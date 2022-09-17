/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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
#define Display_CS_Pin GPIO_PIN_2
#define Display_CS_GPIO_Port GPIOA
#define Display_RS_Pin GPIO_PIN_3
#define Display_RS_GPIO_Port GPIOA
#define Display_WR_Pin GPIO_PIN_4
#define Display_WR_GPIO_Port GPIOA
#define Display_RST_Pin GPIO_PIN_5
#define Display_RST_GPIO_Port GPIOA
#define DATA_0_Pin GPIO_PIN_6
#define DATA_0_GPIO_Port GPIOA
#define DATA_1_Pin GPIO_PIN_7
#define DATA_1_GPIO_Port GPIOA
#define DATA_2_Pin GPIO_PIN_0
#define DATA_2_GPIO_Port GPIOB
#define DATA_3_Pin GPIO_PIN_1
#define DATA_3_GPIO_Port GPIOB
#define DATA_4_Pin GPIO_PIN_2
#define DATA_4_GPIO_Port GPIOB
#define DATA_5_Pin GPIO_PIN_10
#define DATA_5_GPIO_Port GPIOB
#define DATA_6_Pin GPIO_PIN_11
#define DATA_6_GPIO_Port GPIOB
#define DATA_7_Pin GPIO_PIN_12
#define DATA_7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
