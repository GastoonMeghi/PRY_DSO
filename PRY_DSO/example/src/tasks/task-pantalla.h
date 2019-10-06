/*
 * task-pantalla.h
 *
 *  Created on: 22 sep. 2019
 *      Author: Gaston
 */

#ifndef SRC_TASKS_TASK_PANTALLA_H_
#define SRC_TASKS_TASK_PANTALLA_H_

#include "../inc/UTFT/DefaultFonts.h"
#include "../inc/UTFT/UTFT.h"

#define CANTIDAD_DE_MUESTRAS 10
#define WRITTING 0
#define DONE 1
#define SIN_CAMBIOS 94 //caracter ASCII de "^"
#define VOLTAGE_LENGTH 9
#define FREC_LENGTH 8
#define ACOPLE_LENGTH 5
#define SIGNAL_LENGTH 300
#define MUESTRAS_IMPRIMIBLES 7
typedef struct {
	uint8_t state_pantalla; // Los contenidos de la estructura de ser modificados unicamente cuando la pantalla este en modo done
									 // Una vez ingresados nuevos datos debe colocarse la pantalla en modo writting y esperar que el estado vuelva a donde

	char Vpp[VOLTAGE_LENGTH]; //String con la tensión pico a pico medida con la unidad al final Ej: "14V  " "0,12mV"
	char Veff[VOLTAGE_LENGTH]; //tensión eficaz de la señal medida
	char Vm[VOLTAGE_LENGTH]; //String con la tensión media medida
	char fs[FREC_LENGTH]; //frecuencia de muestreo utilizada
	char f[FREC_LENGTH]; //frecuencia de la señal medida
	char T[FREC_LENGTH]; //período de la señal medida
	char acople[ACOPLE_LENGTH]; // acople seleccionado "AC" "DC" "GND"

	uint8_t signal[300]; //señal tal cual y como debe ser muestrada. el contenido del vector son
						 //directamente la altura de los pixeles en la pantalla, entonces:
						 // El nivel de cero es 110 (ahí es donde esta mapeado el cero de tensíon)
						 // las tensiones positivas son las menores a 110 y con un máx de 0
						 // las tensiones negativas son las mayores a 110 y con un máx de 220

} pantalla_t;

//structura que muestra si hubo algún cambio en alguno de los parametros para saber si hace falta
// o no actualizar la pantalla
typedef struct {
	uint8_t Vpp;
	uint8_t Veff;
	uint8_t Vm;
	uint8_t fs;
	uint8_t f;
	uint8_t T;
	uint8_t acople;
	uint8_t signal;
} cambios_pantalla_t;

void Board_UTFT_Init(void);
void task_pantalla (void);
void task_pantalla_Init(void);
cambios_pantalla_t calcular_cambios(pantalla_t *pantalla_actual);


#endif /* SRC_TASKS_TASK_PANTALLA_H_ */
