/*
 * task-main.h
 *
 *  Created on: 14 oct. 2019
 *      Author: Gaston
 */

#ifndef SRC_TASKS_TASK_MAIN_H_
#define SRC_TASKS_TASK_MAIN_H_

#define FLANCO_SEL 1
#define PLUS_PRESSED 1
#define MINUS_PRESSED 1
#define FLANCO_OK  1
#define FLANCO_SEL 1
#define CLEAN_FLANCO_SEL 1
#define CLEAN_FLANCO_OK 1

//***Modos del trigger*****
#define RISING_EDGE 1
#define FALLING_EDGE 0
//************************


typedef struct {
	uint32_t Vpp;
	uint32_t Veff;
	uint32_t Vm;
	uint32_t fs;
	uint32_t f;
	uint32_t T;
	uint8_t acople;
	uint32_t fdv;
	uint32_t fdt;
	float trigger_level;	/*	TODO  evaluar si conviene usar float o uint32 */
	trigger_edge_t trigger_pol;

	uint16_t signal[300];
} parametros_t;


void task_main (void);

void seleccion (void);
#endif /* SRC_TASKS_TASK_MAIN_H_ */
