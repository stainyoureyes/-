#include "tim.h"
#include "adc.h"
#include "oled.h"
#include "delay.h"
#include "bsp_usart.h"

/*	TIM2 CH3--PA2
	High level is the Effective level.*/

#define Compare 10			//求和平均的个数
u8 paper; 					//测试纸张数
u32 TEST_Array[Max] ;	 //校准数组 
u32 Mid_Array[Max-1] ;	//校正数值中间值 
u32 mid_data;		//校准中值数据 

int j=0,i=0,m=0;

u16 overflow=0;
u32 TIM3_Cnt,TIM2_Cnt,sum;
u8 Overflow_Flag;
extern u8 Text_Times;//测试次数

/*	标志位为0有效	*/	
u8 LCD_FLAG;			//显示标志位	
extern u8 Text_Finish_Flag;//测试结束标志位
extern u8 Examine_Flag;//检测纸张数目标志位
extern u8 Text_Write_Flag;	//测试写入数据标志位
 u8 Short_Circuit_Flag;
u8 buff3[2],buff4[8];
void TIM2_EXT_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStructure;	 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_ETRClockMode1Config(TIM2, TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted, 0x00);  //设置为采用外部时钟计数,可设定滤波参数消除信号干扰
	
	TIM2_TimeBaseInitStructure.TIM_Period = 0xffff;//设置自动重装载值
	TIM2_TimeBaseInitStructure.TIM_Prescaler = 0;//设置分频
	TIM2_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM2_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseInitStructure);	
	  
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);

}

void TIM3_INT_Init()
{
	TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;	 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM3_TimeBaseInitStructure.TIM_Period = 0xFFFF;//设置自动重装载值
	TIM3_TimeBaseInitStructure.TIM_Prescaler = 0;//设置分频
	TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseInitStructure);	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

/*	TIM4 CH1--PA0	100ms	*/

void TIM4_IRQ_Init()   
{
	TIM_TimeBaseInitTypeDef  TIM4_CH1;
	NVIC_InitTypeDef 		 NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
	TIM4_CH1.TIM_Period = 9999; 
	TIM4_CH1.TIM_Prescaler =719; 
	TIM4_CH1.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM4_CH1.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM4_CH1); 
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM4,DISABLE);
	

}


void TIM2_IRQHandler(void)
{
	u32 cnt;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)

		{
			
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
			cnt = TIM_GetCounter(TIM3); 

			TIM3_Cnt=65536*overflow+cnt;

			if (m<Compare && m>0)
			{
				
				sum = sum+TIM3_Cnt;
				m++;
			}
			else  if(m==Compare)
			{
				
				TIM2_Cnt = sum/Compare;
				m=0;
				sum=0;
			}
			else if(m==0)
			{
				TIM2_Cnt = TIM3_Cnt;
			}
//			TIM3_Cnt2=TIM3_Cnt-TIM3_Cnt1;
//			TIM3_Cnt1=TIM3_Cnt;
//			printf("N:%d \r\n",TIM2_Cnt);
//			display_math(1,1,TIM3_Cnt,buff1);
			
			TIM_SetCounter(TIM3,0); 
			TIM_SetCounter(TIM2,0); 
			overflow=0;
		}
}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIM3中断标志位
	
	overflow++;
	if(overflow>=1500)
	{
//		Short_Circuit_Flag=1;
// 		ssd1306_clear();
		display_short_circuit(0,1);
//		Short_Circuit_Flag=0;
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		LCD_FLAG = 1;
	}
	
}

void TIM4_IRQHandler(void)
{
	int a; 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{

		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		

//		LCD_FLAG=1;
//		
//		TEST_Array[i++] = TIM3_Cnt;
//		mid_data = TEST_Array[i]+TEST_Array[i+1];
//		mid_data /= 2;
//		Mid_Array[j++] = mid_data;
		
		if(Text_Finish_Flag == 0)
		{
			if(Text_Write_Flag == 0)
			{
				TEST_Array[Text_Times] = TIM2_Cnt;

				Text_Write_Flag=1;
				LCD_FLAG=1;

			}
//			else 
//			{
//				LCD_FLAG=1;
//			}

		}
//		else if(Text_Finish_Flag == 1)
		else
		{
			for(i=0;i<Max-1;i++)
			{
				mid_data = TEST_Array[i]+TEST_Array[i+1];
				mid_data /= 2;
				Mid_Array[j++] = mid_data;
			}

			
		}
		
		if(Examine_Flag == 1)
		{
//			for(a=0;a<Max-1;a++)
//			{
//				if(TIM2_Cnt<Mid_Array[a] && TIM2_Cnt>=Mid_Array[a+1])
//				{
//					paper=a+1;
//				}
//				else if(TIM2_Cnt>Mid_Array[0])
//				{
//					paper=1;
//				}
//				else if(TIM2_Cnt<Mid_Array[Max-2])
//				{
//					paper=Max-1;
//				}
//				else {paper=20;}
		for(a=0;a<Max-1;a++)
		{	
			if(TIM2_Cnt<Mid_Array[a])
			{
			if(TIM2_Cnt>Mid_Array[a+1])
			 {
				paper=a+2;
			 }
			}				
		}
		if(TIM2_Cnt>=Mid_Array[0])
		{
			paper=1;
		}
		if(TIM2_Cnt<=Mid_Array[Max-2])
		{
			paper=Max;
		}	
		ssd1306_clear();
		display_paper(0,1,paper,buff3);
		display_math(0,1,TIM2_Cnt,buff4);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		Examine_Flag = 0;
			
//			Examine_Flag == 1
		}
					
		
		TIM_Cmd(TIM4, DISABLE);		

	}
	
}

