/*--------------------------------------------------------------------*-

    task-Door1_switch_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple Door1_SWITCH task for LPC1769.
	[Read Input on LPCXpresso baseboard.]

    Simple switch interface code, with software debounce.

-*--------------------------------------------------------------------*/


// Project header
#include "task-Door1_switch_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
uint32_t Door1_switch_pressed_G = SENSOR_OFF;


// ------ Private constants ----------------------------------------
// SW_THRES must be > 1 for correct debounce behavior
#define SW_THRES (3)


// ------ Private variable -----------------------------------------
static uint8_t switch_input = 0;


/*------------------------------------------------------------------*-

    Door1_SWITCH_Init()

    Prepare for Door1_SWITCH_Update() function - see below.

-*------------------------------------------------------------------*/
void Door1_SWITCH_Init(void)
{
	// Set up "S1" SW as an input pin
	Chip_IOCON_PinMux(LPC_IOCON, DOOR1_SWITCH_PORT, DOOR1_SWITCH_PIN, DOOR1_SWITCH_PIN_MODE, DOOR1_SWITCH_PIN_FUNC);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, DOOR1_SWITCH_PORT, DOOR1_SWITCH_PIN);

	// Switch not pressed
	Door1_switch_pressed_G = SENSOR_OFF;
}


/*------------------------------------------------------------------*-

    Door1_SWITCH_Update()

    Simple switch interface code, with software debounce.

    If Door1_SWITCH is open, Door1_switch_pressed_G => SENSOR_OFF.
    If Door1_SWITCH is close, Door1_switch_pressed_G => SW_PRESSED.

    Must schedule every 10 mili Second (soft deadline).

-*------------------------------------------------------------------*/
void Door1_SWITCH_Update(void)
{
	// Duration of switch press
	static uint32_t Duration = 0;

	switch_input = Chip_GPIO_ReadPortBit(LPC_GPIO, DOOR1_SWITCH_PORT, DOOR1_SWITCH_PIN);
	if (switch_input == SW_PRESSED)
	{
		Duration += 1;
		if (Duration > SW_THRES)
		{
			Duration = SW_THRES;
			Door1_switch_pressed_G = SENSOR_ON;
		}
		else
		{
			// Switch pressed, but not yet for long enough
			Door1_switch_pressed_G = SENSOR_OFF;
		}
	}
	else
	{
		// Switch not pressed - reset the count
		Duration = 0;

		// Update status
		Door1_switch_pressed_G = SENSOR_OFF;
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
