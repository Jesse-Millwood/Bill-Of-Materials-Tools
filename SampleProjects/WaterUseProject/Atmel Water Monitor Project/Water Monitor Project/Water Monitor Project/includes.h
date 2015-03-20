/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	lcd.h										 
 *  																	 
 *																		 
 * Target Architecture: Atmega 168pa									 
 *																		 
 * Description:															 
 *																		 
 *																		 
 *****************************************************************************/
 #ifndef INCLUDES_H_
 #define INCLUDES_H_

 #define F_CPU 16000000UL
 // C-standard libs
 #include <stdio.h>
 #include <string.h> 
 #include <inttypes.h>
 #include <math.h>
 // AVR libs
 #include <avr/io.h>
 #include <avr/pgmspace.h>
 #include <avr/interrupt.h>
 #include <avr/eeprom.h>
 #include <util/delay.h>
 // Project libs
 #include "init.h"
 #include "lcd_lib.h"
 #include "LCDmessages.h"
 #include "Encoder.h"
 #include "FlowMeter.h"
 #include "statemachine.h"
 
 volatile int8_t useless_global;

 #endif