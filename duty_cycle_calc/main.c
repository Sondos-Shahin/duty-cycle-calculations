/**********************************************************************************
 * [FILE NAME]: main.c
 *
 * [AUTHOR]: Sondos Ahmed Eladl Mohamed
 *
 * [DATE CREATED]: july 20, 2021
 *
 * [Description]: app to determine the duty cycle of a waveform
 *
 ***********************************************************************************/


#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include"Timer.h"
#include"external_interrupt.h"
#include "lcd.h"


#define FIRST_EDGE        1
#define SECOND_EDGE       2
#define THIRD_EDGE        3
#define FOURTH_EDGE       4


uint8 edge_Counter = 0;
uint16 High_time = 0;
uint16 Period_time = 0;
uint16 total_time = 0;

void EdgeDetector(void);


int main(void)
{
	uint32 dutyCycle = 0;
	SREG |= (1<<7);

	LCD_init();

	External_Interrupt_Configuration edge= {INT_0, Raising,DISABLE};


	Timer_Configuration timer= {0,0, Timer_1, F_CPU_CLOCK, Overflow, 0};
	TimerInit(&timer);


	External_Interrupt_Set_CallBack(INT_0, EdgeDetector);
	External_Interrupt_Init(&edge);





	while(1)
	{

		if(edge_Counter == 4)
		{
			TimerDeInit(Timer_1);
			External_Interrupt_Deinit(INT_0);

			edge_Counter = 0;
			LCD_displayString("Duty Cycle= ");
			/* calculate the dutyCycle */
			dutyCycle = ((float)(total_time-Period_time) / (total_time - High_time)) * 100;
			LCD_intgerToString(dutyCycle);
			LCD_displayCharacter('%');
		}

	}


}






void EdgeDetector()
{
	edge_Counter++;


	if(edge_Counter == FIRST_EDGE)
	{


		External_Interrupt_Configuration edge= {INT_0,Falling,DISABLE};
		External_Interrupt_Set_CallBack(INT_0,EdgeDetector );
		External_Interrupt_Init(&edge);
        TCNT1=0;
	}

	else if(edge_Counter == SECOND_EDGE)
	{


		External_Interrupt_Configuration edge= {INT_0,Raising,DISABLE};
		External_Interrupt_Set_CallBack(INT_0,EdgeDetector );
		External_Interrupt_Init(&edge);
        High_time=  TCNT1;

	}

	else if(edge_Counter == THIRD_EDGE)
	{


		External_Interrupt_Configuration edge= {INT_0,Falling,DISABLE};
		External_Interrupt_Set_CallBack(INT_0,EdgeDetector );
		External_Interrupt_Init(&edge);
        Period_time = TCNT1;
	}


	else if(edge_Counter == FOURTH_EDGE)
	{

		External_Interrupt_Configuration edge= {INT_0,Raising,DISABLE};
		External_Interrupt_Set_CallBack(INT_0,EdgeDetector );
		External_Interrupt_Init(&edge);
        total_time = TCNT1;
		TCNT1=0;
	}


}


























