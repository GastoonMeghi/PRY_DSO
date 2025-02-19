/*
 * HW_lpc1769.c
 *
 *  Created on: 14 jul. 2019
 *      Author: Gaston
 */
#include "board.h"


#include "HW_lpc1769.h"

//función que escribe los datos en el bus de 16bits
void LCD_Writ_Bus(uint8_t VH,uint8_t VL, uint8_t mode)
{
	//enciendo un led para mostrar cuanto tiempo paso dentro de esta función
	//Chip_GPIO_WritePortBit(LPC_GPIO,0,22,false);
	*BIT(6,FIO0PINU)=0x10;//usando bitbanding

	//version con bitbanding
	*BIT(10,FIO0PINU)=VL>>0; //&((uint8_t)0x01);
	*BIT(14,FIO1PINU)=VL>>1; //&((uint8_t)0x01);
	*BIT(2,FIO0PINL)=VL>>2;// &((uint8_t)0x01);
	*BIT(3,FIO0PINL)=VL>>3;// &((uint8_t)0x01);
	*BIT(5,FIO0PINU)=VL>>4;// &((uint8_t)0x01);
	*BIT(11,FIO0PINU)=VL>>5;// &((uint8_t)0x01);
	Chip_GPIO_WritePortBit(LPC_GPIO,DB6_PORT, DB6_BIT, VL>>6 &((uint8_t)0x01)); //no me funciono con bitbanding
	//*BIT(12,FIO0PINU)=VL>>6;//&((uint8_t)0x01);
	//*BIT(12,FIO0PINU)=VL>>6;// &((uint8_t)0x01);
	*BIT(13,FIO2PINL)=VL>>7;// &((uint8_t)0x01);


	//version anterior
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB0_PORT, DB0_BIT, VL>>0 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB1_PORT, DB1_BIT, VL>>1 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB2_PORT, DB2_BIT, VL>>2 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB3_PORT, DB3_BIT, VL>>3 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB4_PORT, DB4_BIT, VL>>4 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB5_PORT, DB5_BIT, VL>>5 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB7_PORT, DB7_BIT, VL>>7 &((uint8_t)0x01));




	*BIT(0,FIO0PINU)=VH>>0;
	*BIT(15,FIO0PINL)=VH>>1;
	*BIT(1,FIO0PINU)=VH>>2;
	*BIT(2,FIO0PINU)=VH>>3;
	*BIT(1,FIO0PINL)=VH>>4;
	*BIT(0,FIO0PINL)=VH>>5;
	*BIT(6,FIO0PINL)=VH>>6;
	*BIT(7,FIO0PINL)=VH>>7;

	//Chip_GPIO_WritePortBit(LPC_GPIO,DB8_PORT, DB8_BIT, VH>>0 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB9_PORT, DB9_BIT, VH>>1 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB10_PORT, DB10_BIT, VH>>2 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB11_PORT, DB11_BIT, VH>>3 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB12_PORT, DB12_BIT, VH>>4 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB13_PORT, DB13_BIT, VH>>5 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB14_PORT, DB14_BIT, VH>>6 &((uint8_t)0x01));
	//Chip_GPIO_WritePortBit(LPC_GPIO,DB15_PORT, DB15_BIT, VH>>7 &((uint8_t)0x01));

	*BIT(8,FIO0PINU)=0;
	*BIT(8,FIO0PINU)=1;
	//Chip_GPIO_WritePortBit(LPC_GPIO,WR_PORT, WR_BIT, 0);
	//Chip_GPIO_WritePortBit(LPC_GPIO,WR_PORT, WR_BIT, 1);


	*BIT(6,FIO0PINU)=0x0F;
	//Chip_GPIO_WritePortBit(LPC_GPIO,0,22,true);

}


void _fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	//PORTA = ch;

	*BIT(10,FIO0PINU)=ch>>0; //&((uint8_t)0x01);
	*BIT(14,FIO1PINU)=ch>>1; //&((uint8_t)0x01);
	*BIT(2,FIO0PINL)=ch>>2;// &((uint8_t)0x01);
	*BIT(3,FIO0PINL)=ch>>3;// &((uint8_t)0x01);
	*BIT(5,FIO0PINU)=ch>>4;// &((uint8_t)0x01);
	*BIT(11,FIO0PINU)=ch>>5;// &((uint8_t)0x01);
	Chip_GPIO_WritePortBit(LPC_GPIO,DB6_PORT, DB6_BIT, ch>>6 &((uint8_t)0x01)); //no me funciono con bitbanding
	//*BIT(12,FIO0PINU)=ch>>6;//&((uint8_t)0x01);
	*BIT(13,FIO2PINL)=ch>>7;// &((uint8_t)0x01);


//	Chip_GPIO_WritePortBit(LPC_GPIO,DB0_PORT, DB0_BIT, ch>>0 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB1_PORT, DB1_BIT, ch>>1 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB2_PORT, DB2_BIT, ch>>2 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB3_PORT, DB3_BIT, ch>>3 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB4_PORT, DB4_BIT, ch>>4 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB5_PORT, DB5_BIT, ch>>5 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB6_PORT, DB6_BIT, ch>>6 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB7_PORT, DB7_BIT, ch>>7 &((uint8_t)0x01));


	*BIT(0,FIO0PINU)=cl>>0;
	*BIT(15,FIO0PINL)=cl>>1;
	*BIT(1,FIO0PINU)=cl>>2;
	*BIT(2,FIO0PINU)=cl>>3;
	*BIT(1,FIO0PINL)=cl>>4;
	*BIT(0,FIO0PINL)=cl>>5;
	*BIT(6,FIO0PINL)=cl>>6;
	*BIT(7,FIO0PINL)=cl>>7;

//	Chip_GPIO_WritePortBit(LPC_GPIO,DB8_PORT, DB8_BIT, cl>>0 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB9_PORT, DB9_BIT, cl>>1 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB10_PORT, DB10_BIT, cl>>2 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB11_PORT, DB11_BIT, cl>>3 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB12_PORT, DB12_BIT, cl>>4 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB13_PORT, DB13_BIT, cl>>5 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB14_PORT, DB14_BIT, cl>>6 &((uint8_t)0x01));
//	Chip_GPIO_WritePortBit(LPC_GPIO,DB15_PORT, DB15_BIT, cl>>7 &((uint8_t)0x01));

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
