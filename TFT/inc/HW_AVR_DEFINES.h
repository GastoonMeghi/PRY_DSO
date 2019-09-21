/*
 * HW_AVR_DEFINES.h
 *
 *  Created on: 8 jul. 2019
 *      Author: Gaston
 */

#ifndef HW_AVR_DEFINES_H_
#define HW_AVR_DEFINES_H_

#define cbi(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,0);
#define sbi(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,0);
#define pulse_high(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,1); Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,0);
#define pulse_low(port, bit) Chip_GPIO_WritePortBit(LPC_GPIO,port, bit,0); Chip_GPIO_WritePortBit(LPC_GPIO,port,bit,1);
#define cport(port, data) port &= data
#define sport(port, data) port |= data

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define fontbyte(x) *((uint8_t *) &cfont.font[x])

#define regtype volatile uint8_t
#define regsize uint8_t
#define bitmapdatatype unsigned int*

#endif /* HW_AVR_DEFINES_H_ */
