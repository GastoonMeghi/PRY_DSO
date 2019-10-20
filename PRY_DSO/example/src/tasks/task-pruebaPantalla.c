/*
 * task-pruebaPantalla.c
 *
 *  Created on: 4 oct. 2019
 *      Author: Gaston
 */

#include "task-pruebaPantalla.h"
#include "task-pantalla.h"
#include "board.h"
#include <String.h>

extern pantalla_t pantalla;
extern uint8_t estado_pantalla;
extern int sin4[300];
extern int sin[300];
extern uint8_t signal[300];
extern char str_Vm[6];
void task_pruebaPantalla(void)
{
	static char i=0;
	static char aux[2];
	static uint8_t flag=1;
	static uint8_t flag2=0;
	uint32_t j=0;
	if (estado_pantalla==DONE)
	{
		if(flag)//flag para que se inicialize una sola vez
		{
		for (i=0;i<VOLTAGE_LENGTH;i++)
			{
			pantalla.Vpp[i]=' ';
			pantalla.Veff[i]=' ';
			pantalla.Vm[i]=' ';
			}
			pantalla.Vpp[VOLTAGE_LENGTH-1]=0;
			pantalla.Veff[VOLTAGE_LENGTH-1]=0;
			pantalla.Vm[VOLTAGE_LENGTH-1]=0;

			for (i=0;i<FREC_LENGTH;i++)
			{
					pantalla.fs[i]=' ';
					pantalla.f[i]=' ';
					pantalla.T[i]=' ';
			}
			pantalla.fs[FREC_LENGTH-1]=0;
			pantalla.f[FREC_LENGTH-1]=0;
			pantalla.T[FREC_LENGTH-1]=0;

			for (i=0;i<ACOPLE_LENGTH;i++)
			{
					pantalla.acople[i]=' ';
			}
			pantalla.acople[ACOPLE_LENGTH-1]=0;
		aux[1]=0;
		}
		flag=0;
		aux[0]='0'+i;
//		strcpy(pantalla.Veff,"Veff=");
//		strcat(pantalla.Veff,aux);
//		strcat(pantalla.Veff,"mV");
//
//		strcpy(pantalla.Vpp,"Vpp=");
//		strcat(pantalla.Vpp,aux);
//		strcat(pantalla.Vpp,"V");
//
//		strcpy(pantalla.T,"T=");
//		strcat(pantalla.T,aux);
//		strcat(pantalla.T,"mSeg");
//
//		strcpy(pantalla.Vm,"Vm=");
//		strcat(pantalla.Vm,str_Vm);
//		strcat(pantalla.Vm,"mV");
				strcpy(pantalla.fdt,aux);
				strcpy(pantalla.fdv,aux);
				strcpy(pantalla.trigger_level,aux);


		if (flag2==0) //toglea entre dos señales
		{
			for (j=0;j<SIGNAL_LENGTH;j++)
			{
				pantalla.signal[j]=signal[j];
			}
			flag2=1;
			pantalla.seleccion=SEL_TRIGGER_POL;
			strcpy(pantalla.acople,"AC");
			strcpy(pantalla.trigger_pol,"ASC");

		}
		else
		{
			for (j=0;j<SIGNAL_LENGTH;j++)
			{
				pantalla.signal[j]=sin4[j];
			}
			pantalla.seleccion=SEL_FDT;
			strcpy(pantalla.acople,"DC");
			strcpy(pantalla.trigger_pol,"DES");
			flag2=0;
		}
		i++;
		if(i==9)i=0;
		estado_pantalla=WRITTING;

	}
}


