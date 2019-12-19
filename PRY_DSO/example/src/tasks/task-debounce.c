/*
 * task-debounce.c
 *
 *  Created on: 18 dic. 2019
 *      Author: ordonezt
 */

#include "task-debounce.h"

key_t Key[N_KEYS] = {0};

void task_debounce(void)
{
	static uint16_t keys_old = NO_KEYS;
	static uint8_t contador_invariables[N_KEYS] = {0};
	uint16_t keys_now, cambios;
	bool key_now_state;
	uint8_t i;

	keys_now = getKeys();	//getKeys se encarga de que la logica sea activo alto

	cambios = keys_now ^ keys_old;	//Tengo 1 en los que cambiaron

	for(i = 0; i < N_KEYS; i++)
	{
		if(!BIS(cambios, i))	//Si la tecla i, no tuvo un cambio entro
		{
			contador_invariables[i]++;
			contador_invariables[i] = contador_invariables[i] >= MIN_TIME_KEYS? MIN_TIME_KEYS: contador_invariables[i];
			if(contador_invariables[i] >= MIN_TIME_KEYS) //Tecla estable
			{
				key_now_state = BIS(keys_now, i);
				Key[i].was_pressed = !Key[i].state && key_now_state? TRUE: FALSE;
				Key[i].was_release = Key[i].state && !key_now_state? TRUE: FALSE;
				Key[i].state = key_now_state;
			}
		}
		else
			contador_invariables[i] = 0;
	}
	keys_old = keys_now;
}

uint16_t getKeys(void)
{
	return (Chip_GPIO_GetPinState(LPC_GPIO, OK_PORT, OK_PIN) << 0) || (Chip_GPIO_GetPinState(LPC_GPIO, PLUS_PORT, PLUS_PIN) << 1) || (Chip_GPIO_GetPinState(LPC_GPIO, MINUS_PORT, MINUS_PIN) << 2) || (Chip_GPIO_GetPinState(LPC_GPIO, SEL_PORT, SEL_PIN) << 3) || (Chip_GPIO_GetPinState(LPC_GPIO, CPL1_PORT, CPL1_PIN) << 4) || (Chip_GPIO_GetPinState(LPC_GPIO, CPL2_PORT, CPL2_PIN) << 5) || (Chip_GPIO_GetPinState(LPC_GPIO, CPL3_PORT, CPL3_PIN) << 6) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN11_PORT, VSEN11_PIN) << 7) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN12_PORT, VSEN12_PIN) << 8) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN13_PORT, VSEN13_PIN) << 9) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN21_PORT, VSEN21_PIN) << 10) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN22_PORT, VSEN22_PIN) << 11) || (Chip_GPIO_GetPinState(LPC_GPIO, VSEN23_PORT, VSEN23_PIN) << 12);
}
void initDebounce(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, OK_PORT, OK_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, PLUS_PORT, PLUS_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, MINUS_PORT, MINUS_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, SEL_PORT, SEL_PIN, IOCON_MODE_PULLUP);

	Chip_IOCON_PinMuxSet(LPC_IOCON, CPL1_PORT, CPL1_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, CPL2_PORT, CPL2_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, CPL3_PORT, CPL3_PIN, IOCON_MODE_PULLUP);

	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN11_PORT, VSEN11_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN12_PORT, VSEN12_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN13_PORT, VSEN13_PIN, IOCON_MODE_PULLUP);

	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN21_PORT, VSEN21_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN22_PORT, VSEN22_PIN, IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, VSEN23_PORT, VSEN23_PIN, IOCON_MODE_PULLUP);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, OK_PORT, OK_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, PLUS_PORT, PLUS_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, MINUS_PORT, MINUS_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, SEL_PORT, SEL_PIN);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, CPL1_PORT, CPL1_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, CPL2_PORT, CPL2_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, CPL3_PORT, CPL3_PIN);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN11_PORT, VSEN11_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN12_PORT, VSEN12_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN13_PORT, VSEN13_PIN);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN21_PORT, VSEN21_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN22_PORT, VSEN22_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, VSEN23_PORT, VSEN23_PIN);
}
