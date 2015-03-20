/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	init.c											 
 *  																	 
 *																		 
 * Target Architecture: Atmega168PA									 
 *																		 
 * Description:																	 
 *																		 
 *																		 
 *****************************************************************************/

 #include "includes.h"
 
 // EEPROM Locations
 #define	DIcyclesLOC 0x00
 #define	KYcyclesLOC 0x08
 
 #define	DIgalLOC	0x10
 #define	KYgalLOC	0x30
 
 #define	DIthreshLOC	0x50
 #define	KYthreshLOC	0x70
 


 void init(void)
 {
	 // Initialize Flags Variables
	 swFlags.tactswON = 0;
	 swFlags.tacthold = 0;
	 swFlags.encswON  = 0;
	 swFlags.enchold  = 0;
	 // Initialize timer flags
	 t.time1ms	= 0;
	 t.time5ms	= 0;
	 t.time10ms	= 0;
	 t.time1sec = 0;
	 t.oneSecflg = 0;
	 
	 LED.time1ms	= 0;
	 LED.time5ms	= 0;
	 LED.time10ms	= 0;
	 LED.time1sec	= 0;
	 LED.oneSecflg  = 0;
	 
	 
	 timeBaseCount = 0;
 	// Set Directions For Interface pins
 	// PORT D OTUPUTS
 	DDRD = (1<<STATUS_LED);
	// Activate Pull-up for tactile switch, making it active low
	PORTD |= (1<<BUTTON) ;
	
	// Pin Change Interrupt Enable 2
	PCICR |= (1<<PCIE2);
	// Pin Change Enable Mask
	PCMSK2 |= (1<<PCINT16) | (1<<PCINT19);
	
	// Enable and configure a counter for button hold time
	// CTC mode clock divided by 1024
	// 16Mhz/1024 = 15.63kHz -> period: 64us
	TCCR0A |= (1<<WGM01) ;
	TCCR0B |= (1<<CS02) | (1<<CS00);
	// Counter0 output compare match A Interrupt Enabled
	TIMSK0 |= (1<<OCIE0A);
	// Compare Interrupt should activate every 1ms
	OCR0A = 16;
	
	eePROMinit();
 }
 
 void check_SW_State(void)
 {
	 // pull up resistors are activated on buttons, they are active low
	 // 1ms debounce
	 swFlags.tactswON = ((!BUTTON_RD) && (t.time1ms)) ?	1 : 0;
	 swFlags.encswON  = ((!ENC_SW_RD) && (t.time1ms)) ? 1 : 0;
	
	if(swFlags.encswON && t.time1sec)
	{
		swFlags.enchold = 1;
	}
	else if(!swFlags.encswON)
	{
		swFlags.enchold = 0;
	}
	
	if(swFlags.tactswON && t.time1sec)
	{
		swFlags.tacthold = 1;
	}
	else if(!swFlags.tactswON)
	{
		swFlags.tacthold = 0;
	}
 }
 
 void check_timers(void)
 {
	 // check the base counter and set or clear the respective
	 // bits in the bit field
	 t.time1ms	= (timeBaseCount >= 1)		? 1 : 0;
	 t.time5ms	= (timeBaseCount >= 5)		? 1 : 0;
	 t.time10ms	= (timeBaseCount >= 10)		? 1 : 0;
	 t.time1sec	= (timeBaseCount >= 1000)	? 1 : 0;
	 
	 // check the LED counter and set or clear the respective
	 // bits in the bit field
	 LED.time1ms	= (timeLEDcount>= 1)		? 1 : 0;
	 LED.time5ms	= (timeLEDcount >= 5)		? 1 : 0;
	 LED.time10ms	= (timeLEDcount >= 10)		? 1 : 0;
	 LED.time1sec	= (timeLEDcount >= 1000)	? 1 : 0;
	 
	 if (LED.time1sec)
	 {
		 LED.oneSecflg = 1;
	 }
	 // if the base counter is above 1000 (1sec) then clear it
	 // as it is useless at that point
	 if(timeBaseCount>=1000)
	 {
		 timeBaseCount = 0;
		 t.oneSecflg = 1;
	 }
	 if(timeLEDcount>=1000)
	 {
		 LED.oneSecflg = 1;
		 timeLEDcount = 0;
	 }
 }

void check_Alarm (void)
{	
	uint8_t LEDseconds;
	
	
	
	if (LED.oneSecflg && (state == STATE_mainmenu))
	{
		Display_Tank_Alert(DItank);
		Display_Tank_Alert(KYtank);
	}

	
	if(FLOW_indicator.threshold_met)
	{
		// threshold has been met
		if(LED.oneSecflg)
		{
			// toggle led on one second flag 
			LEDseconds ++;
			LED.oneSecflg = 0;
			S_LED_TOG;
		}
	}
	
	
	else if (state == STATE_mainmenu)
	{
		LEDseconds = 0;
		S_LED_OFF;
	}
}


void eePROMinit(void)
{
	FLOW_DIcycles = eeprom_read_byte((uint8_t*)DIcyclesLOC);
	FLOW_KYcycles = eeprom_read_byte((uint8_t*)KYcyclesLOC);
	
	FLOW_DIgals = eeprom_read_float((float*)DIgalLOC);
	FLOW_KYgals = eeprom_read_float((float*)KYgalLOC);
	
	FLOW_DIgalThreshold = eeprom_read_float((float*)DIthreshLOC);
	FLOW_KYgalThreshold = eeprom_read_float((float*)KYthreshLOC);
	
}

void eePROMsave(uint8_t choice)
{
	if((choice == CYCLES) || (choice == ALL))
	{
		eeprom_update_byte((uint8_t*)DIcyclesLOC,FLOW_DIcycles);
		eeprom_update_byte((uint8_t*)KYcyclesLOC, FLOW_KYcycles);
	}
	
	if((choice == GALS) || (choice == ALL))
	{
		eeprom_update_float((float*)DIgalLOC, FLOW_DIgals);
		eeprom_update_float((float*)KYgalLOC, FLOW_KYgals);
	}
	
	if ((choice == THRESH) || (choice == ALL))
	{
		eeprom_update_float((float*)DIthreshLOC, FLOW_DIgalThreshold);
		eeprom_update_float((float*)KYthreshLOC, FLOW_KYgalThreshold);
	}

}

/*
 * Interrupt activated when there is a pin change on any of the devices 
 * connected to PCINT16,PCINT17,PCINT18, or PCINT19 these devices are:
 * PD0 (PCINT16)		: ENC_SW
 * PD1 (PCINT17)		: ENC_CH_B
 * PD2 (PCINT18, INT0)	: ENC_CH_A
 * PD3 (PCINT19)		: BUTTON
 */

ISR(PCINT2_vect)
{
	// Reset timer if activity is sensed on either button
	TCNT0 = 0;
}

ISR(TIMER0_COMPA_vect)
{
	// OCR0A is 16, Interrupt should activate every 1ms
	// If either button is active then increment base counter
	// else clear it
	if((!BUTTON_RD) || (!ENC_SW_RD))
		timeBaseCount ++;
	else
		timeBaseCount = 0;
		
	timeLEDcount ++;
}