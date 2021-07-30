/*
 * Timer_config.h
 *
 *  Created on: Jul 18, 2021
 *      Author: sondos
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define CLEAR_CLOCK_VALUE        0XF8
#define NULL   (void*)0

typedef enum
{
	Timer_0,Timer_1,Timer_2
}Timer_Type;


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;


typedef enum
{
	Overflow,Compare
}Timer_Mode;


typedef enum
{
	Channel_A, Channel_B
}Channel_Type;

typedef struct
{
	uint16 timer_Initial_Value;
	uint16 timer_Match_Value;
	Timer_Type  timer_type;
	Timer_Clock timer_clk;
	Timer_Mode  timer_mode;
	Channel_Type compare_register;

}Timer_Configuration;


      /******************************functions prototype********************************/
void TimerInit(const Timer_Configuration * Configuration_Ptr);
void TimerSetCallBack( Timer_Type  timer_type,void(*Function_ptr)(void) );
void TimerStop(Timer_Type timer_type);
void TimerDeInit(Timer_Type timer_type);

#endif /* TIMER_H_ */
