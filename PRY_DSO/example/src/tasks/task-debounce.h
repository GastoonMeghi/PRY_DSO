/*
 * task-debounce.h
 *
 *  Created on: 18 dic. 2019
 *      Author: ordonezt
 */

#ifndef SRC_TASKS_TASK_DEBOUNCE_H_
#define SRC_TASKS_TASK_DEBOUNCE_H_

#include "my_board.h"

#define OK_PORT			0			/*BTN1*/
#define OK_PIN			4			/*BTN1*/

#define PLUS_PORT		4			/*BTN2*/
#define PLUS_PIN		28			/*BTN2*/

#define MINUS_PORT		0			/*BTN3*/
#define MINUS_PIN		2			/*BTN3*/

#define SEL_PORT		0			/*BTN4*/
#define SEL_PIN			3			/*BTN4*/

#define CPL1_PORT		2
#define CPL1_PIN		13

#define CPL2_PORT		0
#define CPL2_PIN		11

#define CPL3_PORT		0
#define CPL3_PIN		10

#define VSEN11_PORT		0
#define VSEN11_PIN		1

#define VSEN12_PORT		0
#define VSEN12_PIN		0

#define VSEN13_PORT		1
#define VSEN13_PIN		29

#define VSEN21_PORT		3
#define VSEN21_PIN		26

#define VSEN22_PORT		0
#define VSEN22_PIN		27

#define VSEN23_PORT		0
#define VSEN23_PIN		28

#define NO_KEYS	0
#define N_KEYS	13
#define MIN_TIME_KEYS 	6/2		// el tiempo de estabilizacion son 6ms pero el tick es de 2 ms
#define	ONE_KEY_MASK	0x0001

#define BIS(x,i)	(x >> i) & ONE_KEY_MASK			//BIT IS SET

typedef struct{
	bool state;
	bool was_pressed;
	bool was_release;
}key_t;

typedef enum{
	OK,
	PLUS,
	MINUS,
	SEL,
	CPL1,
	CPL2,
	CPL3,
	VSEN11,
	VSEN12,
	VSEN13,
	VSEN21,
	VSEN22,
	VSEN23
}dso_keys_t;

extern key_t Key[N_KEYS];

void task_debounce(void);
uint16_t getKeys(void);
void InitDebounce(void);
#endif /* SRC_TASKS_TASK_DEBOUNCE_H_ */
