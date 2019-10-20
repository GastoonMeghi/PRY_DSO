/*
 * drivers_PWM.c
 *
 *  Created on: 13 sep. 2019
 *      Author: Tomás Ordóñez
 */

#include "my_chip.h"


void Chip_PWM_SetPrescale(uint32_t pr)
{
	LPC_PWM1->PR = pr - 1;
}

uint32_t Chip_PWM_GetPrescale(void)
{
	return LPC_PWM1->PR + 1;
}

void Chip_PWM_CounterEnable(uint8_t state)
{
	if(state == ENABLE)
		LPC_PWM1->TCR |= 1 << BIT_COUNTER_ENABLE;
	else
		LPC_PWM1->TCR &= ~(1 << BIT_COUNTER_ENABLE);
}

void Chip_PWM_CounterReset(uint8_t state)
{
	if(state == ENABLE)
		LPC_PWM1->TCR |= 1 << BIT_COUNTER_RESET;
	else
		LPC_PWM1->TCR &= ~(1 << BIT_COUNTER_RESET);

}

void Chip_PWM_Enable(uint8_t state)
{
	if(state == ENABLE)
		LPC_PWM1->TCR |= 1 << BIT_PWM_ENABLE;
	else
		LPC_PWM1->TCR &= ~(1 << BIT_PWM_ENABLE);

}

void Chip_PWM_CountMode(uint8_t mode, uint8_t input)
{
	LPC_PWM1->CTCR &= ~0xF;	//Limpio los bits
	LPC_PWM1->CTCR |= mode | (input << BIT_COUNT_INPUT);
}

void Chip_PWM_SetMatchControl(uint8_t match, uint8_t accion)
{
	LPC_PWM1->MCR &= ~(accion << match*3); 	//Limpio el bit
	LPC_PWM1->MCR |= accion << match*3;		//Cargo la accion
}

void Chip_PWM_ClearMatchControl(uint8_t match, uint8_t accion)
{
	LPC_PWM1->MCR &= ~(accion << match*3); 	//Limpio la accion
}

void Chip_PWM_SelectEdge(uint8_t salida, uint8_t modo)
{
	if(modo == DOUBLE_EDGE)
		LPC_PWM1->PCR |= 1 << salida;
	else
		LPC_PWM1->PCR &= ~(1 << salida);
}

void Chip_PWM_OutputEnable(uint8_t salida, uint8_t estado)
{
	if(estado == ENABLE)
		LPC_PWM1->PCR |= 1 << (salida + 8);
	else
		LPC_PWM1->PCR &= ~(1 << (salida + 8));
}

void Chip_PWM_LatchEnable(uint8_t match)
{
	LPC_PWM1->LER |= 1 << match;
}

void Chip_PWM_SetMatch(uint8_t match, uint32_t valor)
{
	if(match <= 3)
		LPC_PWM1->MRA[match] = valor;
	else
		LPC_PWM1->MRB[match-4] = valor;
}

uint32_t Chip_PWM_GetMatch(uint8_t match)
{
	if(match <= 3)
		return LPC_PWM1->MRA[match];
	else
		return LPC_PWM1->MRB[match - 4];
}
