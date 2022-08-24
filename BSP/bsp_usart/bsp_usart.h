#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "sys.h"
#include "stdint.h"
#include <stdio.h>

#define DMA_RX_BUF_MAX_LEN   100u
#define DMA_TX_BUF_MAX_LEN   100u

void usart1_init(uint32_t baud_rate);
void USART1_DMA_Rx_Config(void);
void USART1_DMA_Tx_Config(void);
void Usart1_Send(u32 *buf,u8 len);

int fputc(int ch, FILE *f);
#endif
