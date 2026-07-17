#ifndef _KEY_H
#define _KEY_H
#include "main.h"
#include "gpio.h"
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
unsigned char KEY_GetVal(void);


#endif
