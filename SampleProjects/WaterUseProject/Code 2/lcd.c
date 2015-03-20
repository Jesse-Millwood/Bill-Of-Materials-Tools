/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	lcd.c											 
 *  																	 
 *																		 
 * Target Architecture: Atmega 168pa									 
 *																		 
 * Description:															 
 *																		 
 *																		 
 *****************************************************************************/

 #include "includes.h"

 void command(char i)
 { 
 	P1  = i;       		// Put data on output        
 	LCD_RS_PIN_LOW;		// RS = LOW : send instruction
 	LCD_R_W_PIN_LOW;	// R/W = LOW : Write
 	LCD_E_PIN_HIGH;		// 
 	_ms_delay(1);		// enable pulse width for greater than 300ns
 	LCD_E_PIN_LOW;
 }

 void write(char i)
 {
  	P1  = i;       		// Put data on output        
 	LCD_RS_PIN_HIGH;	// RS = HIGH : send data
 	LCD_R_W_PIN_LOW;	// R/W = LOW : Write
 	LCD_E_PIN_HIGH;		// 
 	_ms_delay(1);		// enable pulse width for greater than 300ns
 	LCD_E_PIN_LOW; 
 }

 void init()
 {
 	LCD_E_PIN_LOW;
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