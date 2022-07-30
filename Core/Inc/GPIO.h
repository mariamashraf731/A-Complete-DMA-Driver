/*
 * GPIO.h
 *
 *  Created on: Nov 24, 2021
 *      Author: ADVINTIC
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define GPIO_REG(PORT_ID, REG_ID) ((unsigned int*)(PORT_ID + REG_ID))
//clock
#define RCC_AHB1ENR GPIO_REG(0x40023800,0X30)
#define RCC_AHB2ENR GPIO_REG(0x40023800,0x34)

//portA registers
#define GPIOA_MODER GPIO_REG(0x40020000,0X00)
#define GPIOA_OTYPER GPIO_REG(0x40020000,0x04)
#define GPIOA_OSPEEDR GPIO_REG(0x40020000,0x08)
#define GPIOA_PUPDR GPIO_REG(0x40020000,0x0C)
#define GPIOA_IDR GPIO_REG(0x40020000,0x10)
#define GPIOA_ODR GPIO_REG(0x40020000,0x14)
#define GPIOA_BSRR GPIO_REG(0x40020000,0x18)
#define GPIOA_LCKR GPIO_REG(0x40020000,0x1C)
#define GPIOA_AFRL GPIO_REG(0x40020000,0x20)
#define GPIOA_AFRH GPIO_REG(0x40020000,0x24)
//portB registers
#define GPIOB_MODER GPIO_REG(0x40020400,0X00)
#define GPIOB_OTYPER GPIO_REG(0x40020400,0x04)
#define GPIOB_OSPEEDR GPIO_REG(0x40020400,0x08)
#define GPIOB_PUPDR GPIO_REG(0x40020400,0x0C)
#define GPIOB_IDR GPIO_REG(0x40020400,0x10)
#define GPIOB_ODR GPIO_REG(0x40020400,0x14)
#define GPIOB_BSRR GPIO_REG(0x40020400,0x18)
#define GPIOB_LCKR GPIO_REG(0x40020400,0x1C)
#define GPIOB_AFRL GPIO_REG(0x40020400,0x20)
#define GPIOB_AFRH GPIO_REG(0x40020400,0x24)

//write result
#define OK  ((unsigned char)0)
#define NOK ((unsigned char)1)

#define A ((unsigned char)0)
#define B ((unsigned char)1)

//mode types
#define INPUT ((unsigned int)0x00)
#define OUTPUT ((unsigned int)0x01)
#define ALTERNATE_FUN ((unsigned int)0x02)
#define ANALOG ((unsigned int)0x03)

//output modes
#define PUSH_PULL ((unsigned int)0x00)
#define OPEN_DRAIN ((unsigned int)0x01)
//INPUT modes
#define PULL_UP ((unsigned int)0x01)
#define PULL_DOWN ((unsigned int)0x02)

void GPIO_EnableClock(unsigned char PortId);
void GPIO_Init(unsigned char PortId, unsigned char PinNum, unsigned char PinMode,unsigned char DefaultState);
unsigned char GPIO_WritePin(unsigned char PortId, unsigned char PinNum,unsigned char Data);
unsigned char GPIO_ReadPin(unsigned char PortId, unsigned char PinNum);

#endif /* INC_GPIO_H_ */
