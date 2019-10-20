/*
 * my_board.h
 *
 *  Created on: 30 sep. 2019
 *      Author: Tomás Ordóñez
 */

#ifndef MY_BOARD_H_
#define MY_BOARD_H_

#include "board.h"
#include "board_api.h"
#include "my_chip.h"


#define	TRIGGER_OUT_PORT	1
#define TRIGGER_OUT_PIN		23

#define	TRIGGER_IN_PORT		0
#define TRIGGER_IN_PIN		24


#define ADC_CHANNEL ADC_CH5		//Cambiar por ADC_CH0 para leer la señal
#define SAMPLE_BUFFER_LENGHT 	300
#define ADC_PORT	0
#define ADC_PIN		23

extern uint16_t sample_buffer[SAMPLE_BUFFER_LENGHT];
extern uint8_t sample_buffer_flag;
extern ADC_CLOCK_SETUP_T ADCSetup;

typedef enum{RISING, FALLING}trigger_edge_t;

/**
 * @brief	Funcion de inicializacion del PWM
 * @return	Nothing
 * @note	Inicializacion basica:
 * 				1) Prender el periferico
 * 				2) Darle clock al periferico
 */
void InitPWM(void);

/**
 * @brief	Configura el modulo de PWM
 * @return	Nothing
 * @note	-
 */
void ConfigPWM(void);

/**
 * @brief	Setea la frecuencia de salida del PWM
 * @param	freq		: Frecuencia requerida
 * @return	Nothing
 * @note	-
 */
void PWM_SetFreq(uint32_t freq);

/**
 * @brief	Establece el duty de una salida de PWM
 * @param	output		: Salida objetivo del 1 al 6
 * @param	duty		: Ciclo de actividad
 * @return	Nothing
 * @note	duty numero entre 0 y MAX_DUTY
 * 			Asumo funcionamiento en single edge => output = match
 */
void PWM_SetDuty(uint8_t output, float duty);

/**
 * @brief	Devuelve el valor del duty de una salida de PWM
 * @param	output		: Salida objetivo del 1 al 6
 * @return	Duty
 * @note	Duty numero entre 0 y MAX_DUTY
 * 			Asumo funcionamiento en single edge => output = match
 */
float PWM_GetDuty(uint8_t output);

/**
 * @brief	Prende o saca del reposo al PWM
 * @param	Nothing
 * @return	Nothing
 * @note	-
 */
void PWM_TurnOn(void);

/**
 * @brief	Inicializa la salida PWM1 con determinado duty
 * @param	duty		: Ciclo de actividad
 * @return	Nothing
 * @note	duty numero entre 0 y MAX_DUTY
 */
void InitPWM1(uint32_t duty);

/**
 * @brief	Genera el PWM necesario para el nivel de trigger requerido
 * @param	lvl		: Valor signado de tension entre 1.650V y -1.650V
 * @return	Nothing
 * @note	-
 */
void setTriggerLvl(float lvl);

/**
 * @brief	Inicializa lo necesario para usar el ADC
 * @param	Nothing
 * @return	Nothing
 * @note	-
 */
void InitADC(void);

/**
 * @brief	Inicializa un led para PWM
 * @param	Nothing
 * @return	Nothing
 * @note	-
 */
void InitLed(void);

/**
 * @brief	Inicializa las interrupciones por GPIO
 * @param	Nothing
 * @return	Nothing
 * @note	-
 */
void InitTriggerInt(void);

/**
 * @brief	Inicializa la salida de trigger
 * @param	Nothing
 * @return	Nothing
 * @note	-
 */
void InitTriggerPWM(void);

void setSampleRate(uint32_t sampleRate);

void setTriggerEdge(trigger_edge_t edge);

void startSampling(float triggerLvl, trigger_edge_t edge, uint32_t sampleRate);
#endif /* MY_BOARD_H_ */
