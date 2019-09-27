/*--------------------------------------------------------------------*-

    task-Door2_switch_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple Door2_SWITCH task for LPC1769.
	[Read Input on LPCXpresso baseboard.]

    Simple switch interface code, with software debounce.

-*--------------------------------------------------------------------*/


// Project header
#include "task-Door2_switch_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
uint32_t Door2_switch_pressed_G = SENSOR_OFF;


// ------ Private constants ----------------------------------------
// SW_THRES must be > 1 for correct debounce behavior
#define SW_THRES (3)


// ------ Private variable -----------------------------------------
static uint8_t switch_input = 0;


/*------------------------------------------------------------------*-

    Door2_SWITCH_Init()

    Prepare for Door2_SWITCH_Update() function - see below.

-*------------------------------------------------------------------*/
void Door2_SWITCH_Init(void)
{
	// Set up "S2" SW as an input pin
	Chip_IOCON_PinMux(LPC_IOCON, DOOR2_SWITCH_PORT, DOOR2_SWITCH_PIN, DOOR2_SWITCH_PIN_MODE, DOOR2_SWITCH_PIN_FUNC);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, DOOR2_SWITCH_PORT, DOOR2_SWITCH_PIN);

	// Switch not pressed
	Door2_switch_pressed_G = SENSOR_OFF;
}


/*------------------------------------------------------------------*-

    Door2_SWITCH_Update()

    Simple switch interface code, with software debounce.

    If Door2_SWITCH is not pressed, Door2_switch_pressed_G => SENSOR_OFF.
    If Door2_SWITCH is     pressed, Door2_switch_pressed_G => SENSOR_ON.

    Must schedule every 10 mili Second (soft deadline).

-*------------------------------------------------------------------*/
void Door2_SWITCH_Update(void)
{
	// Duration of switch press
	static uint32_t Duration = 0;

	// Read S2_SWITCH
	switch_input = Chip_GPIO_ReadPortBit(LPC_GPIO, DOOR2_SWITCH_PORT, DOOR2_SWITCH_PIN);
	if (switch_input == SW_PRESSED)
	{
		Duration += 1;
		if (Duration > SW_THRES)
		{
			Duration = SW_THRES;
			Door2_switch_pressed_G = SENSOR_ON;
		}
		else
		{
			// Switch pressed, but not yet for long enough
			Door2_switch_pressed_G = SENSOR_OFF;
		}
	}
	else
	{
		// Switch not pressed - reset the count
		Duration = 0;

		// Update status
		Door2_switch_pressed_G = SENSOR_OFF;
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
