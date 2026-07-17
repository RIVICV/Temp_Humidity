/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
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
#define DHT11_Pin GPIO_PIN_0
#define DHT11_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_10
#define OLED_CS_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_11
#define OLED_DC_GPIO_Port GPIOB
#define OLED_RST_Pin GPIO_PIN_12
#define OLED_RST_GPIO_Port GPIOB
#define OLED_SCK_Pin GPIO_PIN_13
#define OLED_SCK_GPIO_Port GPIOB
#define OLED_MOSI_Pin GPIO_PIN_14
#define OLED_MOSI_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOA
#define IIC_SCL_Pin GPIO_PIN_6
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_7
#define IIC_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
