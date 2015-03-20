/*
 * LCDmessages.h
 *
 * Created: 2/10/2014 11:14:33 AM
 *  Author: Magnum Laptop1
 */ 


#ifndef LCDMESSAGES_H_
#define LCDMESSAGES_H_

void delay1s(void);
void progress(void);
void demoanimation(uint8_t* incrementflag);
void WelcomeMessage(void);
void MainDisplay(void);
void InfoDisplay(	int8_t count_cycleDI, int8_t count_cycleKZN,
					float count_galnsDI,  float count_galnsKZN);
void displayAB(void);
void ThresholdSelectDisplay(void);
void Display_flow_animation(uint8_t activity);
void Display_Tank_selector(uint8_t activity);
void Display_Tank_Alert(uint8_t Tank);


#endif /* LCDMESSAGES_H_ */