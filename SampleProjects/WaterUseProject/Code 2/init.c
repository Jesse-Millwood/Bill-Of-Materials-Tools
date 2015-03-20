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

 void init(void)
 {
 	// Set Directions For Interface pins
 	// PORT B OUTPUTS
 	DDRB |= (1<<LCD_RS_PIN)|(1<<LCD_R_W_PIN);
 	// PORT B INPUTS
 	DDRB &= ~(1<<FLOW_SENSOR_PIN);
 	
 	// PORT C OTUPUTS
 	DDRC |= (1<<LCD_DB2_PIN)|(1<<LCD_DB3_PIN)|(1<<LCD_DB4_PIN)|(1<<LCD_DB5_PIN)|
 			(1<<LCD_DB6_PIN)|(1<<LCD_DB7_PIN);
 	
 	// PORT D OTUPUTS
 	DDRD |= (1<<STATUS_LED);
 	// PORT D INPUTS
 	DDRD &= ~(1<<BUTTON) & ~(1<<ENC_SW) & ~(1<<ENC_CH_A) & ~(1<<ENC_CH_B);

 	// Activate Pull-ups
 	PORTB |= (1<<FLOW_SENSOR_PIN);

 }
