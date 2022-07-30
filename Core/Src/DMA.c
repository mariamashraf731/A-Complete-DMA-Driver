#include "DMA.h"
#include "GPIO.h"


unsigned int *DMA_lookuptable[8][5]={{DMA_S0CR,DMA_S0NDTR,DMA_S0PAR,DMA_S0M0AR,DMA_S0FCR},{DMA_S1CR,DMA_S1NDTR,DMA_S1PAR,DMA_S1M0AR,DMA_S1FCR}
,{DMA_S2CR,DMA_S2NDTR,DMA_S2PAR,DMA_S2M0AR,DMA_S2FCR},{DMA_S3CR,DMA_S3NDTR,DMA_S3PAR,DMA_S3M0AR,DMA_S3FCR}
,{DMA_S4CR,DMA_S4NDTR,DMA_S4PAR,DMA_S4M0AR,DMA_S4FCR},{DMA_S5CR,DMA_S5NDTR,DMA_S5PAR,DMA_S5M0AR,DMA_S5FCR}
,{DMA_S6CR,DMA_S6NDTR,DMA_S6PAR,DMA_S6M0AR,DMA_S6FCR},{DMA_S7CR,DMA_S7NDTR,DMA_S7PAR,DMA_S7M0AR,DMA_S7FCR}};

unsigned int DMA_Interrupt_bits[4]={5,11,21,27};
unsigned char global_stream=0; /*this variable is made so ISR would know
which stream is on as all IRQHandler functions in startup file
are renamed ISR so it can't detect which stream is on inside it*/

void DMA_Init(unsigned char STREAM){
	*RCC_AHB1ENR|=(0X01<<22);//enable clock for DMA2
	if (STREAM < 5){
		*NVIC_ISER1 |= (1<<(24+STREAM));     //DMA2 interrupt enabled    24,25,26,27,28/4,5,6 ISER2
	}
	else {
		*NVIC_ISER2 |= (1<<(STREAM-1));
	}
}
void DMA_Parameters(unsigned char STREAM,unsigned int *P_ADDRESS,unsigned int *M_ADDRESS ){
	global_stream=STREAM;
	*DMA_lookuptable[STREAM][0] =0; /*channel zero selected ,
	priority is low, DMA is the flow controller*/
	while((*DMA_lookuptable[STREAM][0]&1)==1); //wait till stream is disabled
	*DMA_lookuptable[STREAM][0]|=(0x02<<6)|(0x01<<9)|(0x01<<10)|(0x02<<11)|(0x02<<13)|(0X01<<21)|(0X01<<23)|(0x01<<4);
	/*Memory to memory mode , Peripheral/memory address pointer is incremented
     after each data transfer ,  Peripheral/Memory data size is word(32 bit),
     Peripheral /memory burst transfer configuration --> INCR4
     transfer complete interrupt enable */
	*DMA_lookuptable[STREAM][2]= (unsigned int)P_ADDRESS; // source address
	*DMA_lookuptable[STREAM][3]= (unsigned int)M_ADDRESS;  // destination address
	*DMA_lookuptable[STREAM][1]=100; // transfer item size
	*DMA_lookuptable[STREAM][4]&= ~(0X03<<0); // FIFO mode of threshold 1/4
}
void Start_Transfer(unsigned char STREAM){

	*DMA_lookuptable[STREAM][0]|=(0X01<<0);	   //enable DMA stream
}
unsigned char Transfer_state(unsigned char STREAM){
	unsigned char status;
	if (STREAM < 4){
			status=(*DMA_LISR>>DMA_Interrupt_bits[STREAM])&1 ; //store transfer complete status flag of the stream
		}
	else{
			status=(*DMA_HISR>>DMA_Interrupt_bits[STREAM-4])&1 ;
		}
	*DMA_lookuptable[STREAM][0]&= ~(0X01<<0);    //disable  DMA stream
	return status;
}
void ISR(){
	TC_CalloutNotification();
	if (global_stream < 4){
		*DMA_LIFCR |= (1<<DMA_Interrupt_bits[global_stream]); // clear transfer complete interrupt flag of the stream
	}
	else{
		*DMA_HIFCR |= (1<<DMA_Interrupt_bits[global_stream-4]);
	}
}

