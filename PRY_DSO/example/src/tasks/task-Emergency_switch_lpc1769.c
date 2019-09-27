/*--------------------------------------------------------------------*-

    task-Em_switch_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple EM_SWITCH task for LPC1769.
	[Read Input on LPCXpresso baseboard.]

    Simple switch interface code, with software debounce.

-*--------------------------------------------------------------------*/


// Project header
#include "task-Emergency_switch_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
uint32_t Em_switch_pressed_G = SENSOR_OFF;


// ------ Private constants ----------------------------------------
// SW_THRES must be > 1 for correct debounce behavior
#define SW_THRES (3)


// ------ Private variable -----------------------------------------
static uint8_t switch_input = 0;


/*------------------------------------------------------------------*-

    EM_SWITCH_Init()

    Prepare for EM_SWITCH_Update() function - see below.

-*------------------------------------------------------------------*/
void Em_SWITCH_Init(void)
{
	// Set up "E1" SW as an input pin
	Chip_IOCON_PinMux(LPC_IOCON, EM_SWITCH_PORT, EM_SWITCH_PIN, EM_SWITCH_PIN_MODE, EM_SWITCH_PIN_FUNC);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, EM_SWITCH_PORT, EM_SWITCH_PIN);

	// Switch not pressed
	Em_switch_pressed_G = SENSOR_OFF;
}


/*------------------------------------------------------------------*-

    EM_SWITCH_Update()

    Simple switch interface code, with software debounce.

    If EM_SWITCH is not pressed, Em_switch_pressed_G => SENSOR_OFF.
    If EM_SWITCH is     pressed, Em_switch_pressed_G => SENSOR_ON.

    Must schedule every 10 mili Second (soft deadline).

-*------------------------------------------------------------------*/
void Em_SWITCH_Update(void)
{
	// Duration of switch press
	static uint32_t Duration = 0;

	// Read E1_SWITCH
	switch_input = Chip_GPIO_ReadPortBit(LPC_GPIO, EM_SWITCH_PORT, EM_SWITCH_PIN);
	if (switch_input == SW_PRESSED)
	{
		Duration += 1;
		if (Duration > SW_THRES)
		{
			Duration = SW_THRES;
			Em_switch_pressed_G = SENSOR_ON;
		}
		else
		{
			// Switch pressed, but not yet for long enough
			Em_switch_pressed_G = SENSOR_OFF;
		}
	}
	else
	{
		// Switch not pressed - reset the count
		Duration = 0;

		// Update status
		Em_switch_pressed_G = SENSOR_OFF;
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
