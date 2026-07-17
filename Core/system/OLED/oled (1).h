#ifndef _OLED_H
#define _OLED_H
#include "main.h"
#define OLED_DAT 1 //高电平发送数据
#define OLED_CMD 0 //低电平发送命令
#define OLED_SCK(x) HAL_GPIO_WritePin(OLED_SCK_GPIO_Port,OLED_SCK_Pin,(GPIO_PinState )x)//时钟
#define OLED_MOSI(x) HAL_GPIO_WritePin(OLED_MOSI_GPIO_Port,OLED_MOSI_Pin,(GPIO_PinState )x)//数据线 
#define OLED_RES(x) HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin,(GPIO_PinState )x)//复位
#define OLED_DC(x) HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,(GPIO_PinState )x)//数据命令选择线
#define OLED_CS(x) HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,(GPIO_PinState )x)//片选

extern const char android[];//android
extern const char wbyq_logo[];//wbyq_logo
extern const u8 font_24_24[][24*24/8];//24*24汉字
extern const u8 font_32_32[][32*32/8];//32*32汉字
extern const u8 ASCII_8_16[][16];//8*16 ASCII
extern const u8 ASCII_12_24[][36];//12*24 ASCII
extern const char bmp1[];
extern const char basketball[];
extern const u8 font_16_16[][16*16/8];

void OLED_Init(void);//OLED初始化
void OLED_Clear(void);//清屏函数
void OLED_Refresh_Gram(void);//更新显示
void OLED_Display_font(u8 x,u8 y,u8 size,u8 number);//显示汉字
void OLED_Display_char(u8 x,u8 y,u8 w,u8 h,u8 chr);//显示字符
void OLED_Display_str(u8 x,u8 y,u8 w,u8 h,u8 *str);//显示字符串
void OLED_Displey_Imag(u8 x,u8 y,u8 w,u8 h,u8 *imag);//显示图片

#endif
