/*-----------------------------------------------------------------------------/
 * File Name: 		main.h                                                     | 
 * Title: 			main Header File                                           | 
 * Author:			Jesse Millwood                                             | 
 * Target MCU:		Atmel AVR Series                                           | 
 * Editor Tab Size: 4                                                          | 
 *                                                                             | 
 * Description:		This code is meant to include function declarations and    |
 * 					macro definitions needed for the main file of the Water    |
 *					Usage Device Project                                       |
 ******************************************************************************/


#ifndef MAIN_H
#define MAIN_H
// Structure and Macro Function that allows the pin to be defined
 // as a variable
 typedef struct
 {
 	unsigned int bit0:1;
 	unsigned int bit1:1;
 	unsigned int bit2:1;
 	unsigned int bit3:1;
 	unsigned int bit4:1;
 	unsigned int bit5:1;
 	unsigned int bit6:1;
 	unsigned int bit7:1;
 } _io_reg;

 #define REGISTER_BIT(reg,bt) ((volatile _io_reg*)&reg)->bit##bt

 // Define the Macros for the INPUT and OUTPUT of the AVR Pins
 #define OUTPUT 1
 #define INPUT 0
 #define TRUE 1
 #define FALSE 0
 #define ACTIVE 1
 #define INACTIVE 0

 // Function Prototypes
 int init_port_directions(void);
 int init_pullups(void);
 int init_interrupts(void);

 #endif