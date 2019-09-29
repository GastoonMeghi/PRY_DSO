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
#define CLEAR_CS *BIT(8,FIO0PINL)=0

#define FIO0MASKL 0x2009C010
#define FIO1MASKL 0x2009C030
#define FIO2MASKL 0x2009C050
#define FIO3MASKL 0x2009C070
#define FIO4MASKL 0x2009C090

#define FIO0MASKU 0x2009C012
#define FIO1MASKU 0x2009C032
#define FIO2MASKU 0x2009C052
#define FIO3MASKU 0x2009C072
#define FIO4MASKU 0x2009C092

#define FIO0PINL 0x2009C014
#define FIO1PINL 0x2009C034
#define FIO2PINL 0x2009C054
#define FIO3PINL 0x2009C074
#define FIO4PINL 0x2009C094
#define FIO0PINU 0x2009C016
#define FIO1PINU 0x2009C036
#define FIO2PINU 0x2009C056
#define FIO3PINU 0x2009C076
#define FIO4PINU 0x2009C096

#define BIT_BAND_ALIAS 0x22000000
#define PERIPH_BASE 0x20000000
#define BIT(bit,ADDRES) (uint32_t *)((ADDRES-PERIPH_BASE)*32+(bit*4)+BIT_BAND_ALIAS)

#define SET_CS *BIT(8,FIO0PINL)=1;
#define CLEAR_CS *BIT(8,FIO0PINL)=0;

#define SET_RS *BIT(9,FIO0PINU)=1;
#define CLEAR_RS *BIT(9,FIO0PINU)=0;


void LCD_Writ_Bus(uint8_t VH,uint8_t VL, uint8_t mode);
void _fast_fill_16(int ch, int cl, long pix);

#endif /* HW_LPC1769_H_ */
