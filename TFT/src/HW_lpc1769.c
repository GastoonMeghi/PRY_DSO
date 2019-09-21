/*
 * HW_lpc1769.c
 *
 *  Created on: 14 jul. 2019
 *      Author: Gaston
 */
#include "board.h"


#include "HW_lpc1769.h"

void LCD_Writ_Bus(uint8_t VH,uint8_t VL, uint8_t mode)
{
	Chip_GPIO_WritePortBit(LPC_GPIO,DB0_PORT, DB0_BIT, VL>>0 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB1_PORT, DB1_BIT, VL>>1 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB2_PORT, DB2_BIT, VL>>2 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB3_PORT, DB3_BIT, VL>>3 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB4_PORT, DB4_BIT, VL>>4 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB5_PORT, DB5_BIT, VL>>5 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB6_PORT, DB6_BIT, VL>>6 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB7_PORT, DB7_BIT, VL>>7 &((uint8_t)0x01));


	Chip_GPIO_WritePortBit(LPC_GPIO,DB8_PORT, DB8_BIT, VH>>0 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB9_PORT, DB9_BIT, VH>>1 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB10_PORT, DB10_BIT, VH>>2 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB11_PORT, DB11_BIT, VH>>3 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB12_PORT, DB12_BIT, VH>>4 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB13_PORT, DB13_BIT, VH>>5 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB14_PORT, DB14_BIT, VH>>6 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB15_PORT, DB15_BIT, VH>>7 &((uint8_t)0x01));

	Chip_GPIO_WritePortBit(LPC_GPIO,WR_PORT, WR_BIT, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO,WR_PORT, WR_BIT, 1);

}


void _fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	//PORTA = ch;
	Chip_GPIO_WritePortBit(LPC_GPIO,DB0_PORT, DB0_BIT, ch>>0 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB1_PORT, DB1_BIT, ch>>1 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB2_PORT, DB2_BIT, ch>>2 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB3_PORT, DB3_BIT, ch>>3 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB4_PORT, DB4_BIT, ch>>4 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB5_PORT, DB5_BIT, ch>>5 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB6_PORT, DB6_BIT, ch>>6 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB7_PORT, DB7_BIT, ch>>7 &((uint8_t)0x01));

	Chip_GPIO_WritePortBit(LPC_GPIO,DB8_PORT, DB8_BIT, cl>>0 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB9_PORT, DB9_BIT, cl>>1 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB10_PORT, DB10_BIT, cl>>2 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB11_PORT, DB11_BIT, cl>>3 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB12_PORT, DB12_BIT, cl>>4 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB13_PORT, DB13_BIT, cl>>5 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB14_PORT, DB14_BIT, cl>>6 &((uint8_t)0x01));
	Chip_GPIO_WritePortBit(LPC_GPIO,DB15_PORT, DB15_BIT, cl>>7 &((uint8_t)0x01));

	//PORTC = cl;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
		pulse_low(WR_PORT, WR_BIT);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(WR_PORT, WR_BIT);
		}

}
