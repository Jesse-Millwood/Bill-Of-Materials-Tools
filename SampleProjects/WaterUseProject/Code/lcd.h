/*-----------------------------------------------------------------------------|
 * File Name:		lcd.h                                                      |
 * Title:			LCD Header File for ST7066U LCD Charcter Display Controller|
 * Author:			Jesse Millwood											   |
 * Target MCU:		Atmel AVR Series                                           |
 * Editor Tab Size:	4                                                          |
 *																			   |
 * Description:		This code is meant to include function declarations and    |
 * 					macro definitions common to LCD Character Displays   	   |
 *					controlled by the ST7066U LCD Controller				   |
 ******************************************************************************/
#include <avr/io.h>

 #ifndef LCD_H
 #define LCD_H

 // Define Global Macros For LCD Pin Assignments
 #define LCD_RS_PIN 	REGISTER_BIT(PINB,2)
 #define LCD_R_W_PIN 	REGISTER_BIT(PINB,1)
 #define LCD_E_PIN		REGISTER_BIT(PIND,7)
 #define LCD_DB0_PIN	REGISTER_BIT(PIND,6)
 #define LCD_DB1_PIN	REGISTER_BIT(PIND,5)
 #define LCD_DB2_PIN	REGISTER_BIT(PINC,0)
 #define LCD_DB3_PIN	REGiSTER_BIT(PINC,1)
 #define LCD_DB4_PIN	REGISTER_BIT(PINC,2)
 #define LCD_DB5_PIN	REGISTER_BIT(PINC,3)
 #define LCD_DB6_PIN	REGISTER_BIT(PINC,4)
 #define LCD_DB7_PIN	REGISTER_BIT(PINC,5)

 // Define Direction of pins 
 #define LCD_RS_DIR 	REGISTER_BIT(DDRB,2)
 #define LCD_R_W_DIR 	REGISTER_BIT(DDRB,1)
 #define LCD_E_DIR		REGISTER_BIT(DDRD,7)
 #define LCD_DB0_DIR	REGISTER_BIT(DDRD,6)
 #define LCD_DB1_DIR	REGISTER_BIT(DDRD,5)
 #define LCD_DB2_DIR	REGISTER_BIT(DDRC,0)
 #define LCD_DB3_DIR	REGiSTER_BIT(DDRC,1)
 #define LCD_DB4_DIR	REGISTER_BIT(DDRC,2)
 #define LCD_DB5_DIR	REGISTER_BIT(DDRC,3)
 #define LCD_DB6_DIR	REGISTER_BIT(DDRC,4)
 #define LCD_DB7_DIR	REGISTER_BIT(DDRC,5)


 
 // Function Prototypes
 void command(char i);
 void write(char i);
 void init();




 #endif
