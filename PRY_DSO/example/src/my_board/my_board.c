/*
 * my_board.c
 *
 *  Created on: 17 oct. 2019
 *      Author: Tomás Ordóñez
 */

#include "my_board.h"

uint16_t sample_buffer[SAMPLE_BUFFER_LENGHT] = {0};
uint8_t sample_buffer_flag = 0;
ADC_CLOCK_SETUP_T ADCSetup;

void InitPWM(void)
{
	//Paso 1
	if(!Chip_Clock_IsPeripheralClockEnabled(SYSCTL_CLOCK_PWM1))
		Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PWM1);

	//Paso 2
	Chip_Clock_SetPCLKDiv(SYSCTL_CLOCK_PWM1,SYSCTL_CLKDIV_4); //25MHz
}

void ConfigPWM(void)
{
	Chip_PWM_SetPrescale(25);	//1MHz

	Chip_PWM_CountMode(PWM_TIMER, 0);

	Chip_PWM_SetMatchControl(MATCH0, M_RESET);

	//Se debe establecer el periodo del PWM (Match 0) antes de habilitarlo si no, no arranca
	Chip_PWM_SetMatch(MATCH0, PWM_FREQ);

	//Habilito el latch haciendo efectivo los cambios en el match
	Chip_PWM_LatchEnable(MATCH0);

	//Reseteo la cuenta
	Chip_PWM_CounterReset(ENABLE);

	//PWM listo para ser encendido y funcionar
}

void PWM_SetFreq(uint32_t freq)
{
	uint32_t ticks;

	ticks = ((Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_PWM1) / Chip_PWM_GetPrescale())) / freq;

	Chip_PWM_SetMatch(MATCH0, ticks);

	Chip_PWM_LatchEnable(MATCH0);
}

void PWM_SetDuty(uint8_t output, float duty)
{
	uint32_t ticks;

	ticks = (duty * Chip_PWM_GetMatch(MATCH0)) / MAX_DUTY;

	Chip_PWM_SetMatch(output, ticks);

	Chip_PWM_LatchEnable(output);
}

float PWM_GetDuty(uint8_t output)
{
	//duty numero entre 0 y MAX_DUTY
	//Asumo funcionamiento en single edge => output = match

	return (Chip_PWM_GetMatch(output) / Chip_PWM_GetMatch(MATCH0)) * MAX_DUTY;
}

void PWM_TurnOn(void)
{
	//Habilito el contador y lo saco del estado de reset
	Chip_PWM_CounterEnable(ENABLE);
	Chip_PWM_CounterReset(DISABLE);

	//Habilito el PWM
	Chip_PWM_Enable(ENABLE);
}

void InitPWM1(uint32_t duty)
{
	PWM_SetDuty(PWM1, duty);

	PWM_TurnOn();

	//Habilito la salida
	Chip_PWM_OutputEnable(PWM1, ENABLE);
}

void setTriggerLvl(float lvl)
{
	float duty;

	if(lvl > -MAX_TRIGGER_LVL && lvl < MAX_TRIGGER_LVL)
	{
		duty = (lvl + MAX_TRIGGER_LVL) / (2 * MAX_TRIGGER_LVL);
		PWM_SetDuty(PWM1, duty);
	}
}

void InitADC(void)
{
	/*Entrada de ADC*/
//	Chip_IOCON_PinMuxSet(LPC_IOCON, ADC_PORT, ADC_PIN, IOCON_FUNC1|IOCON_MODE_INACT); //Entrada de ADC P0.23 con funcion 1
//	/*ADC Init */
//	Chip_ADC_Init(LPC_ADC, &ADCSetup);
//	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_ADC,SYSCTL_CLKDIV_1);
//	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);	//Lo pongo en modo burst (Conversiones repetitivas)
//	ADCSetup.burstMode = TRUE;
//	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);	//Habilito la interrupcion del canal
//	Chip_ADC_Int_SetChannelCmd(LPC_ADC, 8, DISABLE); //Pongo 0 en ADGINTEN por q estoy en modo burst
//	NVIC_EnableIRQ(ADC_IRQn); //Habilito las interrupciones del ADC en el NVIC

	/*Potenciometro*/
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 31, IOCON_FUNC3|IOCON_MODE_INACT); //Entrada de ADC con func3
	/*ADC Init */
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_ADC,SYSCTL_CLKDIV_1);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);	//Lo pongo en modo burst (Conversiones repetitivas)
	ADCSetup.burstMode = TRUE;
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);	//Habilito la interrupcion del canal
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, 8, DISABLE); //Pongo 0 en ADGINTEN por q estoy en modo burst
	NVIC_EnableIRQ(ADC_IRQn); //Habilito las interrupciones del ADC en el NVIC
}

void InitLed(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, 2, 3, IOCON_FUNC1|IOCON_MODE_INACT);	//LED R como PWM14
	InitPWM();
	ConfigPWM();

	PWM_TurnOn();
	//Habilito la salida
	Chip_PWM_OutputEnable(PWM4, ENABLE);
}
void InitTriggerPWM(void)
{
//	Chip_IOCON_PinMuxSet(LPC_IOCON, TRIGGER_OUT_PORT, TRIGGER_OUT_PIN, IOCON_FUNC2|IOCON_MODE_INACT);	//P1.23 como PWM14
//
//	InitPWM();
//	ConfigPWM();
//	PWM_TurnOn();
//
//	//Habilito la salida
//	Chip_PWM_OutputEnable(PWM4, ENABLE);


	Chip_IOCON_PinMuxSet(LPC_IOCON, 2, 3, IOCON_FUNC1|IOCON_MODE_INACT);	//LED R como PWM14

	InitPWM();
	ConfigPWM();
	PWM_TurnOn();

	//Habilito la salida
	Chip_PWM_OutputEnable(PWM4, ENABLE);
}
void InitTriggerInt(void)
{
	//Entrada trigger
//	Chip_GPIOINT_Init(LPC_GPIOINT); //Habilita el clock a los GPIO
//	Chip_IOCON_PinMuxSet(LPC_IOCON, TRIGGER_IN_PORT, TRIGGER_IN_PIN, IOCON_FUNC0|IOCON_MODE_REPEATER); //Configuro como GPIO repetidor
//	Chip_GPIO_SetPinDIRInput(LPC_GPIO, TRIGGER_IN_PORT, TRIGGER_IN_PIN);	//Configuro como entrada

//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_IN_PIN); //Limpio interrupciones previas por las dudas
//	Chip_GPIOINT_SetIntRising(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_IN_PIN); //Habilito interrupcion por rising edge
//	NVIC_EnableIRQ(EINT3_IRQn);	//Habilito interrupcion en el NVIC

	//SW2
	Chip_GPIOINT_Init(LPC_GPIOINT); //Habilita el clock a los GPIO
	Chip_IOCON_PinMuxSet(LPC_IOCON, TRIGGER_IN_PORT, 18, IOCON_FUNC0|IOCON_MODE_REPEATER); //Configuro como GPIO repetidor
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, TRIGGER_IN_PORT, 18);	//Configuro como entrada

	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18); //Limpio interrupciones previas
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18); //Int rising edge
	NVIC_EnableIRQ(EINT3_IRQn);	//Habilito interrupcion en el NVIC

}

void EINT3_IRQHandler(void)
{
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_PIN); //Limpio el flag de interrupcion para que no vuelva a interrumpir
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18); //Limpio BORRAR

//	Chip_GPIOINT_SetIntRising(LPC_GPIOINT, GPIOINT_PORT0, 0); //Deshabilito todas las int
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 0); //Deshabilito todas las int BORRAR

//	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, 100000);	//100KHz

	Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL, ENABLE);	//Habilito el canal para convertir
}

void ADC_IRQHandler(void)
{
	static uint16_t sample_index = 0;

//	if(flagCambios == 1)
//	{
//		sample_index = 0;
//		Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL, DISABLE);	//Deshabilito el canal y dejo de muestrear
//	}

	Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL, sample_buffer + sample_index);

	sample_index++;
	if(!(sample_index %= SAMPLE_BUFFER_LENGHT))
	{
		sample_buffer_flag = 1;
		Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL, DISABLE);	//Deshabilito el canal y dejo de muestrear
	}

}

void startSampling(void)
{
	setTriggerLvl(0);
	setTriggerEdge(RISING);
	setSampleRate(1000);
}

void setTriggerEdge(trigger_edge_t edge)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_IN_PIN); //Limpio interrupciones previas por las dudas

	if(edge == RISING)
		Chip_GPIOINT_SetIntRising(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_IN_PIN); //Habilito interrupcion por rising edge
	else
		Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 1 << TRIGGER_IN_PIN); //Habilito interrupcion por falling edge
}

void setSampleRate(uint32_t sampleRate)
{
	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, sampleRate);	//100KHz
}
