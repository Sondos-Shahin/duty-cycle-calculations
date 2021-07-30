/*
 * Timer_config.c
 *
 *  Created on: Jul 18, 2021
 *      Author: sondos
 */

#include "Timer.h"

static volatile void (*T0_callBack_Ptr)(void) = NULL;
static volatile void (*T1_callBack_Ptr)(void) = NULL;
static volatile void (*T2_callBack_Ptr)(void) = NULL;

                                       /*ISR for timer 0*/

ISR(TIMER0_OVF_vect)
{
	if(T0_callBack_Ptr != NULL)
	{

		(*T0_callBack_Ptr)();// calling the function from the main using pointer to function
	}
}

ISR(TIMER0_COMP_vect)
{
	if(T0_callBack_Ptr != NULL)
	{

		(*T0_callBack_Ptr)();// calling the function from the main using pointer to function
	}
}


                                     /*ISR for timer 1*/

ISR(TIMER1_OVF_vect)
{
	if(T1_callBack_Ptr != NULL)
	{

		(*T1_callBack_Ptr)(); // calling the function from the main using pointer to function
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(T1_callBack_Ptr != NULL)
	{

		(*T1_callBack_Ptr)(); // calling the function from the main using pointer to function
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(T1_callBack_Ptr != NULL)
	{

		(*T1_callBack_Ptr)(); // calling the function from the main using pointer to function
	}
}


                                     /*ISR for timer 2*/
ISR(TIMER2_OVF_vect)
{
	if(T2_callBack_Ptr != NULL)
	{

		(*T2_callBack_Ptr)(); //calling the function from the main using pointer to function
	}
}

ISR(TIMER2_COMP_vect)
{
	if(T2_callBack_Ptr != NULL)
	{

		(*T2_callBack_Ptr)(); //calling the function from the main using pointer to function
	}
}



       /*function to take a pointer of the needed function in main and pass it to the ISR function*/

void TimerSetCallBack(Timer_Type timer_type,  void(*Function_ptr)(void))
{
if(timer_type==Timer_0){T0_callBack_Ptr = Function_ptr;}
else if(timer_type==Timer_1){T1_callBack_Ptr = Function_ptr;}
else if(timer_type==Timer_2){T2_callBack_Ptr = Function_ptr;}// or we will use just else
}



         /*function to set the initial values for any timer type*/

void TimerInit(const Timer_Configuration * Configuration_Ptr){

	if(Configuration_Ptr->timer_type==Timer_0){

		TimerDeInit(Timer_0);// reset all registers
		TCNT0 = (Configuration_Ptr->timer_Initial_Value) & 0xFF;
		TCCR0 = (TCCR0  & CLEAR_CLOCK_VALUE) | (Configuration_Ptr->timer_clk);
		TCCR0  = CLEAR_BIT(TCCR0 ,  COM00);
		TCCR0  = CLEAR_BIT(TCCR0 ,  COM01);

        if(Configuration_Ptr->timer_mode== Overflow)
        {
        	TCCR0  = CLEAR_BIT(TCCR0 , WGM00);
        	TCCR0  = CLEAR_BIT(TCCR0 , WGM01);
        	TCCR0  = SET_BIT(TCCR0,FOC0);
        	TIMSK = SET_BIT(TIMSK, TOIE0);

        }
        else if(Configuration_Ptr->timer_mode==Compare)
        {
        TCCR0  = CLEAR_BIT(TCCR0 , WGM00);
        TCCR0  = SET_BIT(TCCR0 , WGM01);
        TCCR0  = SET_BIT(TCCR0,FOC0);
        OCR0 = ((Configuration_Ptr->timer_Match_Value)) & 0xFF;
        TIMSK = SET_BIT(  TIMSK, OCIE0);
        }
	}









	else if(Configuration_Ptr->timer_type==Timer_1){



	TimerDeInit(Timer_1);// reset all registers

	TCNT1 = (Configuration_Ptr->timer_Initial_Value) & 0xFFFF;
	TCCR1B =  (TCCR1B & CLEAR_CLOCK_VALUE) | (Configuration_Ptr->timer_clk);
	TCCR1A &= 0x0F;

	if(Configuration_Ptr->timer_mode== Overflow)
	        {
	        	TCCR1A  = CLEAR_BIT(TCCR1A , WGM10);
	        	TCCR1A  = CLEAR_BIT(TCCR1A , WGM11);
	        	TCCR1B  = CLEAR_BIT(TCCR1B , WGM12);
	            TCCR1B  = CLEAR_BIT(TCCR1B , WGM13);
	        	TCCR1A =  SET_BIT(TCCR1A,FOC1A);
	        	TCCR1A =  SET_BIT(TCCR1A,FOC1B);
                TIMSK= SET_BIT(TIMSK,TOIE1);


	        }
	        else if(Configuration_Ptr->timer_mode==Compare)
	        {
	       if(Configuration_Ptr->compare_register==Channel_A)
	       {

	    	                    TCCR1A  = CLEAR_BIT(TCCR1A , WGM10);
	    	   	             	TCCR1A  = CLEAR_BIT(TCCR1A , WGM11);
	    	   					TCCR1B = SET_BIT(TCCR1B, WGM12);
	    	   					TCCR1B = CLEAR_BIT(TCCR1B, WGM13);
                                TCCR1A =  SET_BIT(TCCR1A,FOC1A);
	    	   					TCCR1A =  SET_BIT(TCCR1A,FOC1B);
                                OCR1A = (Configuration_Ptr->timer_Match_Value) & 0xFFFF;
                                TIMSK = SET_BIT(TIMSK,OCIE1A);

	       }
	       else if(Configuration_Ptr->compare_register==Channel_B) //or just else
	       {
	    	    TCCR1A  = CLEAR_BIT(TCCR1A , WGM10);
            	TCCR1A  = CLEAR_BIT(TCCR1A , WGM11);
				TCCR1B = SET_BIT(TCCR1B, WGM12);
				TCCR1B = CLEAR_BIT(TCCR1B, WGM13);
				TCCR1A =  SET_BIT(TCCR1A,FOC1A);
			    TCCR1A =  SET_BIT(TCCR1A,FOC1B);
			    OCR1A = ((Configuration_Ptr->timer_Match_Value)+1) & 0xFFFF;
				OCR1B = (Configuration_Ptr->timer_Match_Value) & 0xFFFF;
                TIMSK = SET_BIT(TIMSK,OCIE1B);




	       }



	        }

}

	else if(Configuration_Ptr->timer_type==Timer_2){



	TimerDeInit(Timer_2);// reset all registers
	ASSR  &= 0X00;
	        TCNT2 = (Configuration_Ptr->timer_Initial_Value) & 0xFF;
			TCCR2  = (TCCR2  & CLEAR_CLOCK_VALUE) | (Configuration_Ptr->timer_clk);
			TCCR2  = CLEAR_BIT(TCCR2 ,  COM20);
			TCCR2  = CLEAR_BIT(TCCR2 ,  COM21);

	        if(Configuration_Ptr->timer_mode== Overflow)
	        {
	        	TCCR2  = CLEAR_BIT(TCCR2 , WGM20);
	        	TCCR2  = CLEAR_BIT(TCCR2 , WGM21);
	        	TCCR2  = SET_BIT(TCCR2,FOC2);
	        	TIMSK = SET_BIT(TIMSK, TOIE2);

	        }
	        else if(Configuration_Ptr->timer_mode==Compare)
	        {
	        TCCR2 = CLEAR_BIT(TCCR2 , WGM20);
	        TCCR2  = SET_BIT(TCCR2 , WGM21);
	        TCCR2  = SET_BIT(TCCR2,FOC2);
	        OCR2   = (Configuration_Ptr->timer_Match_Value) & 0xFF;
	        TIMSK  = SET_BIT(  TIMSK, OCIE2);
	        }
}




}

                          /*stop function to stop the timer from counting*/

void TimerStop(Timer_Type timer_type)// stop timer clk
{
	if(timer_type==Timer_0){TCCR0 = TCCR0  & CLEAR_CLOCK_VALUE ;}
	else if(timer_type==Timer_1){TCCR1B = TCCR1B  & CLEAR_CLOCK_VALUE ;}
	else if(timer_type==Timer_2){TCCR2 = TCCR2  & CLEAR_CLOCK_VALUE ;}// or we will use just else

}

                                /*de intializing   the timer registers       */

void TimerDeInit(Timer_Type timer_type)
{
	if(timer_type==Timer_0){
		TCNT0 =0x00;//timer 0 initial value register
		TCCR0 &=0x00;//timer 0 control register
		OCR0  &=0x00;//timer 0 o/p compare register
		TIMSK &=0x00;//timer 0 interrupt mask register
	}
	else if(timer_type==Timer_1){
		        TCNT1 =0x00;//timer 1 initial value register
				TCCR1A &=0x00;//timer 1 control register(A)
				TCCR1B &=0x00;//timer 1 control register(B)
				OCR1A  &=0x00;//timer 1 o/p compare register(A)
				OCR1B  &=0x00;//timer 1 o/p compare register(B)
				TIMSK  &=0x00;//timer 1 interrupt mask register(higher & lower)

	}
	else if(timer_type==Timer_2){
		TCNT2 =0x00;//timer 2 initial value register
		TCCR2 &=0x00;//timer 2 control register
		OCR2  &=0x00;//timer 2 o/p compare register
		TIMSK &=0x00;//timer 2 interrupt mask register
	}// or we will use just else

}


