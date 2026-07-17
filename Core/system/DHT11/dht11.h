#ifndef _DHT11_H
#define _DHT11_H
#include "main.h"
#include "delay.h"
//IO方向设置
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=0X00000008;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=0X00000003;}
////IO操作函数											   
#define	DHT11_DQ_OUT(x)  if(x){GPIOA->ODR|=1<<0;}else{GPIOA->ODR&=~(1<<0);}//写数据
#define	DHT11_DQ_IN   (!!(GPIOA->IDR&1<<0))//读数据

u8 DHT11_Init(void);//DHT11初始化
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif

