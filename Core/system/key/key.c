#include "main.h"
#include "gpio.h"
#include "key.h"

unsigned char KEY_GetVal(void)
{
	
	unsigned char static stat=0;
	if(((!KEY1)||(!KEY2))&&!stat)
	{
		stat=1;
		HAL_Delay(30);
		if(!KEY1) return 1;
		else if(!KEY2) return 2;
		else return 0;
	}
	else{
		if(KEY1&&KEY2) stat=0;
	}
	return 0;
		
}
