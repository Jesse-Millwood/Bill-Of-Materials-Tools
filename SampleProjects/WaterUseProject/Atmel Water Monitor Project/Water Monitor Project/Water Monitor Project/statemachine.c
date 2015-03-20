/*
 * statemachine.c
 *
 * Created: 2/20/2014 9:45:30 AM
 *  Author: Magnum Laptop1
 */ 
#include "includes.h"


void statemachine_init(void)
{
	// Initialize the state
	state = STATE_mainmenu;
}

void statemachine (void)
{
	switch(state)
	{
		case(STATE_mainmenu):
			mainmenuState();
			break;
		case(STATE_thresholdmenu):
			thresholdmenuState();
			break;
		default:
			mainmenuState();
			break;
	}
}

void mainmenuState(void)
{
	MainDisplay();
	InfoDisplay(FLOW_DIcycles,FLOW_KYcycles,FLOW_DIgals,FLOW_KYgals);
	if ((FLOW_indicator.state == ACTIVE) && (FLOW_freq >= 10))
	{
		// If the flow meter is active display the flow animation
		Display_flow_animation(ACTIVE);
	}
	else 
	{
		// If the flow meter is not active do not show animation
		Display_flow_animation(INACTIVE);
	}
	
	// check hold state of tactile button to select and clear tank displays
	if (swFlags.tacthold)
	{
		Display_Tank_selector(ACTIVE);
	}
	else
	{
		Display_Tank_selector(INACTIVE);
	}

	// check hold state of encoder button to switch to threshold select display
	if(swFlags.enchold && !swFlags.tactswON)
	{
		// only encoder switch was held down
		state = STATE_thresholdmenu;
		S_LED_ON;
		// Initialize Encoder direction flags before going into Threshold display
		ENC.turnLeft = 0;
		ENC.turnRight = 0;
		swFlags.tacthold = 0;
		swFlags.enchold = 0;
		swFlags.encswON = 0;
		swFlags.tactswON = 0;
		// clear lcd once before going to next display
		LCDclr();
	}

	else
	{
		state = STATE_mainmenu;
	}
}

void thresholdmenuState(void)
{
	ThresholdSelectDisplay();
	
	// Check hold state of tactile button to switch back to main display
	if(swFlags.tacthold)
	{
		eePROMsave(THRESH);
		state = STATE_mainmenu;
		// clear tact hold state so that it does not interfere with next state
		swFlags.tacthold = 0;
		S_LED_OFF;
		// clear once before transitioning to next display
		LCDclr();
	}
	else
	{
		state = STATE_thresholdmenu;
	}
}