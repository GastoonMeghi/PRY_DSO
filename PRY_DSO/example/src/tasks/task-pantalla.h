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
#define MUESTRAS_IMPRIMIBLES 9

#define NUM_FUNCIONES_PANTALLA 7+1 //siempre debe ser la cantidad de tareas +1 porque la ultima indica con un NULL que ya se finalizo


//*******PARAMETROS CONFIGURABLES CON LOS BOTONES*****
#define SEL_TRIGGER_LEVEL 0
#define SEL_TRIGGER_POL 1
#define SEL_FDT 2
#define NO_SEL 3

//CORDENADAS X E Y DE LOS PARAMETROS EN PANTALLA
#define TRIGGER_LEVEL_X 305
#define TRIGGER_POL_X 375
#define FDT_X 305
#define FDV_X 305
#define ACOPLE_X 305

#define TRIGGER_LEVEL_Y 135
#define TRIGGER_POL_Y 135
#define FDT_Y 120
#define FDV_Y 105
#define ACOPLE_Y 230

typedef struct {
	uint8_t state_pantalla; // Los contenidos de la estructura de ser modificados unicamente cuando la pantalla este en modo done
									 // Una vez ingresados nuevos datos debe colocarse la pantalla en modo writting y esperar que el estado vuelva a donde
	uint8_t seleccion; //indica cual es el dato que se va a modificar para escribirlo en verde
	char Vpp[VOLTAGE_LENGTH]; //String con la tensión pico a pico medida con la unidad al final Ej: "14V  " "0,12mV"
	char Veff[VOLTAGE_LENGTH]; //tensión eficaz de la señal medida
	char Vm[VOLTAGE_LENGTH]; //String con la tensión media medida
	char fs[FREC_LENGTH]; //frecuencia de muestreo utilizada
	char f[FREC_LENGTH]; //frecuencia de la señal medida
	char T[FREC_LENGTH]; //período de la señal medida
	char acople[ACOPLE_LENGTH]; // acople seleccionado "AC" "DC" "GND"
	char fdv[VOLTAGE_LENGTH];
	char fdt[FREC_LENGTH];
	char trigger_level[VOLTAGE_LENGTH];
	char trigger_pol[VOLTAGE_LENGTH];

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
	uint8_t fdv;
	uint8_t fdt;
	uint8_t trigger_pol;
	uint8_t trigger_level;
	uint8_t seleccion;
} cambios_pantalla_t;





void Board_UTFT_Init(void);

void task_pantalla (void);
void task_pantalla_Init(void);
cambios_pantalla_t calcular_cambios(void);
void organizar (void (*funciones_pantalla[])(uint8_t*));

void write_acople (uint8_t *state);
void write_trigger_pol (uint8_t *state);
void write_trigger_level (uint8_t *state);
void write_fdt (uint8_t *state);
void write_fdv (uint8_t *state);
void write_T(uint8_t *);
void write_signal(uint8_t *);




#endif /* SRC_TASKS_TASK_PANTALLA_H_ */
