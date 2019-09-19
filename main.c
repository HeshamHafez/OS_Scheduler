/******************************************************************************
 *
 * Module: OS Scheduler APP
 *
 * File Name: main.c
 *
 * Description: Source file of OS Scheduler App Code
 *
 * Created on: Sep 16, 2019
 *
 * Author: Hesham Hafez
 *
 *******************************************************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "scheduler.h"
#include "DIO.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void RedLed(void);
void GreenLed(void);
void BlueLed(void);

/*******************************************************************************
 *                             Main Function                                   *
 *******************************************************************************/
int main (void)
{
	DIO_SetPinDirection(DIO_PIN12,OUTPUT);
	DIO_SetPinDirection(DIO_PIN13,OUTPUT);
	DIO_SetPinDirection(DIO_PIN14,OUTPUT);
	SOS_Init();
	SET_BIT(SREG,I);
	SOS_CreateTask(PRIORITY_0,1000,RedLed);
	SOS_CreateTask(PRIORITY_1,2000,GreenLed);
	SOS_CreateTask(PRIORITY_2,3000,BlueLed);
	SOS_Run();
}

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/
void RedLed(void)
{

	static uint8 red_led = 0u;
	red_led ^= 1u;
	if(red_led == 1u)
	{
		DIO_WritePin(DIO_PIN12,HIGH);
	}
	else
	{
		DIO_WritePin(DIO_PIN12,LOW);
	}


}
void GreenLed(void)
{
	static uint8 counter = 0;
	static uint8 green_led = 0u;
	green_led ^= 1u;
	if(green_led == 1u)
	{
		DIO_WritePin(DIO_PIN13,HIGH);
	}
	else
	{
		DIO_WritePin(DIO_PIN13,LOW);
	}
	counter++;
	if(counter == 6)
	{
		SOS_DeleteTask(RedLed);
		SOS_DeleteTask(BlueLed);
	}
}
void BlueLed(void)
{
	static uint8 blue_led = 0u;
	blue_led ^= 1u;
	if(blue_led == 1u)
	{
		DIO_WritePin(DIO_PIN14,HIGH);
	}
	else
	{
		DIO_WritePin(DIO_PIN14,LOW);
	}

}
