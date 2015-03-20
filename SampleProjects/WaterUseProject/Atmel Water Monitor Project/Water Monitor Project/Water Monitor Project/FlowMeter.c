/*
 * FlowMeter.c
 *
 * Created: 2/18/2014 1:49:01 PM
 *  Author: Magnum Laptop1
 */ 

#include "includes.h"

void FLOW_init(void)
{
	// Initialize Flowmeter Globals
	FLOW_indicator.threshold_met = 0;
	FLOW_indicator.state = INACTIVE;
	FLOW_indicator.active_toggle1s = 0;
	FLOW_indicator.incrementcyclesflag = 0;
	
	FLOW_gallonThreshold = 2;
	FLOW_DIgalThreshold = 2;
	FLOW_KYgalThreshold = 2;
	// Activate Pull-up for Flow Sensor
	PORTB	|= (1<<FLOW_SENSOR_PIN);
	
	// Enable pin change interrupt and configure
	PCICR	|= (1<<PCIE0);
	PCMSK0	|= (1<<PCINT0); 
	
	
	// Initialize a timer to keep track of the time between falling edges
	// Timer 1, 16-bit, CTC mode(OCR1A)
	// Divided by 256
	// increments every 16us, overflows every 1.049s
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	// Interrupt 
	TIMSK1 |= (1<<OCIE1A);
	
	// set OCR1A to be hit once every second
	OCR1A = 62500;
	
	// Initialize FLOW meter variables
	FLOW_gals = 0;
	FLOW_DIgals = 0;
	
	FLOW_DIcycles = 0;
	FLOW_KYgals = 0;
	FLOW_KYcycles = 0;
	FLOW_freq = 0;
	FLOW_pcount = 0;
	FLOW_idlecount = 15;
	FLOW_idlecount_mins = 0;
}

void check_FLOW(void)
{
	// Check the if the threshold has been met
	if((FLOW_DIgals >= FLOW_DIgalThreshold) || (FLOW_KYgals >= FLOW_KYgalThreshold))
	{
		FLOW_indicator.threshold_met = 1;
	}
	else
	{
		FLOW_indicator.threshold_met = 0;
	}
	
	if ((FLOW_idlecount <= 10) && (FLOW_freq>=10))
	{
		// Flow meter has been idle for less than 10 seconds
		FLOW_idlecount_mins = 0;
		FLOW_indicator.incrementcyclesflag = 1;
	}
	else
	{
		// Flow meter has been idle for more than 2 seconds
		if (FLOW_idlecount >= 75)
		{
			// Prevent idle count from overflowing and incrementing cycle count
			FLOW_idlecount = 15;
			FLOW_idlecount_mins ++;
			
		}
	}
	if((FLOW_idlecount_mins >= INCREMENT_TIMEOUT) && FLOW_indicator.incrementcyclesflag)
	{
		// Increment cycles after timeout and don't increment at timeout again
		// unless flowmeter is active again
		FLOW_indicator.incrementcyclesflag = 0;
		FLOW_idlecount_mins = 0;
		FLOW_DIcycles ++;
		FLOW_KYcycles ++;
		// Save cycles and gallons variables at cycle increment
		eePROMsave(CYCLES);
		eePROMsave(GALS);
	}
	
}

ISR(PCINT0_vect)
{ 
	if(FLOWSIG_RD)
	{
		// If the interrupt is triggered and the Flow meter signal is 
		// high then one period has occurred
		FLOW_pcount++;
	}
}

ISR(TIMER1_COMPA_vect) 
{
	// The OCIE1A interrupt should be activated once every second
	// This is to determine how many pulses have occurred from the
	// flow meter every second, essentially calculating the frequency
	// in hertz (pulses/second)
	
	FLOW_freq = FLOW_pcount;
	FLOW_indicator.active_toggle1s ^=1;
	// do not divide by zero
	if(FLOW_freq>0)
	{
		FLOW_DIgals += ((float)FLOW_freq/K_FACTOR);
		FLOW_KYgals += ((float)FLOW_freq/K_FACTOR);
		FLOW_idlecount = 0;
		FLOW_indicator.state = ACTIVE;
	}
	else
	{
		// Flow meter is idle
		FLOW_idlecount ++;
		FLOW_indicator.state = INACTIVE;
	}
	// reset the pulse counter.
	FLOW_pcount = 0;
	 
}