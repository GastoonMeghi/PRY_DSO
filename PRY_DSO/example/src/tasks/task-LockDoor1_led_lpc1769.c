/*--------------------------------------------------------------------*-

    task-motor1_led_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple MOTOR1_LED task for LPC1769.
	[Write Output on LPCXpresso baseboard.]

    Simple motor led interface code.

-*--------------------------------------------------------------------*/


// Project header
#include "task-LockDoor1_led_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
uint32_t Lock1_led_required_G = 0;

extern uint32_t LogicOff_G,Time_in_em1_G;
// ------ Private constants ----------------------------------------

#define MAX_EM_DURATION (50)
// ------ Private variable -----------------------------------------


/*------------------------------------------------------------------*-

    Lock1_Init()

    Prepare for Lock1_Update() function - see below.

-*------------------------------------------------------------------*/
void Lock1_LED_Init(void)
{
	// Set up "GPIO" LED as an output pin
	Chip_IOCON_PinMux(LPC_IOCON, LOCK1_LED_PORT, LOCK1_LED_PIN, LOCK1_LED_PIN_MODE, LOCK1_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LOCK1_LED_PORT, LOCK1_LED_PIN);
	Chip_IOCON_PinMux(LPC_IOCON, RG1_LED_PORT, RG1_LED_PIN, RG1_LED_PIN_MODE, RG1_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RG1_LED_PORT, RG1_LED_PIN);
}


/*------------------------------------------------------------------*-

    Lock1_Update()

    Simple motor led interface code.

    If Lock1_led_required_G => LOCK_OFF, LOCK_LED => LED_OFF.
    If Lock1_led_required_G => LOCK_ON,  LOCK_LED => LED_ON.

    Must schedule every 10 mili Second (soft deadline).

-*------------------------------------------------------------------*/
void Lock1_LED_Update(void)
{
	static uint32_t RGEm=0;
	// Read Lock1_led_required_G "status"
	if(LogicOff_G==FALSE){

		if (Lock1_led_required_G == LOCK_ON)
			{
				// Write LOCK1_LED => LED_ON
		    	Chip_GPIO_WritePortBit(LPC_GPIO, LOCK1_LED_PORT, LOCK1_LED_PIN, LED_ON);
		    	Chip_GPIO_WritePortBit(LPC_GPIO, RG1_LED_PORT, RG1_LED_PIN, LED_ON);
			}
			else
			{
				// Write LOCK1_LED => LED_OFF
				Chip_GPIO_WritePortBit(LPC_GPIO, LOCK1_LED_PORT, LOCK1_LED_PIN, LED_OFF);
				Chip_GPIO_WritePortBit(LPC_GPIO, RG1_LED_PORT, RG1_LED_PIN, LED_OFF);
			}

	}else{
		Chip_GPIO_WritePortBit(LPC_GPIO, LOCK1_LED_PORT, LOCK1_LED_PIN, LED_OFF);

		if (++Time_in_em1_G >= MAX_EM_DURATION)
		{
						Time_in_em1_G=0;
						if(RGEm==1){
							RGEm=2;
							Chip_GPIO_WritePortBit(LPC_GPIO, RG1_LED_PORT, RG1_LED_PIN, LED_OFF);


						}else{
							RGEm=1;
							Chip_GPIO_WritePortBit(LPC_GPIO, RG1_LED_PORT, RG1_LED_PIN, LED_ON);


						}

		}
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
