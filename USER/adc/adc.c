#include "adc.h"
#include "bsp_usart.h"
 
u16 ADC_Value[Sample_Num];  
//u8 ADC_RX_Buf_Length;
//u8 output[6];

void My_ADC_Init()
{
	GPIO_InitTypeDef  GPIO_A;
	ADC_InitTypeDef   ADC_InitStructure;
//	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_A.GPIO_Pin=GPIO_Pin_6;
	GPIO_A.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_A.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_A);
	
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_239Cycles5 );
//	ADC_ExternalTrigConvCmd(ADC1,DISABLE);
		
//	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure); 
		
//	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);
	ADC1_DMA_Rx_Config();
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	  
	while(ADC_GetResetCalibrationStatus(ADC1));	
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));	 	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 

}

//void ADC1_2_IRQHandler(void)
//{
//	u16 ADC1v,i;
//	float ADC_ConvertedValue;	
//	
//	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) 
//		{ 
//			
//			ADC1v = ADC_GetConversionValue(ADC1);
//			
//			ADC_ConvertedValue = (float)(ADC1v*3.3/4095);//?
//			
//			ADC_Value[0] = ADC_ConvertedValue;
//			
//			Usart1_Send(ADC_Value,1);
//			
//			output[0]=(u8)(ADC_ConvertedValue/1)+48;
//			output[1]=46;
//			output[2]=(u8)((((u8)(ADC_ConvertedValue*1000)%1000)/100)+48);
//			output[3]=(u8)((((u8)(ADC_ConvertedValue*1000)%1000)%100/10)+48);
//			output[4]=10;
//			
//			Usart1_Send(output,5);
//		
//			ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
//		}
//}

void ADC1_DMA_Rx_Config(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_BufferSize = Sample_Num;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;	
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_Value;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)(&(ADC1->DR));
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1,ENABLE);	
}



