/*--------------------------------------------------------------------*-

    task-Lock2_led_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple Lock2_LED task for LPC1769.
	[Write Output on LPCXpresso baseboard.]

    Simple Lock led interface code.

-*--------------------------------------------------------------------*/


// Project header
#include "task-LockDoor2_led_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
uint32_t Lock2_led_required_G = 0;

extern uint32_t LogicOff_G,Time_in_em2_G;
// ------ Private constants ----------------------------------------

#define MAX_EM_DURATION (50)
// ------ Private variable -----------------------------------------


/*------------------------------------------------------------------*-

    Lock2_Init()

    Prepare for Lock2_Update() function - see below.

-*------------------------------------------------------------------*/
void Lock2_LED_Init(void)
{
	// Set up "Lock2" LED as an output pin
	Chip_IOCON_PinMux(LPC_IOCON, LOCK2_LED_PORT, LOCK2_LED_PIN, LOCK2_LED_PIN_MODE, LOCK2_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LOCK2_LED_PORT, LOCK2_LED_PIN);
	Chip_IOCON_PinMux(LPC_IOCON, RG2_LED_PORT, RG2_LED_PIN, RG2_LED_PIN_MODE, RG2_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RG2_LED_PORT, RG2_LED_PIN);
}


/*------------------------------------------------------------------*-

    Lock2_Update()

    Simple lock led interface code.

    If Lock2_led_required_G => LOCK_OFF, LOCK_LED => LED_OFF.
    If Lock2_led_required_G => LOCK_ON,  LOCK_LED => LED_ON.

    Must schedule every 10 mili Second (soft deadline).

-*------------------------------------------------------------------*/
void Lock2_LED_Update(void)
{
	static uint32_t RGEm=0;

	if(LogicOff_G==FALSE){
	// Read Lock2_led_required_G "status"
		if (Lock2_led_required_G == LOCK_ON)
		{
			// Write Lock2_LED => LED_ON
			Chip_GPIO_WritePortBit(LPC_GPIO, LOCK2_LED_PORT, LOCK2_LED_PIN, LED_ON);
			Chip_GPIO_WritePortBit(LPC_GPIO, RG2_LED_PORT, RG2_LED_PIN, LED_ON);
		}
		else
		{
			// Write Lock2_LED => LED_OFF
			Chip_GPIO_WritePortBit(LPC_GPIO, LOCK2_LED_PORT, LOCK2_LED_PIN, LED_OFF);
			Chip_GPIO_WritePortBit(LPC_GPIO, RG2_LED_PORT, RG2_LED_PIN, LED_OFF);

		}
	}else{
		Chip_GPIO_WritePortBit(LPC_GPIO, LOCK2_LED_PORT, LOCK2_LED_PIN, LED_OFF);

		if (++Time_in_em2_G >= MAX_EM_DURATION)
		{
						Time_in_em2_G=0;
						if(RGEm==1){
							RGEm=2;
							Chip_GPIO_WritePortBit(LPC_GPIO, RG2_LED_PORT, RG2_LED_PIN, LED_OFF);


						}else{
							RGEm=1;
							Chip_GPIO_WritePortBit(LPC_GPIO, RG2_LED_PORT, RG2_LED_PIN, LED_ON);


						}

		}
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
