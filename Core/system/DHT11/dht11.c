#include "dht11.h"
/*******起始信号***************/
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//配置为输出模式
	DHT11_DQ_OUT(0); 	//总线拉低
	Delay_Ms(20);    	//拉低至少18ms
	DHT11_DQ_OUT(1); 	//总线拉高
	DelayUs(30);     	//主机拉高20~40us
}
/***********等待DHT11的回应***************
**返回1:未检测到DHT11的存在
**返回0:存在
*******************************************/
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//配置为输入模式	
  while (!DHT11_DQ_IN&&retry<100)//DHT11会拉低83us左右
	{
		retry++;
		DelayUs(1);
	}
	if(retry>=100)return 1;	  	
   while (DHT11_DQ_IN&&retry<250)//DHT11拉低后会再次拉高87us
	{
		retry++;
		DelayUs(1);
	}	 
	if(retry>=500)return 2;
	else retry=0;  
	return 0;
}
/*******************读取1bit数据***************
**	数字0: 50~58us低电平，23~27us高电平
**	数字1：50~58us低电平，68~74us高电平
**返回值：1/0
*************************************************/
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		DelayUs(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		DelayUs(1);
	}
	DelayUs(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
/**************读取1byte数据*************
**
**从DHT11读取一个字节
**返回值：读到的数据
**
******************************************/

u8 DHT11_Read_Byte(void)    
{        
	u8 i,dat;
	dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值-20~60℃
//humi:湿度值5~95%RH
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{  
	u8 stat=0xff;
 	u8 buf[5]={0};
	u8 i;
	DHT11_Rst();//起始信号
	stat=DHT11_Check();
	if(stat==0)//应答信号
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi++=buf[0];
			*humi=buf[1];
			*temp++=buf[2];
			*temp=buf[3];
		}
	}else return stat;
	return 0;	    
}
//检测DHT11的存在
//返回1:不存在
//返回0:存在  
u8 DHT11_Init(void)
{	 
	/*1.开时钟*/		
	DHT11_DQ_OUT(1);//上拉	
	DHT11_Rst();  //复位DHT11
	return DHT11_Check();//等待DHT11的回应
} 




