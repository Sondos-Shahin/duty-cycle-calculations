/*
 * external_interrupt.c
 *
 *  Created on: Jul 20, 2021
 *      Author: sondos
 */

#include "external_interrupt.h"

static volatile void (*INT0_callBack_Ptr)(void) = NULL;
static volatile void (*INT1_callBack_Ptr)(void) = NULL;
static volatile void (*INT2_callBack_Ptr)(void) = NULL;

                                       /*ISR*/



ISR(INT0_vect)
{
	if(INT0_callBack_Ptr != NULL)
	{

		(*INT0_callBack_Ptr)();
	}
}


ISR(INT1_vect)
{
	if(INT1_callBack_Ptr != NULL)
	{

		(*INT1_callBack_Ptr)();
	}
}

ISR(INT2_vect)
{
	if(INT2_callBack_Ptr != NULL)
	{

		(*INT2_callBack_Ptr)();
	}
}


       /*function to take a pointer of the needed function in main and pass it to the ISR function*/

void External_Interrupt_Set_CallBack(Interrupt_Type INT_Type,  void(*Function_ptr)(void))
{
if(INT_Type==INT_0){INT0_callBack_Ptr = Function_ptr;}
else if(INT_Type==INT_1){INT1_callBack_Ptr = Function_ptr;}
else if(INT_Type==INT_2){INT2_callBack_Ptr = Function_ptr;}// or we will use just else
}







void External_Interrupt_Init(const External_Interrupt_Configuration* Config_Ptr)
{
	if(Config_Ptr->INT_Type==INT_0)
	{
		DDRD=CLEAR_BIT(DDRD, PD2);
		MCUCR = (MCUCR & 0XFC) | (Config_Ptr->INT_control) ;
		GICR = (GICR& 0XBF) | (1<<INT0);
		if(Config_Ptr->INT_Pull_up_option==ENABLE)
		{
			PORTD = SET_BIT(PORTD,  PD2);
		}
	}
	else if(Config_Ptr->INT_Type==INT_1)
	{

		DDRD=CLEAR_BIT(DDRD, PD3);
		MCUCR = (MCUCR & 0XF3) |((Config_Ptr->INT_control)<<2) ;
		GICR = (GICR& 0X7F) | (1<<INT1);
		if(Config_Ptr->INT_Pull_up_option==ENABLE)
		{
			PORTD = SET_BIT(PORTD,  PD3);
		}
	}
	else if(Config_Ptr->INT_Type==INT_2)
	{

		DDRB=CLEAR_BIT(DDRB, PB2);
		MCUCSR = (MCUCSR & 0XBF) | ( ((Config_Ptr->INT_control) & 0X01)<< ISC2) ;
		GICR = (GICR& 0XCF) | (1<<INT2);
		if(Config_Ptr->INT_Pull_up_option==ENABLE)
		{
			PORTB = SET_BIT(PORTB,  PB2);
		}
	}// or we will use just else

}






void External_Interrupt_Deinit(Interrupt_Type INT_Type)
{

	if(INT_Type==INT_0)
	{
		// MCUCR = ( MCUCR & 0XFC);
		 MCUCR=CLEAR_BIT(MCUCR,ISC00);
		 MCUCR=CLEAR_BIT(MCUCR,ISC01);
		// GICR = (GICR & 0XBF);
		 GICR=CLEAR_BIT( GICR,INT0);

	}
	else if(INT_Type==INT_1)
	{
		// MCUCR = ( MCUCR & 0XF3);
		 MCUCR=CLEAR_BIT(MCUCR,ISC10);
		 MCUCR=CLEAR_BIT(MCUCR,ISC11);
		// GICR = (GICR & 0X7F);
		 GICR=CLEAR_BIT( GICR,INT1);
	}
	else if(INT_Type==INT_2)
	{
		//MCUCSR = (MCUCSR & 0XBF);
		MCUCSR=CLEAR_BIT(MCUCSR,ISC2);
	//	GICR = (GICR & 0XCF);
		 GICR=CLEAR_BIT( GICR,INT2);
	}// or we will use just else

}




