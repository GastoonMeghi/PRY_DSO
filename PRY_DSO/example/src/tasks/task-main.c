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

//estado_pantalla=DONE: Controla si la pantalla debe escribir o no
//si esta en modo DONE, la pantalla termino de escribir lo que se le encomendo
//para volver a escribir datos nuevos, se colocan los mismos en pantalla_t pantalla
// y se pone estado_pantalla en WRITTING, el valor cambiara a DONE cuando termine
// NO SE DEBE MODIFICAR EL VALOR DE pantalla SI LA PANTALLA SE ENCUENTRA EN WRITTING
// TODAS LAS FUNCIONES INTERNAS TRABAJAN DIRECTAMENTE SOBRE ESA VARIABLE
extern uint8_t estado_pantalla;

//Estructura de datos con los valores tal y como deben ser mostrados en la pantalla
extern pantalla_t pantalla;

//uint8_t signal[300] : Señal ya procesada como para entrar correctamente en la pantalla
extern uint8_t signal[300];

//Estado del Task de procesamiento de señal
//Cuando queramos que trabaje hay que ponerla en PROCESSING
//La tarea va a leer el buffer del adc y colocarlo en el buffer signal ADC ya aconidicionado para
//mostrarse en la pantalla, comunica que finalizo cambiando su estado a IDLE
extern enum {IDLE,PROCESSING}processing_state;



void task_main (void)
{
	static enum {INIC,SAMPLING,SHOWING_RESULTS_1,SHOWING_RESULTS_2}state=INIC;
	uint32_t sample_rate;

	switch (state)
	{
	case INIC:

		sample_rate = 1000 * parametros.fdt;	/*TODO definir como establecer un sample_rate*/
		startSampling(parametros.trigger_level, parametros.trigger_pol, sample_rate);
		state=SAMPLING;

		return;

	case SAMPLING:
		if (sample_buffer_flag)
		{
			sample_buffer_flag = 0;
			processing_state=PROCESSING;
			state=SHOWING_RESULTS_1;
			//Esto habilita la tarea que procesa las muestras, esta directamente
			//toma el buffer del adc y lo coloca en la variable global signal
		}
		return;

	case SHOWING_RESULTS_1:
		if (processing_state==IDLE)//terminamos de procesar las muestras
		{
			memcpy(pantalla.signal,signal,SIGNAL_LENGTH*sizeof(*(signal)));//Copio los datos en la pantalla
			estado_pantalla=WRITTING; //Habilito la pantalla para que escriba
			state=SHOWING_RESULTS_2;
		}
		return;
	case SHOWING_RESULTS_2:
		if (estado_pantalla==DONE)
		{
			state=INIC;
		}
		return;
	}



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
//	if (CPLSEL1_ACTIVO)
//	{
//		strcpy(pantalla.acople,"DC");
//	}
//	else if (CPLSEL2_ACTIVO)
//	{
//		strcpy(pantalla.acople,"AC");
//	}
//	else if (CPLSEL3_ACTIVO)
//	{
//		strcpy(pantalla.acople,"GND");
//	}
//

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
				parametros.trigger_pol=RISING;
				return;
			}
			if (MINUS_PRESSED)
			{
				parametros.trigger_pol=FALLING;
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
