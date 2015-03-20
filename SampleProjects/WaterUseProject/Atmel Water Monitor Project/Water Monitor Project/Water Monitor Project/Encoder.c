/*
 * Encoder.c
 *
 * Created: 2/12/2014 9:03:25 AM
 *  Author: Magnum Laptop1
 */ 
#include "includes.h"

void Encoder_init(void)
{
	// Initialize Encoder Flags
	ENC.turnLeft = 0;
	ENC.turnRight = 0;
	// Enable Pull ups on Encoder channels and switch
	PORTD |= (1<<ENC_CH_A) | (1<<ENC_CH_B) | (1<<ENC_SW); 
	
	// External Interrupt 0 Activated
	EIMSK |= (1<<INT0);
	// Interrupt Activated on falling edge of INT0 PIN
	EICRA |= (1<<ISC01);
}

/*
 * Interrupt activated when there is a pin change on any of the devices 
 * connected to PCINT16,PCINT17,PCINT18, or PCINT19 these devices are:
 * PD0 (PCINT16)		: ENC_SW
 * PD1 (PCINT17)		: ENC_CH_B
 * PD2 (PCINT18, INT0)	: ENC_CH_A
 * PD3 (PCINT19)		: BUTTON
 */


ISR(INT0_vect)
{
	/*
		This interrupt is for interfacing with the 
		TT Electronics Rotary Encoder	:	EN11-HSB1A15
						DIGIKEY PN		:	987-1186-ND
		This particular rotary encoder has the following operation 
		Clockwise Rotation:      Counter Clockwise Rotation:
		A--------     -----      ------		  -----  
		         |____|                |_____|
		B------		  -----      --------     -----
		       |_____|                   |____| 
		
		The encoder has pull up resistors on channel A and B. Channel C 
		is grounded and there is 0.1uF caps from Channel A and B pins to
		ground
	*/
	_delay_ms(1);
	if (ENC_RD==0b00)
	{
		// Encoder is turning clockwise
		// Channel A has transitioned from high to low
		// and the level of channel B is low
		_delay_ms(1);
		if (ENC_RD == 0b00)
		{
			ENC.turnRight = 1;
			ENC.turnLeft = 0;
		}
	}
	if(ENC_RD == 0b01)
	{
		// Encoder is turning counter clockwise
		// Channel A has transitioned from high to low
		// and the level of channel B is high
		_delay_ms(1);
		if(ENC_RD == 0b01)
		{
			ENC.turnRight = 0;
			ENC.turnLeft = 1;
		}
	}
}