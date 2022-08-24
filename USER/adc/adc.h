#ifndef __ADC_H
#define __ADC_H

#include "stdint.h"	//c99
#include "sys.h"
#define Channel_Num 1
#define Sample_Num  10

void My_ADC_Init(void);
void ADC1_DMA_Rx_Config(void);
#endif 
