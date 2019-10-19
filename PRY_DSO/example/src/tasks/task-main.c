/*
 * task-main.c
 *
 *  Created on: 14 oct. 2019
 *      Author: Gaston
 */

//NO ESTA AGREGADA AL SCHEDULER

#include "board.h"
#include "../main/main.h"
#include "task-main.h"
#include "task-pantalla.h"
#include "string.h"
parametros_t parametros;
extern pantalla_t pantalla;

void task_main (void)
{


}


//Lee todos los pulsadores e informa directamente a la pantalla de la selección de los parametros:
// acople
// escala de tensión
// trigger polaridad y valor

void seleccion(void)
{
	static enum {reposo,config_trigger_lvl,config_trigger_pol,config_fdt}state=reposo;
	if (FLANCO_OK)
	{
		pantalla.seleccion=NO_SEL;
		state=reposo;
		return;
	}

	//**lectura del acople***//
	if (CPLSEL1_ACTIVO)
	{
		strcpy(pantalla.acople,"DC");
	}
	else if (CPLSEL2_ACTIVO)
	{
		strcpy(pantalla.acople,"AC");
	}
	else if (CPLSEL3_ACTIVO)
	{
		strcpy(pantalla.acople,"GND");
	}


	switch (state)
	{
		case reposo:
			if (FLANCO_OK)
			{
				pantalla.seleccion=SEL_TRIGGER_LEVEL;
				state=config_trigger_lvl;
				//CLEAN_FLANCO_OK;
			}
			return;
		case config_trigger_lvl:
			if (PLUS_PRESSED)
			{
				parametros.trigger_level++;
				return;
			}
			if (MINUS_PRESSED)
			{
				parametros.trigger_level--;
				return;
			}
			if (FLANCO_SEL)
			{
				pantalla.seleccion=SEL_TRIGGER_POL;
				state=config_trigger_pol;
				//CLEAN_FLANCO_SEL;
			}
		case config_trigger_pol:
			if (PLUS_PRESSED)
			{
				parametros.trigger_pol=RISING_EDGE;
				return;
			}
			if (MINUS_PRESSED)
			{
				parametros.trigger_pol=FALLING_EDGE;
				return;
			}
			if (FLANCO_SEL)
			{
				pantalla.seleccion=SEL_FDT;
				state=config_fdt;
				//CLEAN_FLANCO_SEL;
			}
		case config_fdt:
			if (PLUS_PRESSED)
			{
				parametros.fdt++;
				return;
			}
			if (MINUS_PRESSED)
			{
				parametros.fdt--;
				return;
			}
			if (FLANCO_SEL)
			{
				pantalla.seleccion=SEL_TRIGGER_LEVEL;
				state=config_trigger_lvl;
				//CLEAN_FLANCO_SEL;
			}
	}

}
