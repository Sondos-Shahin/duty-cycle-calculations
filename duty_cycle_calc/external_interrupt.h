/*
 * external_interrupt.h
 *
 *  Created on: Jul 20, 2021
 *      Author: sondos
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_



#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


#define NULL   (void*)0
#define ENABLE                                  1
#define DISABLE                                 0





typedef enum
{

INT_0, INT_1, INT_2

}Interrupt_Type;


typedef enum
{

Low_level, Any_logical, Falling, Raising

}Interrupt_Control;


typedef struct
{
	Interrupt_Type  INT_Type;
	Interrupt_Control INT_control;
	uint8 INT_Pull_up_option;

}External_Interrupt_Configuration;




       /********************functions prototype*****************************/

void External_Interrupt_Set_CallBack(Interrupt_Type INT_Type, void(*function_ptr)(void) );
void External_Interrupt_Init(const External_Interrupt_Configuration* Config_Ptr);
void External_Interrupt_Deinit(Interrupt_Type INT_Type);

#endif /* EXTERNAL_INTERRUPT_H_ */
