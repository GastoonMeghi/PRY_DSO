/*
 * HW_lpc1769.h
 *
 *  Created on: 14 jul. 2019
 *      Author: Gaston
 */

#ifndef HW_LPC1769_H_
#define HW_LPC1769_H_
#include "board.h"

#define cbi(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,0);
#define sbi(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,1);
#define pulse_high(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,1); Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,0);
#define pulse_low(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,0); Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,1);

void LCD_Writ_Bus(uint8_t VH,uint8_t VL, uint8_t mode);
void _fast_fill_16(int ch, int cl, long pix);

#endif /* HW_LPC1769_H_ */
