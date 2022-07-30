#include "DMA.h"
#include "GPIO.h"

unsigned int src[100];
unsigned int dest[100]={};

void TC_CalloutNotification(){
	unsigned char status=Transfer_state(6);
	if (status){
	for (unsigned char i= 0 ;i<100 ; i++){
	        if (dest[i] != src[i]){
	        	GPIO_WritePin(A,0,1);
	        }
	        else{
	        	GPIO_WritePin(A,1,1);
	        }
	}
	}
	else{
		GPIO_WritePin(A,0,1);
	}
}

int main()
{
 // initialize source
 for(unsigned char i=0; i<100; i++) {
	 src[i] = (i+1)*100;
 }
 //notification led
 GPIO_EnableClock(A);
 GPIO_Init(A,0,OUTPUT,PUSH_PULL);  //red led
 GPIO_Init(A,1,OUTPUT,PUSH_PULL); //green led

  DMA_Init(1);
  DMA_Parameters(1,src, dest);
  Start_Transfer(1);

while(1) {}
return 0;
}
