/*
 * statemachine.h
 *
 * Created: 2/20/2014 9:46:21 AM
 *  Author: Magnum Laptop1
 */ 


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

// Enumerate States
#define STATE_mainmenu			1
#define STATE_thresholdmenu		2


// Function Prototypes
void statemachine_init(void);
void statemachine(void);
void mainmenuState(void);
void thresholdmenuState(void);

// Globals
uint8_t state;

#endif /* STATEMACHINE_H_ */