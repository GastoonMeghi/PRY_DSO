/*
 * UTFT.h
 *
 *  Created on: 8 jul. 2019
 *      Author: Gaston
 */

#ifndef UTFT_H_
#define UTFT_H_

#define UTFT_VERSION	283

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A			0
#define ILI9327			1
#define SSD1289			2
#define ILI9325C		3
#define ILI9325D_8		4
#define ILI9325D_16		5
#define HX8340B_8		6
#define HX8340B_S		7
#define HX8352A			8
#define ST7735			9
#define PCF8833			10
#define S1D19122		11
#define SSD1963_480		12
#define SSD1963_800		13
#define S6D1121_8		14
#define S6D1121_16		15
#define	SSD1289LATCHED	16
#define ILI9341_16		17
#define ILI9341_8       18
#define SSD1289_8		19
#define	SSD1963_800ALT	20
#define ILI9481			21
#define ILI9325D_16ALT	22
#define S6D0164			23
#define NOT_IN_USE		24
#define ILI9341_S5P		25
#define ILI9341_S4P		26
#define R61581			27
#define ILI9486			28
#define CPLD			29
#define HX8353C			30

#define ITDB32			0	// HX8347-A (16bit)
#define ITDB32WC		1	// ILI9327  (16bit)
#define ITDB32S			2	// SSD1289  (16bit)
#define CTE32			2	// SSD1289  (16bit)
#define ITDB24			3	// ILI9325C (8bit)
#define ITDB24D			4	// ILI9325D (8bit)
#define ITDB24DWOT		4	// ILI9325D (8bit)
#define ITDB28			4	// ILI9325D (8bit)
#define DMTFT24104      4   // ILI9325D (8bit)
#define DMTFT28103      4   // ILI9325D (8bit)
#define ITDB22			6	// HX8340-B (8bit)
#define ITDB22SP		7	// HX8340-B (Serial 4Pin)
#define ITDB32WD		8	// HX8352-A (16bit)
#define CTE32W			8	// HX8352-A	(16bit)
#define ITDB18SP		9	// ST7735   (Serial 5Pin)
#define LPH9135			10	// PCF8833	(Serial 5Pin)
#define ITDB25H			11	// S1D19122	(16bit)
#define ITDB43			12	// SSD1963	(16bit) 480x272
#define ITDB50			13	// SSD1963	(16bit) 800x480
#define CTE50			13	// SSD1963	(16bit) 800x480
#define EHOUSE50		13	// SSD1963	(16bit) 800x480
#define ITDB24E_8		14	// S6D1121	(8bit)
#define ITDB24E_16		15	// S6D1121	(16bit)
#define INFINIT32		16	// SSD1289	(Latched 16bit) -- Legacy, will be removed later
#define ELEE32_REVA		16	// SSD1289	(Latched 16bit)
#define CTE32_R2		17	// ILI9341	(16bit)
#define ITDB24E_V2_16   17  // ILI9341	(16bit)
#define ITDB28_V2_ALT   17  // ILI9341	(16bit)
#define ITDB32S_V2      17  // ILI9341	(16bit)
#define ITDB28_V2       18  // ILI9341	(8bit)
#define ITDB24E_V2_8    18  // ILI9341	(8bit)
#define ELEE32_REVB		19	// SSD1289	(8bit)
#define CTE70			20	// SSD1963	(16bit) 800x480 Alternative Init
#define EHOUSE70		20	// SSD1963	(16bit) 800x480 Alternative Init
#define CTE32HR			21	// ILI9481	(16bit)
#define CTE28			22	// ILI9325D (16bit) Alternative Init
#define CTE22			23	// S6D0164	(8bit)
#define DMTFT22102      23  // S6D0164  (8bit)
#define DMTFT28105      25  // ILI9341  (Serial 5Pin)
#define MI0283QT9		26  // ILI9341	(Serial 4Pin)
#define CTE35IPS		27	// R61581	(16bit)
#define CTE40			28	// ILI9486	(16bit)
#define EHOUSE50CPLD	29	// CPLD		(16bit)
#define CTE50CPLD		29	// CPLD		(16bit)
#define CTE70CPLD		29	// CPLD		(16bit)
#define DMTFT18101      30  // HX8353C  (Serial 5Pin)

#define SERIAL_4PIN		4
#define SERIAL_5PIN		5
#define LATCHED_16		17

#define NOTINUSE		255

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF


#include "HW_AVR_DEFINES.h"
#include "board.h"

typedef struct
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
}_current_font;


		void	InitLCD(uint8_t orientation);
		void	clrScr();
		void	drawPixel(int x, int y);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	fillScr2(uint8_t r, uint8_t g, uint8_t b);
		void	fillScr(uint16_t color);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	fillRect(int x1, int y1, int x2, int y2);
		void	fillRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	fillCircle(int x, int y, int radius);
		void	setColor2(uint8_t r, uint8_t g, uint8_t b);
		void	setColor(uint16_t color);
		uint16_t	getColor();
		void	setBackColor2(uint8_t r, uint8_t g, uint8_t b);
		void	setBackColor(uint32_t color);
		uint16_t	getBackColor();
		void	print(uint8_t *st, uint16_t x, uint16_t y, int16_t deg);
//		void	print(String st, int x, int y, int deg=0);
//		void	printNumI(long num, int x, int y, int length=0, char filler=' ');
//		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ');
		void	setFont(uint8_t* font);
//		uint8_t* getFont();
//		uint8_t	getFontXsize();
//		uint8_t	getFontYsize();
		void drawBitmap(int x, int y, int sx, int sy, unsigned short *data, int scale);
		//		void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
//		void	lcdOff();
//		void	lcdOn();
//		void	setContrast(char c);
//		int		getDisplayXSize();
//		int		getDisplayYSize();
//		void	setBrightness(uint8_t br);
		void	setDisplayPage(int8_t page);
		void	setWritePage(int8_t page);

/*
	The functions and variables below should not normally be used.
	They have been left publicly available for use in add-on libraries
	that might need access to the lower level functions of UTFT.

	Please note that these functions and variables are not documented
	and I do not provide support on how to use them.
*/

		void LCD_Writ_Bus(uint8_t VH,uint8_t VL, uint8_t mode);
		void LCD_Write_COM(uint8_t VL);
		void LCD_Write_DATA2(uint8_t VH,uint8_t VL);
		void LCD_Write_DATA1(uint8_t VL);
		void LCD_Write_COM_DATA(uint8_t com1,int dat1);
		void LCD_Write_Bus_8(uint8_t VL);
		void LCD_Write_DATA_8(uint8_t VL);
		void _hw_special_init();
		void setPixel(uint16_t color);
//		void drawHLine(int x, int y, int l);
//		void drawVLine(int x, int y, int l);
		void printChar(uint8_t c, uint16_t x, uint16_t y);
		void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
		void clrXY();
//		void rotateChar(byte c, int x, int y, int pos, int deg);
//		void _fast_fill_16(int ch, int cl, long pix);
//		void _fast_fill_8(int ch, long pix);
//		void _convert_float(char *buf, double num, int width, uint8_t prec);



#endif /* UTFT_H_ */
