/*--------------------------------------------------------------------*-

    main.c (Released 2019-04)

--------------------------------------------------------------------

    main file for Co-operative - Time Driven System - Project for LPC1769.

    See readme.txt for project information.

-*--------------------------------------------------------------------*/


// Project header
#include "main.h"
#include "board.h"
#include "board_api.h"
#include "../inc/UTFT/HW_lpc1769.h"

/*------------------------------------------------------------------*/

int main(void)
{
	uint32_t i;

	//Board_Init();
	// Check mode, add tasks to schedule

	SYSTEM_Init();

    // Start the scheduler
    SCH_Start();

//	*BIT(6,FIO0PINU)=0; //P0.22 DB0
//	*BIT(6,FIO0PINU)=1; //P0.22 DB0
//	*BIT(6,FIO0PINU)=0; //P0.22 DB0
//
//	*BIT(5,FIO0PINU)=0; //P0.21 DB1
//	*BIT(5,FIO0PINU)=1; //P0.21 DB1
//	*BIT(5,FIO0PINU)=0; //P0.21 DB1
//
//	*BIT(4,FIO0PINU)=0; //P0.20 DB2
//	*BIT(4,FIO0PINU)=1; //P0.20 DB2
//	*BIT(4,FIO0PINU)=0; //P0.20 DB2
//
//	*BIT(3,FIO0PINU)=0; //P0.19 DB3
//	*BIT(3,FIO0PINU)=1; //P0.19 DB3
//	*BIT(3,FIO0PINU)=0; //P0.19 DB3
//
//
//	*BIT(3,FIO0PINU)=0; //P0.19 DB3
//	*BIT(3,FIO0PINU)=1; //P0.19 DB3
//	*BIT(3,FIO0PINU)=0; //P0.19 DB3
//
//	*BIT(2,FIO0PINU)=0; //P0.18 DB4
//	*BIT(2,FIO0PINU)=1; //P0.18 DB4
//	*BIT(2,FIO0PINU)=0; //P0.18 DB4
//
//	*BIT(1,FIO0PINU)=0; //P0.17 DB5
//	*BIT(1,FIO0PINU)=1; //P0.17 DB5
//	*BIT(1,FIO0PINU)=0; //P0.17 DB5
//
//	*BIT(15,FIO0PINL)=0; //P0.15 DB6
//	*BIT(15,FIO0PINL)=1; //P0.15 DB6
//	*BIT(15,FIO0PINL)=0; //P0.15 DB6
//
//	*BIT(9,FIO2PINL)=0; //P2.9 DB7
//	*BIT(9,FIO2PINL)=1; //P2.9 DB7
//	*BIT(9,FIO2PINL)=0; //P2.9 DB7
//
//	*BIT(0,FIO0PINU)=0; //P0.16 DB8
//	*BIT(0,FIO0PINU)=1; //P0.16 DB8
//	*BIT(0,FIO0PINU)=0; //P0.16 DB8
//
//	*BIT(8,FIO2PINL)=0; //P2.8 DB9
//	*BIT(8,FIO2PINL)=1; //P2.8 DB9
//	*BIT(8,FIO2PINL)=0; //P2.8 DB9
//
//	*BIT(6,FIO2PINL)=0; //P2.6 DB10
//	*BIT(6,FIO2PINL)=1; //P2.6 DB10
//	*BIT(6,FIO2PINL)=0; //P2.6 DB10
//
//	*BIT(4,FIO2PINL)=0; //P2.4 DB11
//	*BIT(4,FIO2PINL)=1; //P2.4 DB11
//	*BIT(4,FIO2PINL)=0; //P2.4 DB11
//
//	*BIT(2,FIO2PINL)=0; //P2.2 DB12
//	*BIT(2,FIO2PINL)=1; //P2.2 DB12
//	*BIT(2,FIO2PINL)=0; //P2.2 DB12
//
//
//
//
//	*BIT(1,FIO2PINL)=0; //P2.1 DB13
//	*BIT(1,FIO2PINL)=1; //P2.1 DB13
//	*BIT(1,FIO2PINL)=0; //P2.1 DB13
//
//
//	*BIT(9,FIO0PINL)=0; //P0.9 DB14
//	*BIT(9,FIO0PINL)=1; //P0.9 DB14
//	*BIT(9,FIO0PINL)=0; //P0.9 DB14
//
//	*BIT(7,FIO0PINL)=0; //P0.7 DB15
//	*BIT(7,FIO0PINL)=1; //P0.7 DB15
//	*BIT(7,FIO0PINL)=0; //P0.7 DB15
//
//	SET_CS
//	CLEAR_CS
//
//	SET_RS
//	CLEAR_RS
//
//	CLEAR_WR
//	SET_WR
//
//	cbi(0, 22)
//	sbi(0, 22)
//	cbi(0, 22)
//
//	while (1)
//		pulse_high(0,22);


    while(1)
    {
    	SCH_Dispatch_Tasks();
    }

    return (RETURN_FAULT);
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
