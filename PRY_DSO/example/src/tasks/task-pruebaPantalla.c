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
void task_pruebaPantalla(void)
{
	static char i=0;
	static char aux[2];
	static uint8_t flag=1;
	static uint8_t flag2=0;
	uint32_t j=0;
	if (estado_pantalla==DONE)
	{
		if(flag)
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
		strcpy(pantalla.Veff,"Veff=");
		strcat(pantalla.Veff,aux);
		strcat(pantalla.Veff,"mV");

		strcpy(pantalla.Vpp,"Vpp=");
		strcat(pantalla.Vpp,aux);
		strcat(pantalla.Vpp,"V");

		strcpy(pantalla.T,"T=");
		strcat(pantalla.T,aux);
		strcat(pantalla.T,"mSeg");
		if (flag2==0)
		{
			for (j=0;j<SIGNAL_LENGTH;j++)
			{
				pantalla.signal[j]=sin[j];
			}
			flag2=1;
		}
		else
		{
			for (j=0;j<SIGNAL_LENGTH;j++)
			{
				pantalla.signal[j]=sin4[j];
			}
			flag2=0;
		}
		i++;
		if(i==9)i=0;
		estado_pantalla=WRITTING;

	}
}


