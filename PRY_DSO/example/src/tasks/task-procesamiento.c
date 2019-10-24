/*
 * task-procesamiento.c
 *
 *  Created on: 10 oct. 2019
 *      Author: Gaston
 */


#include "task-procesamiento.h"
#include "board.h"
#include <stdlib.h>
#include "my_board.h"
//uint8_t signal[300] : Señal ya procesada como para entrar correctamente en la pantalla
uint8_t signal[300];
char str_Vm[6];

enum {IDLE,PROCESSING}processing_state=IDLE;

void task_procesamiento(void)
{
	static uint8_t flag;
 	uint32_t i;
	float Vm=0;
	if (processing_state==IDLE) return;


	for (i=0;i<300;i++)
	{
		Vm+=sample_buffer[i];
		signal[i]=(uint8_t)(220-((sample_buffer[i]*44)/819));
	}
	Vm/=300;
	Vm-=2047.5; //Le resto el offset de continua del ADC

	strcpy(str_Vm,"1,3");
	//itoa(Vm,str_Vm,10);

	//Indico a la tarea solicitante que termine
	processing_state=IDLE;

}
