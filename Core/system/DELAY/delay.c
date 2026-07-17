#include "delay.h"
/*
函数功能: 延时us单位
*/
void DelayUs(int us)
{
#ifndef	_SYSTICK_IRQ_
	int i,j;
	for(i=0;i<us;i++)
		for(j=0;j<72;j++);
#else
	u32 tmp;
	SysTick->VAL=0;         //CNT计数器值	
	SysTick->LOAD=9*us;     //9表示1us
	SysTick->CTRL&=~(1<<2);//选择外部时钟源
	SysTick->CTRL|=1<<0;//开启滴答定定时器
	do
	{
			tmp=SysTick->CTRL; //读取状态
	}while((!(tmp&1<<16))&&(tmp&1<<0));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  
#endif	
}
void Delay_Ms(u32 time)
{
#ifndef _SYSTICK_IRQ_ 
	u32 i,j,k;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			for(k=0;k<time;k++);
#else
	u32 temp=0;
	SysTick->LOAD=9000*time;//重装载值
	SysTick->VAL=0;//清空计数器值
	SysTick->CTRL&=~(1<<2);//选择外部时钟源
	SysTick->CTRL|=1<<0;//开启滴答定定时器
	while(1)
	{
		temp=SysTick->CTRL;
		if(temp&1<<16)break;
		if(time==0)break;//重装载值为0直接退出
	}
#endif
}
