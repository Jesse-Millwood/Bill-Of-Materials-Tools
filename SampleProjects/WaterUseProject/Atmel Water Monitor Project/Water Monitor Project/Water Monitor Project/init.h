/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	init.h											 
 *  																	 
 *																		 
 * Target Architecture: Atmega168PA									 
 *																		 
 * Description:																	 
 *																		 
 *																		 
 *****************************************************************************/
#ifndef INIT_H_
#define INIT_H_

#define F_CPU 16000000UL

 // Define the Macros for the INPUT and OUTPUT of the AVR Pins
 #define OUTPUT 1
 #define INPUT 0
 #define TRUE 1
 #define FALSE 0
 #define ACTIVE 1
 #define INACTIVE 0
 #define DItank 2
 #define KYtank 3

 // Define pins that interface with the world
 #define BUTTON				PD3
 #define STATUS_LED			PD4		
 // Macros
 #define S_LED_ON			(PORTD |= (1<<STATUS_LED))
 #define S_LED_OFF			(PORTD &= ~(1<<STATUS_LED))
 #define S_LED_TOG			(PORTD ^= (1<<STATUS_LED))
 /// Read and store state of Tactile Switch
 #define BUTTON_RD			(PIND&(1<<BUTTON))

// Defines 
#define SWHOLD 100
// Defines for eePROMsave function
#define CYCLES	1
#define GALS	2
#define THRESH	3
#define ALL		4
// Global flag bit fields
typedef struct  
{
	unsigned tactswON : 1;
	unsigned tacthold : 1;
	unsigned encswON  : 1;
	unsigned enchold  : 1;
	
}flags;

typedef struct 
{
	unsigned time1ms	: 1;
	unsigned time5ms	: 1;
	unsigned time10ms	: 1;
	unsigned time1sec	: 1;
	unsigned oneSecflg	: 1;
}tflags;

// Global Variables
uint8_t swTimerCntr;
flags swFlags;
tflags t;
tflags LED;
volatile uint16_t timeBaseCount;
volatile uint16_t timeLEDcount;

// Function Prototypes
 void init(void);
 void check_SW_State(void);
 void check_timers(void);
 void check_Alarm(void);
 void eePROMinit(void);
 void eePROMsave(uint8_t choice);

 #endif