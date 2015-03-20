/*
 * LCDmessages.c
 *
 * Created: 2/10/2014 11:02:54 AM
 *  Author: Magnum Laptop1
 */ 

#include "includes.h"

//Strings stored in AVR Flash memory
const uint8_t LCDwelcomeln1[]	PROGMEM="AVR LCD DEMO";
const uint8_t LCDprogress[]		PROGMEM="Loading...";
const uint8_t LCDanimation[]	PROGMEM="LCD animation";
const uint8_t Welcome[]			PROGMEM="Water Usage Monitor";
const uint8_t Tank1Title[]		PROGMEM="   DI:";
const uint8_t Tank2Title[]		PROGMEM="Kyzen:";
const uint8_t MsrmntHeader[]	PROGMEM="Cyls / Gals";
const uint8_t ThresholdSel[]	PROGMEM="Threshold Select";
const uint8_t Menu[]			PROGMEM="Menu:";

// additional custom LCD characters
const uint8_t backslash[8] PROGMEM=
{
	0b00000000,//back slash
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001,
	0b00000000,
	0b00000000
};

//delay 1s
void delay1s(void)
{
	uint8_t i;
	for(i=0;i<100;i++)
	{
		_delay_ms(10);
	}
}
//demonstration of progress bar
void progress(void)
{
	delay1s();
	CopyStringtoLCD(LCDprogress, 6, 2);
	for(uint8_t i=0;i<255;i++)
	{
		_delay_ms(10);
		LCDGotoXY(1, 3);
		LCDprogressBar(i, 255, 16);
	}
}
//demonstration of animation
void demoanimation(uint8_t* incrementflag)
{
	uint8_t xcoord,ycoord;
	xcoord = 1;
	ycoord = 1;
	LCDdefinechar(backslash,0);
	LCDGotoXY(xcoord,ycoord);
	
	switch (*incrementflag)
	{
		case 1:
			LCDsendChar('-');
			break;
		case 2:
			LCDsendChar('/');
			break;
		case 3:
			LCDsendChar('|');
			break;
		case 4:
			LCDsendChar(8);// backslash
			break;
		case 5:
			LCDsendChar('-');
			break;
		case 6:
			LCDsendChar('/');
			break;
		case 7:
			LCDsendChar('|');
			break;
		case 8:
			LCDsendChar(8);
			*incrementflag = 1;
			break;
		case 10:
			LCDsendChar(' ');
			break;
		default:
			LCDsendChar('/');
			break;
		
	}
	

}

void WelcomeMessage (void)
{
	LCDclr();
	CopyStringtoLCD(Welcome,0,0);
	progress();
	LCDclr();
}

void MainDisplay (void)
{
	CopyStringtoLCD(Welcome,0,0);
	CopyStringtoLCD(MsrmntHeader,8,1);
	CopyStringtoLCD(Tank1Title,1,2);
	CopyStringtoLCD(Tank2Title,1,3);
}

void InfoDisplay(	int8_t count_cycleDI, int8_t count_cycleKZN,
					float count_galnsDI,  float count_galnsKZN)
{
		char DIgals[7] = {};
		char KYgals[7] = {};
		// Convert floats to strings display thousands to tenths place word width
		// is set to be seven to accommodate the thousands, hundreds, and ones place,
		// the decimal point character, and the tenths.
		/*
			Special note about using sprintf to convert a float to a string:
			----------------------------------------------------------------
			In AVRstudio6.1 press Alt+F7 to bring up Project Properties, Under 
			"AVR/GNU Linker" press the "Libraries" option.
			In the "Libraries box press the "Add Item" button and type "printf_flt"
			this is equivalent to adding "-lprintf_flt" switch to the command line
			implementation of the gnu linker. 
			Now press the General option under "AVR/GNU Linker" and click the check
			mark for "Use vprintf library(-Wl,-u,vfprintf)"
			Also include the stdio.h library in the top header file for the project
			
			If this is not done sprintf will not work with float types. You will 
			most likely see a question mark on the LCD screen where you thought 
			a floating point number should be
		*/
		sprintf(DIgals,"%7.1f",count_galnsDI);
		sprintf(KYgals,"%7.1f",count_galnsKZN);
		
		
		// Display Tank1 cycle count thousandths
		LCDGotoXY(8,2);
		LCDsendChar(((char)(int)'0'+(count_cycleDI%10000/1000)));
		// Display Tank1 cycle count hundredths
		LCDGotoXY(9,2);
		LCDsendChar(((char)(int)'0'+(count_cycleDI%1000/100)));
		// Display Tank1 cycle count tens
		LCDGotoXY(10,2);
		LCDsendChar(((char)(int)'0'+(count_cycleDI%100/10)));
		// Display Tank1 cycle count ones
		LCDGotoXY(11,2);
		LCDsendChar(((char)(int)'0'+(count_cycleDI%10)));
		
		// Display DI tank floating point gallon count 
		LCDGotoXY(13,2);
		LCDstring(DIgals,7);
		
		// Display Tank2 cycle count thousandths
		LCDGotoXY(8,3);
		LCDsendChar(((char)(int)'0'+(count_cycleKZN%10000/1000)));
		// Display Tank2 cycle count hundredths
		LCDGotoXY(9,3);
		LCDsendChar(((char)(int)'0'+(count_cycleKZN%1000/100)));
		// Display Tank2 cycle count tens
		LCDGotoXY(10,3);
		LCDsendChar(((char)(int)'0'+(count_cycleKZN%100/10)));
		// Display Tank2 cycle count ones
		LCDGotoXY(11,3);
		LCDsendChar(((char)(int)'0'+(count_cycleKZN%10)));

		// Display Kyzen tank floating point gallon count
		LCDGotoXY(13,3);
		LCDstring(KYgals,7);
}

void displayAB(void)
{	
	/*
	// Display frequency for debug
	char freq[4]={};
	sprintf(freq,"%-4i",FLOW_freq);
	LCDGotoXY(0,1);
	LCDstring("F:",2);
	LCDGotoXY(2,1);
	LCDstring(freq,4);
	*/
	char localstring[1] = {};
	uint8_t useless_local;
	useless_local = (FLOW_indicator.threshold_met) ? 1 : 0;
	sprintf(localstring, "%1i",useless_local);
	LCDGotoXY(0,1);
	LCDstring("C:",2);
	LCDGotoXY(2,1);
	LCDstring(localstring,1);
	
}

void ThresholdSelectDisplay(void)
{
	static uint8_t tank;
	char DIThreshstring[18] = {};
	char KYThreshstring[20] = {};
	
	if(ENC.turnRight)
	{
		// clear turn right flag
		ENC.turnRight = 0;
		if(tank == DItank)
		{
			FLOW_DIgalThreshold ++;
		}
		
		else if(tank == KYtank)
		{
			FLOW_KYgalThreshold ++;
		}
	}
	
	else if(ENC.turnLeft)
	{
		// clear turn Left flag
		ENC.turnLeft = 0;
		if(tank == DItank)
		{
			if (FLOW_DIgalThreshold >= 1)
			{
				FLOW_DIgalThreshold --;
			}
			else
			{
				FLOW_DIgalThreshold = 0;
			}
			
		}
		
		else if(tank == KYtank)
		{
			if (FLOW_KYgalThreshold >= 1)
			{
				FLOW_KYgalThreshold --;
			}
			else
			{
				FLOW_KYgalThreshold = 0;
			}
			
		}
	}
	
	if (swFlags.encswON && t.oneSecflg)
	{
		t.oneSecflg = 0;
		tank = (tank == DItank)?KYtank:DItank;
	}
	
	if ((tank == KYtank) && (state == STATE_thresholdmenu))
	{
		LCDGotoXY(0,2);
		LCDsendChar(' ');
		LCDGotoXY(0,3);
		LCDsendChar(0b01111110);
		
	}
	else if ((tank == DItank) && (state == STATE_thresholdmenu))
	{
		LCDGotoXY(0,2);
		LCDsendChar(0b01111110);
		LCDGotoXY(0,3);
		LCDsendChar(' ');
	}
	
	
	sprintf(DIThreshstring,"DI:%7.1f Gals.",FLOW_DIgalThreshold);
	sprintf(KYThreshstring,"Kyzen:%7.1f Gals.",FLOW_KYgalThreshold);
	CopyStringtoLCD(ThresholdSel,0,0);
	CopyStringtoLCD(Menu,0,1);
	LCDGotoXY(4,2);
	LCDstring(DIThreshstring,16);
	LCDGotoXY(1,3);
	LCDstring(KYThreshstring,19);
	
}

void Display_flow_animation(uint8_t activity)
{
	static uint8_t animation_increment;
	
	if (activity == ACTIVE)
	{
		if(FLOW_indicator.active_toggle1s)
		{
			animation_increment = (animation_increment >= 8) ? 1 : animation_increment + 1;
		}
		else
		{
			animation_increment = (animation_increment >= 8) ? 1 : animation_increment;
		}
		
	}
	else if(activity == INACTIVE)
	{
		animation_increment = 10;
	}
	demoanimation(&animation_increment);
}

void Display_Tank_selector(uint8_t activity)
{
	static uint8_t xcoord,ycoordA,ycoordB,tank;
	xcoord = 0;
	if(ENC.turnRight || ENC.turnLeft)
	{
		// If the encoder turns either way reset the flag
		// and switch the y coordinate between the lines the 
		// two tanks are on
		ENC.turnLeft = 0;
		ENC.turnRight = 0;
		if (ycoordA == 2)
		{
			ycoordA = 3;
			ycoordB = 2;
			tank = KYtank;
		}
		else
		{
			ycoordA = 2;
			ycoordB = 3;
			tank = DItank;
		}
	}

	if (activity == ACTIVE)
	{
		LCDGotoXY(xcoord,ycoordA);
		LCDsendChar(0b01111110);
		LCDGotoXY(xcoord,ycoordB);
		LCDsendChar(' ');
		// If encoder switch is pressed clear the selected
		// tank gallon counter
		if(swFlags.encswON)
		{
			if(tank == DItank)
			{
				FLOW_DIgals = 0;
				FLOW_DIcycles = 0;
			}
			else if (tank == KYtank)
			{
				FLOW_KYgals = 0;
				FLOW_KYcycles = 0;
			}
		}
	}

	else if (activity == INACTIVE)
	{
		LCDGotoXY(xcoord,ycoordA);
		LCDsendChar(' ');
		LCDGotoXY(xcoord,ycoordB);
		LCDsendChar(' ');
		
	}
}

void Display_Tank_Alert(uint8_t Tank)
{
	uint8_t DIxcoord = 12;
	uint8_t DIycoord = 2;
	uint8_t KYxcoord = 12;
	uint8_t KYycoord = 3;
	if (Tank == DItank)
	{
		if (FLOW_DIgals >= FLOW_DIgalThreshold)
		{
			LCDGotoXY(DIxcoord,DIycoord);
			LCDsendChar('!');
		}
		else 
		{
			LCDGotoXY(DIxcoord,DIycoord);
			LCDsendChar(' ');
		}
		
	}
	if (Tank == KYtank)
	{
		if (FLOW_KYgals >= FLOW_KYgalThreshold)
		{
			LCDGotoXY(KYxcoord,KYycoord);
			LCDsendChar('!');
		}
		else
		{
			LCDGotoXY(KYxcoord,KYycoord);
			LCDsendChar(' ');
		}
		
	}
}