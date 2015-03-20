/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	main.c											 
 *  																	 
 *																		 
 * Target Architecture: ATmega 168PA									 
 *																		 
 * Description:															 
 *																		 
 *																		 
 *****************************************************************************/

#include "includes.h"

int main(void)
{
	init();				// Initialize general IO that is not otherwise contianed in its own lib
	LCDinit();			// init LCD bit, dual line, cursor right
	WelcomeMessage();	// Welcome Display
	Encoder_init();		// init the encoder 
	FLOW_init();		// init the flow meter
	statemachine_init();// init the statemachine 
	LCDclr();			// clears LCD
	
	LCDclr();
	
	sei();
	while(1)//loop demos
	{
		check_FLOW();
		check_timers();
		check_SW_State();
		check_Alarm();
		statemachine();
	}
	return 0;
}
