#include "oled.h"
/*******************OLED屏发送1byte数据**************
**形参：u8 data,-- 数据
**			u8 cmd -- 0写命令，1写数据
**
******************************************************/
void OLED_SPI_ReadWriteOneByte(u8 data,u8 cmd)
{
	u8 i;
	if(cmd) OLED_DC(1);
	else OLED_DC(0);
	OLED_CS(0);//片选拉低，选择OLED屏
	OLED_SCK(0);
	for(i=0;i<8;i++)
	{
		OLED_SCK(0);
		if(data&0x80)OLED_MOSI(1);
		else OLED_MOSI(0);
		OLED_SCK(1);
		data<<=1;
	}
	OLED_CS(1);
	OLED_SCK(0);
}
/*OLED初始化*/
void OLED_Init(void)
{
	OLED_RES(1);
	HAL_Delay(100);
	OLED_RES(0);
	HAL_Delay(100);
	OLED_RES(1);
	HAL_Delay(100);
	OLED_SPI_ReadWriteOneByte(0xAE,OLED_CMD); //关闭显示

	OLED_SPI_ReadWriteOneByte(0x40,OLED_CMD);//设置屏幕起始行 (0x40-0x7F)，0x40对应第0行
	OLED_SPI_ReadWriteOneByte(0xB0,OLED_CMD);//设置页地址（Page 0）

	OLED_SPI_ReadWriteOneByte(0xC8,OLED_CMD);//0xc0上下反置 0xc8正常,此指令会立即生效

	OLED_SPI_ReadWriteOneByte(0x81,OLED_CMD);//设置对比度
	OLED_SPI_ReadWriteOneByte(0xff,OLED_CMD);//从0x00至0xFF,值设置得越大屏幕越亮

	OLED_SPI_ReadWriteOneByte(0xa1,OLED_CMD);//段重定向设置,0xa0左右反置 0xa1正常

	OLED_SPI_ReadWriteOneByte(0xa6,OLED_CMD);//此命令用于设置显示是否反转,0xa6,RAM中的数据1表示点亮像素;0xa7,RAM中的数据0表示点亮像素
	
	OLED_SPI_ReadWriteOneByte(0xa8,OLED_CMD);//设置复用率
	OLED_SPI_ReadWriteOneByte(0x1f,OLED_CMD);//该设置适用于 128×32 的 OLED 显示屏
	
	OLED_SPI_ReadWriteOneByte(0xd3,OLED_CMD);//设置显示偏移
	OLED_SPI_ReadWriteOneByte(0x00,OLED_CMD);//不偏移
	
	OLED_SPI_ReadWriteOneByte(0xd5,OLED_CMD);//设置显示时钟分频值(A[3:0]),即设置从CLK分频得到的DCLK(显示时钟)的分频值/震荡频率(A[7:4])
	OLED_SPI_ReadWriteOneByte(0xf0,OLED_CMD);//分频比为1，振荡频率最高
	
	OLED_SPI_ReadWriteOneByte(0xd9,OLED_CMD);//设置预充电周期的时长，此周期单位为一DCLK的周期，复位值为2 DCLK
	OLED_SPI_ReadWriteOneByte(0x22,OLED_CMD);
	
	OLED_SPI_ReadWriteOneByte(0xda,OLED_CMD);//设置列引脚硬件配置
	OLED_SPI_ReadWriteOneByte(0x02,OLED_CMD);
	
	OLED_SPI_ReadWriteOneByte(0xdb,OLED_CMD);//设置VCOMH反压值
	OLED_SPI_ReadWriteOneByte(0x49,OLED_CMD);
	
	OLED_SPI_ReadWriteOneByte(0x8d,OLED_CMD);//电荷泵设置
	OLED_SPI_ReadWriteOneByte(0x14,OLED_CMD);//启用电荷泵

	OLED_SPI_ReadWriteOneByte(0xAF,OLED_CMD); //开启显示	
	OLED_Clear();	
}
/******************OLED清屏**********************/
void OLED_Clear(void)
{
	u8 i,j;
	for(i=0;i<4;i++)
	{
		OLED_SPI_ReadWriteOneByte(0xB0+i,OLED_CMD);
		OLED_SPI_ReadWriteOneByte(0x10,OLED_CMD);
		OLED_SPI_ReadWriteOneByte(0x0,OLED_CMD);
		for(j=0;j<128;j++) OLED_SPI_ReadWriteOneByte(0x0,OLED_DAT);
	}
}
/****************OLED设置光标**************************
**形参：u8 x,--0~127
**			u8 y,--0~4
**
*******************************************************/
void OLED_Set_Pos(u8 x,u8 y)
{
	OLED_SPI_ReadWriteOneByte((0xB0|y)&0xB7,OLED_CMD);//设置页地址
	OLED_SPI_ReadWriteOneByte(0x10|(x>>4),OLED_CMD);//设列高4位
	OLED_SPI_ReadWriteOneByte(0x0|(x&0xf),OLED_CMD);//设置列4位地址
}
/********************画点函数******************
**形参：u8 x,---横坐标0~127
**			u8 y,---纵坐标0~63
**			u8 dat--0表示灭，1表示亮
**OLED_Draw_Point(1,2,1);
***********************************************/
u8 OLED_GRAM[8][128];
void OLED_Draw_Point(u8 x,u8 y,u8 dat)
{
	u8 page=y/8;//页地址
	if(dat)OLED_GRAM[page][x]|=1<<y%8;//点亮一个点
	else OLED_GRAM[page][x]&=~(1<<y%8);
}
/****************更新GRAM到显示屏***************/
void OLED_Refresh_Gram(void)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_SPI_ReadWriteOneByte(0xB0+i,OLED_CMD);
		OLED_SPI_ReadWriteOneByte(0x10,OLED_CMD);
		OLED_SPI_ReadWriteOneByte(0x0,OLED_CMD);
		for(j=0;j<128;j++) OLED_SPI_ReadWriteOneByte(OLED_GRAM[i][j],OLED_DAT);
	}
}
/***********************显示汉字*********************
**形参：u8 x,横坐标0~127
*				u8 y,纵坐标0~7
*				u8 size,汉字大小,16*16,24*24,32*32
**			u8 number,要显示的第几个汉字
**
*****************************************************/
void OLED_Display_font(u8 x,u8 y,u8 size,u8 number)
{
	u16 i,j;
	for(i=0;i<size/8;i++)
	{
		OLED_Set_Pos(x,y+i);//设置坐标
		for(j=0;j<size;j++)
		{
			if(size==16)OLED_SPI_ReadWriteOneByte(font_16_16[number][j+i*size],OLED_DAT);
			if(size==24)OLED_SPI_ReadWriteOneByte(font_24_24[number][j+i*size],OLED_DAT);		
			else if(size==32)OLED_SPI_ReadWriteOneByte(font_32_32[number][j+i*size],OLED_DAT);
		}
	}
}
/*************************显示一个字符***************/
void OLED_Display_char(u8 x,u8 y,u8 w,u8 h,u8 chr)
{
	u16 i,j;
	for(i=0;i<h/8;i++)
	{
		OLED_Set_Pos(x,y+i);//设置坐标
		for(j=0;j<w;j++)
		{
			if(h==16) OLED_SPI_ReadWriteOneByte(ASCII_8_16[chr-' '][j+i*w],OLED_DAT);	
			else if(h==24) 
			{
				if(chr == ' ')OLED_SPI_ReadWriteOneByte(ASCII_12_24[chr-' '][j+i*w],OLED_DAT);
				else if(chr == '.')OLED_SPI_ReadWriteOneByte(ASCII_12_24[chr-' '-2][j+i*w],OLED_DAT);
				else OLED_SPI_ReadWriteOneByte(ASCII_12_24[chr-' '-15][j+i*w],OLED_DAT);	
			}
		}
	}
}
/***********************显示字符串******************/
void OLED_Display_str(u8 x,u8 y,u8 w,u8 h,u8 *str)
{
	unsigned int i=0;
	while(*str!='\0')
	{
		OLED_Display_char(x+i,y,w,h,*str);
		i+=w;
		str++;
		if((x+i)>127)
		{
			x=0;
			i=0;
			y+=h/8;
			if(y>=7)y=0;
		}
	}
}

/*********************显示图片****************/
void OLED_Displey_Imag(u8 x,u8 y,u8 w,u8 h,u8 *imag)
{
	u8 i,j;
	u8 page=h/8;
	if(h%8)page+=1;
	for(i=0;i<page;i++)//显示的页数
	{
		OLED_Set_Pos(x,y+i);//设置光标位置
		for(j=0;j<w;j++)
		{
			OLED_SPI_ReadWriteOneByte(imag[j+i*w],OLED_DAT);	
		}
	}
}
