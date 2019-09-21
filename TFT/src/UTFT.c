/*
 * UTFT.c
 *
 *  Created on: 8 jul. 2019
 *      Author: Gaston
 */

#include "UTFT.h"
#include "HW_lpc1769.h"
#include "board.h"
#include <string.h>


// Include hardware-specific functions for the correct MCU


	static uint8_t			fch, fcl, bch, bcl;
	static uint8_t			orient;
	static long			disp_x_size=239, disp_y_size=399; //pongo el tamaño del display
	static uint8_t			display_model, display_serial_mode;
	static regtype			*P_RS, *P_WR, *P_CS, *P_RST, *P_SDA, *P_SCL, *P_ALE;//puertos
	static regsize			B_RS, B_WR, B_CS, B_RST, B_SDA, B_SCL, B_ALE;// pines
	//Los puertos y los pines se implementan diferente en el lpc1769 así que quizas se termine borrando
	static uint8_t			__p1, __p2, __p3, __p4, __p5;
	static _current_font	cfont;
		uint8_t			_transparent;
	static uint8_t display_transfer_mode=16;
//En principio no lo deberia usar, porque solo carga los valores de los pines
//UTFT(byte model, int RS, int WR, int CS, int RST, int SER)
//{
//	disp_x_size =239;
//	disp_y_size =399;
//	display_transfer_mode =	16;
//	display_model =8;
//
//	__p1 = RS;
//	__p2 = WR;
//	__p3 = CS;
//	__p4 = RST;
//	__p5 = SER;
//
//		_set_direction_registers(display_transfer_mode);
//		P_RS	= portOutputRegister(digitalPinToPort(RS));
//		B_RS	= digitalPinToBitMask(RS);
//		P_WR	= portOutputRegister(digitalPinToPort(WR));
//		B_WR	= digitalPinToBitMask(WR);
//		P_CS	= portOutputRegister(digitalPinToPort(CS));
//		B_CS	= digitalPinToBitMask(CS);
//		P_RST	= portOutputRegister(digitalPinToPort(RST));
//		B_RST	= digitalPinToBitMask(RST);
//}

void LCD_Write_COM(uint8_t VL)
{
	Chip_GPIO_WritePortBit(LPC_GPIO,RS_PORT, RS_BIT, 0);
	LCD_Writ_Bus(0x00,VL,display_transfer_mode);
}

void LCD_Write_DATA2(uint8_t VH,uint8_t VL)
{
		Chip_GPIO_WritePortBit(LPC_GPIO,RS_PORT, RS_BIT, 1);
		LCD_Writ_Bus(VH,VL,display_transfer_mode);
}


void LCD_Write_DATA1(uint8_t VL)
{

		Chip_GPIO_WritePortBit(LPC_GPIO,RS_PORT, RS_BIT, 1);
		LCD_Writ_Bus(0x00,VL,display_transfer_mode);
}

void LCD_Write_COM_DATA(uint8_t com1,int dat1)
{
     LCD_Write_COM(com1);
     LCD_Write_DATA2(dat1>>8,dat1);
}

void LCD_Write_DATA_8(uint8_t VL)
{
    sbi(P_RS, B_RS);
    LCD_Write_Bus_8(VL);
}

void InitLCD(uint8_t orientation)
{
	orient=orientation;
	unsigned long i;


//Estimo que nada de esto es necesario
//	if (__p4 != NOTINUSE)
//		pinMode(__p4,OUTPUT);
//	if ((display_transfer_mode==LATCHED_16) || ((display_transfer_mode==1) && (display_serial_mode==SERIAL_5PIN)))
//		pinMode(__p5,OUTPUT);
//	if (display_transfer_mode!=1)
//		_set_direction_registers(display_transfer_mode);

	Chip_GPIO_WritePortBit(LPC_GPIO,RST_PORT, RST_BIT, 1);
	for (i=0;i<45451*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 5mSeg
	Chip_GPIO_WritePortBit(LPC_GPIO,RST_PORT, RST_BIT, 0);
	for (i=0;i<136353;i++); //trato de hacer una demora de 15mSeg
	Chip_GPIO_WritePortBit(LPC_GPIO,RST_PORT, RST_BIT, 1);
	for (i=0;i<136353;i++); //trato de hacer una demora de 15mSeg

	Chip_GPIO_WritePortBit(LPC_GPIO,CS_PORT, CS_BIT, 0);

	LCD_Write_COM(0x83);
	LCD_Write_DATA1(0x02);  //TESTM=1

	LCD_Write_COM(0x85);
	LCD_Write_DATA1(0x03);  //VDC_SEL=011
	LCD_Write_COM(0x8B);
	LCD_Write_DATA1(0x01);
	LCD_Write_COM(0x8C);
	LCD_Write_DATA1(0x93); //STBA[7]=1,STBA[5:4]=01,STBA[1:0]=11

	LCD_Write_COM(0x91);
	LCD_Write_DATA1(0x01); //DCDC_SYNC=1

	LCD_Write_COM(0x83);
	LCD_Write_DATA1(0x00); //TESTM=0
	//Gamma Setting

	LCD_Write_COM(0x3E);
	LCD_Write_DATA1(0xB0);
	LCD_Write_COM(0x3F);
	LCD_Write_DATA1(0x03);
	LCD_Write_COM(0x40);
	LCD_Write_DATA1(0x10);
	LCD_Write_COM(0x41);
	LCD_Write_DATA1(0x56);
	LCD_Write_COM(0x42);
	LCD_Write_DATA1(0x13);
	LCD_Write_COM(0x43);
	LCD_Write_DATA1(0x46);
	LCD_Write_COM(0x44);
	LCD_Write_DATA1(0x23);
	LCD_Write_COM(0x45);
	LCD_Write_DATA1(0x76);
	LCD_Write_COM(0x46);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x47);
	LCD_Write_DATA1(0x5E);
	LCD_Write_COM(0x48);
	LCD_Write_DATA1(0x4F);
	LCD_Write_COM(0x49);
	LCD_Write_DATA1(0x40);
	//**********Power On sequence************

	LCD_Write_COM(0x17);
	LCD_Write_DATA1(0x91);

	LCD_Write_COM(0x2B);
	LCD_Write_DATA1(0xF9);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	LCD_Write_COM(0x1B);
	LCD_Write_DATA1(0x14);

	LCD_Write_COM(0x1A);
	LCD_Write_DATA1(0x11);

	LCD_Write_COM(0x1C);
	LCD_Write_DATA1(0x06);

	LCD_Write_COM(0x1F);
	LCD_Write_DATA1(0x42);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	LCD_Write_COM(0x19);
	LCD_Write_DATA1(0x0A);

	LCD_Write_COM(0x19);
	LCD_Write_DATA1(0x1A);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg


	LCD_Write_COM(0x19);
	LCD_Write_DATA1(0x12);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg

	LCD_Write_COM(0x1E);
	LCD_Write_DATA1(0x27);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg


	//**********DISPLAY ON SETTING***********

	LCD_Write_COM(0x24);
	LCD_Write_DATA1(0x60);

	LCD_Write_COM(0x3D);
	LCD_Write_DATA1(0x40);

	LCD_Write_COM(0x34);
	LCD_Write_DATA1(0x38);

	LCD_Write_COM(0x35);
	LCD_Write_DATA1(0x38);

	LCD_Write_COM(0x24);
	LCD_Write_DATA1(0x38);
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg
	for (i=0;i<30301*(100000000/SystemCoreClock);i++); //trato de hacer una demora de 10mSeg

	LCD_Write_COM(0x24);
	LCD_Write_DATA1(0x3C);

	LCD_Write_COM(0x16);
	LCD_Write_DATA1(0x1C);

	LCD_Write_COM(0x01);
	LCD_Write_DATA1(0x06);

	LCD_Write_COM(0x55);
	LCD_Write_DATA1(0x00);

	LCD_Write_COM(0x02);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x03);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x04);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x05);
	LCD_Write_DATA1(0xef);

	LCD_Write_COM(0x06);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x07);
	LCD_Write_DATA1(0x00);
	LCD_Write_COM(0x08);
	LCD_Write_DATA1(0x01);
	LCD_Write_COM(0x09);
	LCD_Write_DATA1(0x8f);

	LCD_Write_COM(0x22);

	Chip_GPIO_WritePortBit(LPC_GPIO,RST_PORT, RST_BIT, 1);

	setColor2(255, 255, 255);
	setBackColor2(0,0,0);
	cfont.font=0;
	_transparent = false;
}

void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t aux; //variable auxiliar para hacer el swap
	if (orient==LANDSCAPE)
	{
		//swap x1 y1
		aux=x1;
		x1=y1;
		y1=aux;

		//swap x2 y2
		aux=x2;
		x2=y2;
		y2=aux;

		y1=disp_y_size-y1;
		y2=disp_y_size-y2;

		//swap y1 y2
		aux=y1;
		y1=y2;
		y2=aux;
	}

	LCD_Write_COM_DATA(0x02,x1>>8);
	LCD_Write_COM_DATA(0x03,x1);
	LCD_Write_COM_DATA(0x04,x2>>8);
	LCD_Write_COM_DATA(0x05,x2);
	LCD_Write_COM_DATA(0x06,y1>>8);
	LCD_Write_COM_DATA(0x07,y1);
	LCD_Write_COM_DATA(0x08,y2>>8);
	LCD_Write_COM_DATA(0x09,y2);
	LCD_Write_COM(0x22);
}

void clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

//void drawRect(int x1, int y1, int x2, int y2)
//{
//	if (x1>x2)
//	{
//		swap(int, x1, x2);
//	}
//	if (y1>y2)
//	{
//		swap(int, y1, y2);
//	}
//
//	drawHLine(x1, y1, x2-x1);
//	drawHLine(x1, y2, x2-x1);
//	drawVLine(x1, y1, y2-y1);
//	drawVLine(x2, y1, y2-y1);
//}
//
//void drawRoundRect(int x1, int y1, int x2, int y2)
//{
//	if (x1>x2)
//	{
//		swap(int, x1, x2);
//	}
//	if (y1>y2)
//	{
//		swap(int, y1, y2);
//	}
//	if ((x2-x1)>4 && (y2-y1)>4)
//	{
//		drawPixel(x1+1,y1+1);
//		drawPixel(x2-1,y1+1);
//		drawPixel(x1+1,y2-1);
//		drawPixel(x2-1,y2-1);
//		drawHLine(x1+2, y1, x2-x1-4);
//		drawHLine(x1+2, y2, x2-x1-4);
//		drawVLine(x1, y1+2, y2-y1-4);
//		drawVLine(x2, y1+2, y2-y1-4);
//	}
//}
//
//void fillRect(int x1, int y1, int x2, int y2)
//{
//	if (x1>x2)
//	{
//		swap(int, x1, x2);
//	}
//	if (y1>y2)
//	{
//		swap(int, y1, y2);
//	}
//	if (display_transfer_mode==16)
//	{
//		cbi(P_CS, B_CS);
//		setXY(x1, y1, x2, y2);
//		sbi(P_RS, B_RS);
//		_fast_fill_16(fch,fcl,((long(x2-x1)+1)*(long(y2-y1)+1)));
//		sbi(P_CS, B_CS);
//	}
//	else if ((display_transfer_mode==8) and (fch==fcl))
//	{
//		cbi(P_CS, B_CS);
//		setXY(x1, y1, x2, y2);
//		sbi(P_RS, B_RS);
//		_fast_fill_8(fch,((long(x2-x1)+1)*(long(y2-y1)+1)));
//		sbi(P_CS, B_CS);
//	}
//	else
//	{
//		if (orient==PORTRAIT)
//		{
//			for (int i=0; i<((y2-y1)/2)+1; i++)
//			{
//				drawHLine(x1, y1+i, x2-x1);
//				drawHLine(x1, y2-i, x2-x1);
//			}
//		}
//		else
//		{
//			for (int i=0; i<((x2-x1)/2)+1; i++)
//			{
//				drawVLine(x1+i, y1, y2-y1);
//				drawVLine(x2-i, y1, y2-y1);
//			}
//		}
//	}
//}
//
//void fillRoundRect(int x1, int y1, int x2, int y2)
//{
//	if (x1>x2)
//	{
//		swap(int, x1, x2);
//	}
//	if (y1>y2)
//	{
//		swap(int, y1, y2);
//	}
//
//	if ((x2-x1)>4 && (y2-y1)>4)
//	{
//		for (int i=0; i<((y2-y1)/2)+1; i++)
//		{
//			switch(i)
//			{
//			case 0:
//				drawHLine(x1+2, y1+i, x2-x1-4);
//				drawHLine(x1+2, y2-i, x2-x1-4);
//				break;
//			case 1:
//				drawHLine(x1+1, y1+i, x2-x1-2);
//				drawHLine(x1+1, y2-i, x2-x1-2);
//				break;
//			default:
//				drawHLine(x1, y1+i, x2-x1);
//				drawHLine(x1, y2-i, x2-x1);
//			}
//		}
//	}
//}
//
//void drawCircle(int x, int y, int radius)
//{
//	int f = 1 - radius;
//	int ddF_x = 1;
//	int ddF_y = -2 * radius;
//	int x1 = 0;
//	int y1 = radius;
//
//	cbi(P_CS, B_CS);
//	setXY(x, y + radius, x, y + radius);
//	LCD_Write_DATA(fch,fcl);
//	setXY(x, y - radius, x, y - radius);
//	LCD_Write_DATA(fch,fcl);
//	setXY(x + radius, y, x + radius, y);
//	LCD_Write_DATA(fch,fcl);
//	setXY(x - radius, y, x - radius, y);
//	LCD_Write_DATA(fch,fcl);
//
//	while(x1 < y1)
//	{
//		if(f >= 0)
//		{
//			y1--;
//			ddF_y += 2;
//			f += ddF_y;
//		}
//		x1++;
//		ddF_x += 2;
//		f += ddF_x;
//		setXY(x + x1, y + y1, x + x1, y + y1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x - x1, y + y1, x - x1, y + y1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x + x1, y - y1, x + x1, y - y1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x - x1, y - y1, x - x1, y - y1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x + y1, y + x1, x + y1, y + x1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x - y1, y + x1, x - y1, y + x1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x + y1, y - x1, x + y1, y - x1);
//		LCD_Write_DATA(fch,fcl);
//		setXY(x - y1, y - x1, x - y1, y - x1);
//		LCD_Write_DATA(fch,fcl);
//	}
//	sbi(P_CS, B_CS);
//	clrXY();
//}
//
//void fillCircle(int x, int y, int radius)
//{
//	for(int y1=-radius; y1<=0; y1++)
//		for(int x1=-radius; x1<=0; x1++)
//			if(x1*x1+y1*y1 <= radius*radius)
//			{
//				drawHLine(x+x1, y+y1, 2*(-x1));
//				drawHLine(x+x1, y-y1, 2*(-x1));
//				break;
//			}
//}
//
void clrScr()
{
	long i;

	cbi(CS_PORT,CS_BIT);
	clrXY();
//	if (display_transfer_mode!=1)
		sbi(RS_PORT,RS_BIT);
//	if (display_transfer_mode==16)
		_fast_fill_16(0,0,((disp_x_size+1)*(disp_y_size+1)));
//	else if (display_transfer_mode==8)
//		_fast_fill_8(0,((disp_x_size+1)*(disp_y_size+1)));
//	else
//	{
		//comente de acá
//		for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
//		{
//				LCD_Writ_Bus(0,0,display_transfer_mode);
//		}
		//hasta acá
//	}
	sbi(CS_PORT,CS_BIT);
}
//
//void fillScr2(uint8_t r, uint8_t g, uint8_t b)
//{
//	uint16_t color;
//	color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
//
//	fillScr(color);
//}
//
//void fillScr(uint16_t color)
//{
//	long i;
//	char ch, cl;
//
//	ch=byte(color>>8);
//	cl=byte(color & 0xFF);
//
//	cbi(P_CS, B_CS);
//	clrXY();
//	if (display_transfer_mode!=1)
//		sbi(P_RS, B_RS);
//	if (display_transfer_mode==16)
//		_fast_fill_16(ch,cl,((disp_x_size+1)*(disp_y_size+1)));
//	else if ((display_transfer_mode==8) and (ch==cl))
//		_fast_fill_8(ch,((disp_x_size+1)*(disp_y_size+1)));
//	else
//	{
//		for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
//		{
//			if (display_transfer_mode!=1)
//				LCD_Writ_Bus(ch,cl,display_transfer_mode);
//			else
//			{
//				LCD_Writ_Bus(1,ch,display_transfer_mode);
//				LCD_Writ_Bus(1,cl,display_transfer_mode);
//			}
//		}
//	}
//	sbi(P_CS, B_CS);
//}

void setColor2(uint8_t r, uint8_t g, uint8_t b)
{
	fch=((r&248)|g>>5);
	fcl=((g&28)<<3|b>>3);
}

void setColor(uint16_t color)
{
	fch=(uint8_t)(color>>8);
	fcl=(uint8_t)(color & 0xFF);
}

uint16_t getColor()
{
	return (uint16_t)(fch<<8)|(uint16_t) (fcl);
}

void setBackColor2(uint8_t r, uint8_t g, uint8_t b)
{
	bch=((r&248)|g>>5);
	bcl=((g&28)<<3|b>>3);
	_transparent=false;
}

void setBackColor(uint32_t color)
{
	if (color==VGA_TRANSPARENT)
		_transparent=true;
	else
	{
		bch=(uint8_t)(color>>8);
		bcl=(uint8_t)(color & 0xFF);
		_transparent=false;
	}
}

uint16_t getBackColor()
{
	return ((uint16_t)(bch<<8)) | (uint16_t)(bcl);
}

void setPixel(uint16_t color)
{
	LCD_Write_DATA2((color>>8),(color&0xFF));	// rrrrrggggggbbbbb
}

void drawPixel(int x, int y)
{
	Chip_GPIO_WritePortBit(LPC_GPIO,CS_PORT, CS_BIT,0);
	setXY(x, y, x, y);
	setPixel((fch<<8)|fcl);
	Chip_GPIO_WritePortBit(LPC_GPIO,CS_PORT, CS_BIT,1);
	clrXY();
}

//void drawLine(int x1, int y1, int x2, int y2)
//{
//	if (y1==y2)
//		drawHLine(x1, y1, x2-x1);
//	else if (x1==x2)
//		drawVLine(x1, y1, y2-y1);
//	else
//	{
//		unsigned int	dx = (x2 > x1 ? x2 - x1 : x1 - x2);
//		short			xstep =  x2 > x1 ? 1 : -1;
//		unsigned int	dy = (y2 > y1 ? y2 - y1 : y1 - y2);
//		short			ystep =  y2 > y1 ? 1 : -1;
//		int				col = x1, row = y1;
//
//		cbi(P_CS, B_CS);
//		if (dx < dy)
//		{
//			int t = - (dy >> 1);
//			while (true)
//			{
//				setXY (col, row, col, row);
//				LCD_Write_DATA (fch, fcl);
//				if (row == y2)
//					return;
//				row += ystep;
//				t += dx;
//				if (t >= 0)
//				{
//					col += xstep;
//					t   -= dy;
//				}
//			}
//		}
//		else
//		{
//			int t = - (dx >> 1);
//			while (true)
//			{
//				setXY (col, row, col, row);
//				LCD_Write_DATA (fch, fcl);
//				if (col == x2)
//					return;
//				col += xstep;
//				t += dy;
//				if (t >= 0)
//				{
//					row += ystep;
//					t   -= dx;
//				}
//			}
//		}
//		sbi(P_CS, B_CS);
//	}
//	clrXY();
//}
//
//void drawHLine(int x, int y, int l)
//{
//	if (l<0)
//	{
//		l = -l;
//		x -= l;
//	}
//	cbi(P_CS, B_CS);
//	setXY(x, y, x+l, y);
//	if (display_transfer_mode == 16)
//	{
//		sbi(P_RS, B_RS);
//		_fast_fill_16(fch,fcl,l);
//	}
//	else if ((display_transfer_mode==8) and (fch==fcl))
//	{
//		sbi(P_RS, B_RS);
//		_fast_fill_8(fch,l);
//	}
//	else
//	{
//		for (int i=0; i<l+1; i++)
//		{
//			LCD_Write_DATA(fch, fcl);
//		}
//	}
//	sbi(P_CS, B_CS);
//	clrXY();
//}
//
//void drawVLine(int x, int y, int l)
//{
//	if (l<0)
//	{
//		l = -l;
//		y -= l;
//	}
//	cbi(P_CS, B_CS);
//	setXY(x, y, x, y+l);
//	if (display_transfer_mode == 16)
//	{
//		sbi(P_RS, B_RS);
//		_fast_fill_16(fch,fcl,l);
//	}
//	else if ((display_transfer_mode==8) and (fch==fcl))
//	{
//		sbi(P_RS, B_RS);
//		_fast_fill_8(fch,l);
//	}
//	else
//	{
//		for (int i=0; i<l+1; i++)
//		{
//			LCD_Write_DATA(fch, fcl);
//		}
//	}
//	sbi(P_CS, B_CS);
//	clrXY();
//}
//
void printChar(uint8_t c, uint16_t x, uint16_t y)
{
	uint8_t i,ch;
	uint32_t j;
	uint32_t temp;

	Chip_GPIO_WritePortBit(LPC_GPIO,CS_PORT, CS_BIT, 0);

	if (!_transparent)
	{
		if (orient==PORTRAIT)
		{
			setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);

			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
			{
				//ch=pgm_read_byte(&cfont.font[temp]);
				ch= *((uint8_t*)&cfont.font[temp]);
				for(i=0;i<8;i++)
				{
					if((ch&(1<<(7-i)))!=0)
					{
						setPixel((fch<<8)|fcl);
					}
					else
					{
						setPixel((bch<<8)|bcl);
					}
				}
				temp++;
			}
		}
		else
		{
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;

			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j+=(cfont.x_size/8))
			{
				setXY(x,y+(j/(cfont.x_size/8)),x+cfont.x_size-1,y+(j/(cfont.x_size/8)));
				for (int zz=(cfont.x_size/8)-1; zz>=0; zz--)
				{
					//ch=pgm_read_byte(&cfont.font[temp+zz]);
					ch= *((uint8_t*)&cfont.font[temp+zz]);
					for(i=0;i<8;i++)
					{
						if((ch&(1<<i))!=0)
						{
							setPixel((fch<<8)|fcl);
						}
						else
						{
							setPixel((bch<<8)|bcl);
						}
					}
				}
				temp+=(cfont.x_size/8);
			}
		}
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(j=0;j<cfont.y_size;j++)
		{
			for (int zz=0; zz<(cfont.x_size/8); zz++)
			{
				//ch=pgm_read_byte(&cfont.font[temp+zz]);
				ch= *((uint8_t*)&cfont.font[temp+zz]);
				for(i=0;i<8;i++)
				{

					if((ch&(1<<(7-i)))!=0)
					{
						setXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);
						setPixel((fch<<8)|fcl);
					}
				}
			}
			temp+=(cfont.x_size/8);
		}
	}
	Chip_GPIO_WritePortBit(LPC_GPIO,CS_PORT, CS_BIT, 1);
	clrXY();
}
//
//void rotateChar(byte c, int x, int y, int pos, int deg)
//{
//	byte i,j,ch;
//	word temp;
//	int newx,newy;
//	double radian;
//	radian=deg*0.0175;
//
//	cbi(P_CS, B_CS);
//
//	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
//	for(j=0;j<cfont.y_size;j++)
//	{
//		for (int zz=0; zz<(cfont.x_size/8); zz++)
//		{
//			ch=pgm_read_byte(&cfont.font[temp+zz]);
//			for(i=0;i<8;i++)
//			{
//				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
//				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));
//
//				setXY(newx,newy,newx+1,newy+1);
//
//				if((ch&(1<<(7-i)))!=0)
//				{
//					setPixel((fch<<8)|fcl);
//				}
//				else
//				{
//					if (!_transparent)
//						setPixel((bch<<8)|bcl);
//				}
//			}
//		}
//		temp+=(cfont.x_size/8);
//	}
//	sbi(P_CS, B_CS);
//	clrXY();
//}
//
void print(uint8_t *st, uint16_t x, uint16_t y, int16_t deg)
{
	int stl, i;

	stl = strlen((char*)st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			printChar(*st++, x + (i*(cfont.x_size)), y); //sacar esto si se quiere hacer la rotación de caracteres
			//rotateChar(*st++, x, y, i, deg);
}
//
//void print(String st, int x, int y, int deg)
//{
//	char buf[st.length()+1];
//
//	st.toCharArray(buf, st.length()+1);
//	print(buf, x, y, deg);
//}
//
//void printNumI(long num, int x, int y, int length, char filler)
//{
//	char buf[25];
//	char st[27];
//	boolean neg=false;
//	int c=0, f=0;
//
//	if (num==0)
//	{
//		if (length!=0)
//		{
//			for (c=0; c<(length-1); c++)
//				st[c]=filler;
//			st[c]=48;
//			st[c+1]=0;
//		}
//		else
//		{
//			st[0]=48;
//			st[1]=0;
//		}
//	}
//	else
//	{
//		if (num<0)
//		{
//			neg=true;
//			num=-num;
//		}
//
//		while (num>0)
//		{
//			buf[c]=48+(num % 10);
//			c++;
//			num=(num-(num % 10))/10;
//		}
//		buf[c]=0;
//
//		if (neg)
//		{
//			st[0]=45;
//		}
//
//		if (length>(c+neg))
//		{
//			for (int i=0; i<(length-c-neg); i++)
//			{
//				st[i+neg]=filler;
//				f++;
//			}
//		}
//
//		for (int i=0; i<c; i++)
//		{
//			st[i+neg+f]=buf[c-i-1];
//		}
//		st[c+neg+f]=0;
//
//	}
//
//	print(st,x,y);
//}
//
//void printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
//{
//	char st[27];
//	boolean neg=false;
//
//	if (dec<1)
//		dec=1;
//	else if (dec>5)
//		dec=5;
//
//	if (num<0)
//		neg = true;
//
//	_convert_float(st, num, length, dec);
//
//	if (divider != '.')
//	{
//		for (int i=0; i<sizeof(st); i++)
//			if (st[i]=='.')
//				st[i]=divider;
//	}
//
//	if (filler != ' ')
//	{
//		if (neg)
//		{
//			st[0]='-';
//			for (int i=1; i<sizeof(st); i++)
//				if ((st[i]==' ') || (st[i]=='-'))
//					st[i]=filler;
//		}
//		else
//		{
//			for (int i=0; i<sizeof(st); i++)
//				if (st[i]==' ')
//					st[i]=filler;
//		}
//	}
//
//	print(st,x,y);
//}
//
void setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}
//
//uint8_t* getFont()
//{
//	return cfont.font;
//}
//
//uint8_t getFontXsize()
//{
//	return cfont.x_size;
//}
//
//uint8_t getFontYsize()
//{
//	return cfont.y_size;
//}
//
void drawBitmap(int x, int y, int sx, int sy, unsigned short* data, int scale)
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
			cbi(CS_PORT,CS_BIT);
			setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				col=*((unsigned short*)&data[tc]);
				LCD_Write_DATA2(col>>8,col & 0xff);
			}
			sbi(CS_PORT,CS_BIT);
		}
		else
		{
			cbi(CS_PORT,CS_BIT);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx-1; tx>=0; tx--)
				{
					col=*((unsigned short *)&data[(ty*sx)+tx]);
					LCD_Write_DATA2(col>>8,col & 0xff);
				}
			}
			sbi(CS_PORT,CS_BIT);
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
			cbi(CS_PORT,CS_BIT);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=*((unsigned short *)&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA2(col>>8,col & 0xff);
					}
			}
			sbi(CS_PORT, CS_BIT);
		}
		else
		{
			cbi(CS_PORT, CS_BIT);
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx-1; tx>=0; tx--)
					{
						col=*((unsigned short *)&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA2(col>>8,col & 0xff);
					}
				}
			}
			sbi(CS_PORT, CS_BIT);
		}
	}
	clrXY();
}
//
//void drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
//{
//	unsigned int col;
//	int tx, ty, newx, newy;
//	double radian;
//	radian=deg*0.0175;
//
//	if (deg==0)
//		drawBitmap(x, y, sx, sy, data);
//	else
//	{
//		cbi(P_CS, B_CS);
//		for (ty=0; ty<sy; ty++)
//			for (tx=0; tx<sx; tx++)
//			{
//				col=pgm_read_word(&data[(ty*sx)+tx]);
//
//				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
//				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));
//
//				setXY(newx, newy, newx, newy);
//				LCD_Write_DATA(col>>8,col & 0xff);
//			}
//		sbi(P_CS, B_CS);
//	}
//	clrXY();
//}
//
//void lcdOff()
//{
//	cbi(P_CS, B_CS);
//	switch (display_model)
//	{
//	case PCF8833:
//		LCD_Write_COM(0x28);
//		break;
//	case CPLD:
//		LCD_Write_COM_DATA(0x01,0x0000);
//		LCD_Write_COM(0x0F);
//		break;
//	}
//	sbi(P_CS, B_CS);
//}
//
//void lcdOn()
//{
//	cbi(P_CS, B_CS);
//	switch (display_model)
//	{
//	case PCF8833:
//		LCD_Write_COM(0x29);
//		break;
//	case CPLD:
//		LCD_Write_COM_DATA(0x01,0x0010);
//		LCD_Write_COM(0x0F);
//		break;
//	}
//	sbi(P_CS, B_CS);
//}
//
//void setContrast(char c)
//{
//	cbi(P_CS, B_CS);
//	switch (display_model)
//	{
//	case PCF8833:
//		if (c>64) c=64;
//		LCD_Write_COM(0x25);
//		LCD_Write_DATA(c);
//		break;
//	}
//	sbi(P_CS, B_CS);
//}
//
//int getDisplayXSize()
//{
//	if (orient==PORTRAIT)
//		return disp_x_size+1;
//	else
//		return disp_y_size+1;
//}
//
//int getDisplayYSize()
//{
//	if (orient==PORTRAIT)
//		return disp_y_size+1;
//	else
//		return disp_x_size+1;
//}
//
//void setBrightness(byte br)
//{
//	cbi(P_CS, B_CS);
//	switch (display_model)
//	{
//	case CPLD:
//		if (br>16) br=16;
//		LCD_Write_COM_DATA(0x01,br);
//		LCD_Write_COM(0x0F);
//		break;
//	}
//	sbi(P_CS, B_CS);
//}
//
void setDisplayPage(int8_t page)
{
	cbi(CS_PORT, CS_BIT);
		if (page>7) page=7;
		LCD_Write_COM_DATA(0x04,page);
		LCD_Write_COM(0x0F);
	sbi(CS_PORT, CS_BIT);
}

void setWritePage(int8_t page)
{
	cbi(CS_PORT, CS_BIT);

		if (page>7) page=7;
		LCD_Write_COM_DATA(0x05,page);
		LCD_Write_COM(0x0F);
	sbi(CS_PORT, CS_BIT);
}

