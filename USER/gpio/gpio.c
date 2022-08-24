#include "gpio.h"

void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB端口时钟

	//BEEP: PB1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //开漏输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 

	GPIO_SetBits(GPIOB,GPIO_Pin_1);
//	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	//KEY0:PC1	KEY1:PC13	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_13;				//上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
	//KEY2:PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				//上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	//WK_UP:PA0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//下拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	
	//IIC: SCL: PB6  SDA: PB7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}
	

