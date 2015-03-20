/*-----------------------------------------------------------------------------/
 * File Name: 		encoder.h                                                  | 
 * Title: 			Encoder Header File                                        | 
 * Author:			Jesse Millwood                                             | 
 * Target MCU:		Atmel AVR Series                                           | 
 * Editor Tab Size: 4                                                          | 
 *                                                                             | 
 * Description:		This code is meant to include function declarations and    |
 * 					macro definitions needed for the use of rotary encoders    |
 ******************************************************************************/

 #ifndef ENCODER_H
 #define ENCODER_H
 
 /* Define the direction of and the pin that interfaces with the AVR and
  * the incremental rotary encoder with a built in tactile switch on the shaft.
  * Define the pull-up of the pin that interfaces between the AVR and the 
  * rotary encoder*/

 #define ENCODER_CH_A_PIN		REGISTER_BIT(PIND,2)
 #define ENCODER_CH_A_DIR		REGISTER_BIT(DDRD,2)
 #define ENCODER_CH_A_PORT		REGISTER_BIT(PORTD,2)

 #define ENCODER_CH_B_PIN		REGISTER_BIT(PIND,1)
 #define ENCODER_CH_B_DIR		REGISTER_BIT(DDRD,1)
 #define ENCODER_CH_B_PORT		REGISTER_BIT(PORTD,1)

 #define ENCODER_SW_PIN			REGISTER_BIT(PIND,0)
 #define ENCODER_SW_DIR			REGISTER_BIT(DDRD,0)
 #define ENCODER_SW_PORT		REGISTER_BIT(PORTD,0)



 #endif
