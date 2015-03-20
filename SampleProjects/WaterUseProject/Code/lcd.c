/*-----------------------------------------------------------------------------/
 * File Name: 		lcd.c 	                                                   | 
 * Title: 			LCD Source File                                            | 
 * Author:			Jesse Millwood                                             | 
 * Target MCU:		Atmel AVR Series                                           | 
 * Editor Tab Size: 4                                                          | 
 *                                                                             | 
 * Description:		This code is meant to be the implementation of the         |
 * 					functions prototyped in the lcd header file                |
 ******************************************************************************/

 #include <avr/io.h>
 #include <avr/delay.h>
 #include "lcd.h" 

 void command(char i)
 { 
 	P1  = i;       		// Put data on output        
 	D_I = 0;			// D/I = LOW : send instruction
 	R_W = 0;			// R/W = LOW : Write
 	E   = 1;			// 
 	_ms_delay(1)		// enable pulse width for greater than 300ns
 	E 	= 0; 
 }

 void write(char i)
 {
  	P1  = i;       		// Put data on output        
 	D_I = 1;			// D/I = LOW : send instruction
 	R_W = 0;			// R/W = LOW : Write
 	E   = 1;			// 
 	_ms_delay(1)		// enable pulse width for greater than 300ns
 	E 	= 0; 
 }

 void init()
 {
 	E 	= 0;
 	_ms_delay(100);		// wait more than 15 msec after power up
 	command(0x30);		// Command to Wake Up
 	_ms_delay(30);		// must wait more than 5 m sec
  	command(0x30);		// Command to Wake Up
 	_ms_delay(10);		// must wait more than 5 m sec
  	command(0x30);		// Command to Wake Up
 	_ms_delay(10);		// must wait more than 5 m sec
 	command(0x38);		// Command to set Function set: 8-bit/2-line
 	command(0x10);		// Command to Set Cursor
 	command(0x0c);		// Display ON, Cursor ON
 	command(0x06);		// Entry Mode Set
 }