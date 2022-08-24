//#include "bsp_usart.h"
//#include "tim.h"
//#include "led.h"
//#include "adc.h"

///*	RX-PA9	TX-PA10	
//	USART_DMA 	USART_IT_IDLE */
//       
//u8 Uart1_Rx = 0;             
//u8 Usart_DMA_Rx_Buf[DMA_RX_BUF_MAX_LEN];
//u8 Usart_DMA_Tx_Buf[DMA_TX_BUF_MAX_LEN];
//u16 RX_Buf_Length;
//u16 TX_Buf_Length;

//void usart1_init(u32 baud_rate)
//{
//	GPIO_InitTypeDef 	GPIO_A;
//	USART_InitTypeDef 	USART_InitStructure;
//	NVIC_InitTypeDef	NVIC_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	USART_DeInit(USART1);
//	
//	GPIO_A.GPIO_Pin=GPIO_Pin_10;
//	GPIO_A.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_A.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_A);
//	
//	GPIO_A.GPIO_Pin=GPIO_Pin_9;
//	GPIO_A.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA,&GPIO_A);
//	
//	USART_InitStructure.USART_BaudRate=baud_rate;
//	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Parity=USART_Parity_No;
//	USART_InitStructure.USART_StopBits=USART_StopBits_1;
//	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
//	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
//	USART_Init(USART1,&USART_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
//	
//	USART1_DMA_Rx_Config();			//An Unforgettable Bug
////	USART1_DMA_Tx_Config();

//	USART_Cmd(USART1, ENABLE); 	

//}

//void USART1_DMA_Rx_Config(void)
//{
//	DMA_InitTypeDef dma;
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	DMA_DeInit(DMA1_Channel5); 
//	dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
//	dma.DMA_MemoryBaseAddr = (uint32_t)Usart_DMA_Rx_Buf;
//	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
//	dma.DMA_BufferSize =DMA_RX_BUF_MAX_LEN;

//	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	dma.DMA_Mode = DMA_Mode_Circular;
//	dma.DMA_Priority=DMA_Priority_Medium;
//	dma.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel5, &dma);
//	DMA_ClearFlag(DMA1_FLAG_TC5);
//	DMA_Cmd (DMA1_Channel5,ENABLE);
//}

////void USART1_DMA_Tx_Config(void)
////{
////	DMA_InitTypeDef dma;
////	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
////	DMA_DeInit(DMA1_Channel4);
////	dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
////	dma.DMA_MemoryBaseAddr = (uint32_t)Usart_DMA_Tx_Buf;
////	dma.DMA_DIR = DMA_DIR_PeripheralDST ;                        //外设作为数据传输目的地
////	dma.DMA_BufferSize =DMA_TX_BUF_MAX_LEN;
////	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
////	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
////	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
////	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
////	dma.DMA_Mode = DMA_Mode_Circular;
////	dma.DMA_Priority=DMA_Priority_Medium;
////	dma.DMA_M2M = DMA_M2M_Disable;
////	DMA_Init(DMA1_Channel4, &dma);
////	//DMA_ITConfig(DMA1_Channel4, DMA_IT_TE, ENABLE);
////	DMA_ClearFlag(DMA1_FLAG_TC4);
////	DMA_Cmd (DMA1_Channel4,ENABLE);

////}

//void USART1_IRQHandler(void)
//{      
//    uint16_t i = 0;  
//	u32 Uart1_Buffer[256];
//	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)
//	{
//		/* 接收数据 */
//		
//		USART_ClearITPendingBit(USART1, USART_IT_IDLE);
////		LED=!LED;
//		LED=0;
//		USART1->SR;
//		USART1->DR;
//		USART_ReceiveData(USART1);
//		DMA_Cmd(DMA1_Channel5,DISABLE);
//		DMA_ClearFlag( DMA1_FLAG_TC5 ); 
//		RX_Buf_Length = DMA_RX_BUF_MAX_LEN - DMA_GetCurrDataCounter(DMA1_Channel5);
//        for (i = 0;i < RX_Buf_Length;i++)  
//        {  
//            Uart1_Buffer[i] = Usart_DMA_Rx_Buf[i];  
//                
//        } 
//        DMA_SetCurrDataCounter(DMA1_Channel5,DMA_RX_BUF_MAX_LEN);    
//        DMA_Cmd(DMA1_Channel5,ENABLE); 

//		Usart1_Send(Uart1_Buffer,RX_Buf_Length);
//	}
//}


//void Usart1_Send(u32 *buf,u8 len)
//{
//    u8 t;
//    for(t=0;t<len;t++)     
//    {          
//        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);   
//        USART_SendData(USART1,buf[t]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//    }    
//}


