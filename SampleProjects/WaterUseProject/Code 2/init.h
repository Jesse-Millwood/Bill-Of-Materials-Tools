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

 #include <avr/io.h>
 #include <inttypes.h>
 #include <util/delah.h>

 // Define the Macros for the INPUT and OUTPUT of the AVR Pins
 #define OUTPUT 1
 #define INPUT 0
 #define TRUE 1
 #define FALSE 0
 #define ACTIVE 1
 #define INACTIVE 0

 // Define pins that interface with the world
 #define FLOW_SENSOR_PIN 	PB0
 #define BUTTON				PD3
 #define STATUS_LED			PD4		
 #define ENC_CH_A			PD2
 #define ENC_CH_B			PD1
 #define ENC_SW				PD0

 void init(void);

 #endif