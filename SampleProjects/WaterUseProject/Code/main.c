/*-----------------------------------------------------------------------------/
 * File Name: 		Main.c                                                     | 
 * Title: 			Main File For The Water Usage Monitor Device               | 
 * Author:			Jesse Millwood                                             | 
 * Target MCU:		Atmel AVR Series                                           | 
 * Editor Tab Size: 4                                                          | 
 *                                                                             | 
 * Description:		This code is meant to monitor the Omega Engineering FTB4705| 
 *                  Flow Sensor. It then displays information to the character |
 *					LCD Screen. The user interacts with the device via a rotary|
 *					encoder with a built in switch and a tactile switch. The   |
 * 					microcontroller has one LED for status indications		   |
 ******************************************************************************/

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "main.h"
 #include "global.h"
 #include "lcd.h"
 #include "waterUsage.h"
 #include "encoder.h"

 int main (void)
 {
 	init_port_directions();
 	init_pullups();
 	init_interrupts();

 	// Main program loop
 	while(1)
 	{

 	}

 	return 0;
 }

 int init_port_directions(void)
 {
 	ENCODER_CH_A_DIR 	= INPUT;
 	ENCODER_CH_B_DIR 	= INPUT;
 	ENCODER_SW_DIR		= INPUT;

 	WU_BUTTON_DIR		= INPUT;
 	WU_STATUS_LED_DIR	= OUTPUT;
 	WU_FLOW_SENSOR_DIR	= INPUT;

	LCD_RS_DIR 			= OUTPUT;
	LCD_R_W_DIR			= OUTPUT;
	LCD_E_DIR			= OUTPUT;
	LCD_DB0_DIR			= OUTPUT;
	LCD_DB1_DIR			= OUTPUT;
	LCD_DB2_DIR			= OUTPUT;
	LCD_DB3_DIR			= OUTPUT;
	LCD_DB4_DIR			= OUTPUT;
	LCD_DB5_DIR			= OUTPUT;
	LCD_DB6_DIR			= OUTPUT;
	LCD_DB7_DIR			= OUTPUT;

	return 0;
 }

 int init_pullups(void)
 {
 	// Turn on Pullup for Flow sensor
 	WU_FLOW_SENSOR_PORT = ACTIVE;

 	return 0;
 }

 int init_interrupts(void)
 {

 	return 0;
 }

 




