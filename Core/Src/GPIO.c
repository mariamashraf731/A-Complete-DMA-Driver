#include "GPIO.h"

#define _OUTTYPE_MASK ((unsigned char)0x01)
#define _OUTTYPE_SHIFT 0

#define _PUPD_MASK ((unsigned char)0x06)
#define _PUPD_SHIFT 1

unsigned int *Reg_lookuptable[2][6] = {{RCC_AHB1ENR,GPIOA_MODER,GPIOA_OTYPER,GPIOA_PUPDR,GPIOA_ODR,GPIOA_IDR},{RCC_AHB1ENR,GPIOB_MODER,GPIOB_OTYPER,GPIOB_PUPDR,GPIOB_ODR,GPIOB_IDR}};

void GPIO_EnableClock(unsigned char PortId) {
    	*Reg_lookuptable[PortId][0] |= (0x01 << PortId);
  }

void GPIO_Init(unsigned char PortId, unsigned char PinNum, unsigned char PinMode,
               unsigned char DefaultState) {

	  *Reg_lookuptable[PortId][1] &= ~(0x03 << 2 * PinNum);
	  *Reg_lookuptable[PortId][1] |= PinMode << 2 * PinNum;

	  *Reg_lookuptable[PortId][2] &= ~(1 << PinNum);
	  *Reg_lookuptable[PortId][2] |= ((DefaultState & _OUTTYPE_MASK) >> _OUTTYPE_SHIFT) << PinNum;

	  *Reg_lookuptable[PortId][3] &= ~(0x03 << 2 * PinNum);
	  *Reg_lookuptable[PortId][3] |= ((DefaultState & _PUPD_MASK) >> _PUPD_SHIFT) << (2 * PinNum);

}

unsigned char GPIO_WritePin(unsigned char PortId, unsigned char PinNum,
                            unsigned char Data) {
  unsigned char result;
      if (((*Reg_lookuptable[PortId][1] & (0x03 << 2 * PinNum)) >> (2 * PinNum)) == 1) {
        if (Data) {
        	*Reg_lookuptable[PortId][4] |= (1 << PinNum);
        } else {
        	*Reg_lookuptable[PortId][4] &= ~(1 << PinNum);
        }
        result = OK;
      } else {
        result = NOK;
      }

  return result;
}

unsigned char GPIO_ReadPin(unsigned char PortId, unsigned char PinNum) {
  unsigned char data = 0;
      data = (*Reg_lookuptable[PortId][5] & (1 << PinNum)) >> PinNum;
  return data;
}
