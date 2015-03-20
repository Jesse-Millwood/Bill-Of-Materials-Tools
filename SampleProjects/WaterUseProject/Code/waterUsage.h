/*-----------------------------------------------------------------------------/
 * File Name: 		waterUsage.h                                               | 
 * Title: 			Water Usage Project Header File                            | 
 * Author:			Jesse Millwood                                             | 
 * Target MCU:		Atmel AVR Series                                           | 
 * Editor Tab Size: 4                                                          | 
 *                                                                             | 
 * Description:		This code is meant to include function declarations and    |
 * 					macro definitions needed for the Water Usage Device Project|
 ******************************************************************************/

 #ifndef WATERUSAGE_H
 #define WATERUSAGE_H

 /* Define the direction of and the pin that interfaces with the AVR and
  * the Omega Engineering FTB4705 Flow Sensor.
  * Define the pull-up of the pin that interfaces between the AVR and the 
  * Flow sensor*/
 #define WU_FLOW_SENSOR_PIN		REGISTER_BIT(PINB,0)
 #define WU_FLOW_SENSOR_DIR		REGISTER_BIT(DDRB,0)
 #define WU_FLOW_SENSOR_PORT	REGISTER_BIT(PORTB,0)



 /* Define the direction of and the pin that interfaces with the AVR and
  * the momentary tactile push button switch. 
  * Define the pullup of the pin that interfaces between the AVR and the 
  * momentary tactile push button switch*/
 #define WU_BUTTON_PIN			REGISTER_BIT(PIND,3)
 #define WU_BUTTON_DIR			REGISTER_BIT(DDRD,3)
 #define WU_BUTTON_PORT			REGISTER_BIT(PORTD,3)

 /* Define the direction of and the pin that interfaces with the AVR and
  * the status LED
  * Define the pullup of the pin that interfaces between the AVR and the 
  * momentary status LED*/
 #define WU_STATUS_LED_PIN		REGISTER_BIT(PIND,4)
 #define WU_STATUS_LED_DIR		REGISTER_BIT(DDRD,4)
 #define WU_STATUS_LED_PORT		REGISTER_BIT(PORTD,4)

 


 #endif