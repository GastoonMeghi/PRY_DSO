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
	return
}
