/******************************************************************************
 * Name: Jesse Millwood													 
 * 																		
 * File Name: 	lcd.h											 
 *  																	 
 *																		 
 * Target Architecture: Atmega168PA									 
 *																		 
 * Description:																	 
 *																		 
 *																		 
 *****************************************************************************/
#ifndef LCD_H_
#define LCD_H_

 #define LCD_RS_PIN 		PB2
 #define LCD_R_W_PIN		PB1
 #define LCD_E_PIN			PD7
 #define LCD_DB0_PIN		PD6
 #define LCD_DB1_PIN		PD5
 #define LCD_DB2_PIN		PC0
 #define LCD_DB3_PIN		PC1
 #define LCD_DB4_PIN		PC2
 #define LCD_DB5_PIN		PC3
 #define LCD_DB6_PIN		PC4
 #define LCD_DB7_PIN		PC5

#define LCD_RS_PIN_HIGH		(PORTB |= (1<<LCD_RS_PIN))    			 
#define LCD_R_W_PIN_HIGH	(PORTB |= (1<<LCD_R_W_PIN))    			
#define LCD_E_PIN_HIGH  	(PORTD |= (1<<LCD_E_PIN))  					
#define LCD_DB0_PIN_HIGH	(PORTD |= (1<<LCD_DB0_PIN))    			
#define LCD_DB1_PIN_HIGH	(PORTD |= (1<<LCD_DB1_PIN))    			
#define LCD_DB2_PIN_HIGH	(PORTC |= (1<<LCD_DB2_PIN))    			
#define LCD_DB3_PIN_HIGH	(PORTC |= (1<<LCD_DB3_PIN))    			
#define LCD_DB4_PIN_HIGH	(PORTC |= (1<<LCD_DB4_PIN))    			
#define LCD_DB5_PIN_HIGH	(PORTC |= (1<<LCD_DB5_PIN))    			
#define LCD_DB6_PIN_HIGH	(PORTC |= (1<<LCD_DB6_PIN))    			
#define LCD_DB7_PIN_HIGH	(PORTC |= (1<<LCD_DB7_PIN))

#define LCD_RS_PIN_LOW		(PORTB &= ~(1<<LCD_RS_PIN))    			 
#define LCD_R_W_PIN_LOW		(PORTB &= ~(1<<LCD_R_W_PIN))    			
#define LCD_E_PIN_LOW	  	(PORTD &= ~(1<<LCD_E_PIN))  					
#define LCD_DB0_PIN_LOW		(PORTD &= ~(1<<LCD_DB0_PIN))    			
#define LCD_DB1_PIN_LOW		(PORTD &= ~(1<<LCD_DB1_PIN))    			
#define LCD_DB2_PIN_LOW		(PORTC &= ~(1<<LCD_DB2_PIN))    			
#define LCD_DB3_PIN_LOW		(PORTC &= ~(1<<LCD_DB3_PIN))    			
#define LCD_DB4_PIN_LOW		(PORTC &= ~(1<<LCD_DB4_PIN))    			
#define LCD_DB5_PIN_LOW		(PORTC &= ~(1<<LCD_DB5_PIN))    			
#define LCD_DB6_PIN_LOW		(PORTC &= ~(1<<LCD_DB6_PIN))    			
#define LCD_DB7_PIN_LOW		(PORTC &= ~(1<<LCD_DB7_PIN))       			

  // Function Prototypes
 void command(char i);
 void write(char i);
 void init();

#endif

