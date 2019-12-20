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
#include "task-debounce.h"
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

uint8_t freq_index=0;
uint32_t sample_rate2[FREQ_INDEX_LENGHT] = {5000, 100000,200000};

void task_main (void)
{
	static enum {INIC,SAMPLING,SHOWING_RESULTS_1,SHOWING_RESULTS_2}state=INIC;
	uint32_t sample_rate;

	switch (state)
	{
	case INIC:
//		sample_rate = 1000 * parametros.fdt;	/*TODO definir como establecer un sample_rate*/
		/* BORRAR	*/
		sample_rate = 5000;
		startSampling(parametros.trigger_level, parametros.trigger_pol, sample_rate2[freq_index]);
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
			seleccion();
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


void config_sampligRate(void)
{
if(Key[OK].was_pressed)
{
Key[OK].was_pressed = FALSE;
freq_index++;
freq_index%=FREQ_INDEX_LENGHT;
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


	config_sampligRate();
	config_fdv();
	config_fdt1 ();
	config_acople();
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
			}

	}

}


void config_fdt1 (void)
{
	switch(freq_index)
	{
		case 0:
			strcpy(pantalla.fdt,"5Khz   ");
			break;
		case 1:
			strcpy(pantalla.fdt,"6Khz   ");
			break;
		case 2:
			strcpy(pantalla.fdt,"7Khz   ");
			break;
		case 3:
			strcpy(pantalla.fdt,"8Khz   ");
			break;
	}
}
void config_acople (void)
{

	if (Key[CPL1].state)
	{
		strcpy(pantalla.acople,"DC ");
	}
	else if (Key[CPL2].state)
	{
		strcpy(pantalla.acople,"AC ");
	}
	else if (Key[CPL3].state)
	{
		strcpy(pantalla.acople,"GND");
	}

}
void config_fdv (void)
{
	if(Key[VSEN11].state)
	{
		if(Key[VSEN21].state)
		{
			strcpy(pantalla.fdv,"10mV    ");
		}
		else if(Key[VSEN22].state)
		{
			strcpy(pantalla.fdv,"20mV    ");
		}
		else if(Key[VSEN23].state)
		{
			strcpy(pantalla.fdv,"50mV    ");
		}
	}
	else if(Key[VSEN12].state)
	{
		if(Key[VSEN21].state)
		{
			strcpy(pantalla.fdv,"0.1V    ");
		}
		else if(Key[VSEN22].state)
		{
			strcpy(pantalla.fdv,"0.2V    ");
		}
		else if(Key[VSEN23].state)
		{
			strcpy(pantalla.fdv,"0.5V    ");
		}
	}
	else if(Key[VSEN13].state)
	{
		if(Key[VSEN21].state)
		{
			strcpy(pantalla.fdv,"1V    ");
		}
		else if(Key[VSEN22].state)
		{
			strcpy(pantalla.fdv,"2V    ");
		}
		else if(Key[VSEN23].state)
		{
			strcpy(pantalla.fdv,"5V    ");
		}
	}
}

