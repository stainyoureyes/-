#include "tim.h"
#include "adc.h"
#include "led.h"
#include "exit.h"
#include "gpio.h"
#include "oled.h"
#include "usart.h"	  
#include "delay.h"
#include <bsp_iic.h>

#define Times 50
u8 buff1[2],buff2[8];
u8 Paper_Count=0;
u8 Beep_Flag;
extern u32 TIM3_Cnt,TIM2_Cnt;
extern u8 LCD_FLAG;
extern u8 paper;
extern u8 Text_Finish_Flag;
extern u8 Examine_Flag;
extern u8 Text_Times;
extern u32 TEST_Array[Max];
int main()
{
//	u32 temp=1222255;
//	u8 i,j;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	IO_Init();
	BSP_IIC_Init();
	LED_Init();
	delay_init();
	uart_init(115200);
	exti_init();
	ssd1306_Init();
	
	ssd1306_display128x32(clear);

//	display_beginning(0,1);
//ssd1306_display128x32(ma);

//	delay_ms(1000);

//	ssd1306_display128x32(clear);

	TIM2_EXT_Init();
	TIM3_INT_Init();
	TIM4_IRQ_Init();

   while(1)
	{	
//		temp = Get_Temp_Average(10);
//		printf("HIGH:%d us\r\n",temp);
//		BEEP=1;
		
//		display_math(1,1,temp,buff);
		if (LCD_FLAG == 1)
		{
			ssd1306_clear();
			display_paper(0,1,Text_Times+1,buff1);
			display_math(0,1,TEST_Array[Text_Times],buff2);
//			Text_Times = 0;
			LCD_FLAG=0;			
			
		}
		if(Text_Finish_Flag == 1)
		{
			
		}
		
//		if (Examine_Flag == 1)
//		{
//			ssd1306_clear();
//			display_paper(0,1,paper,buff1);
//			display_math(0,1,TIM2_Cnt,buff2);
//			Examine_Flag = 0;
//		}
		if (Beep_Flag == 1)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			delay_ms(200);
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			Beep_Flag = 0;
		}
	}
	
}
