/*************************************************************************
Title:    testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://jump.to/fleury
Date:     December 2002
Software: AVR-GCC 3.3
Hardware: HD44780 compatible LCD text display
          ATS90S8515/ATmega if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
// modified to test extensions 
// by Martin Thomas, 3/2003

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "lcd.h"


/*
** constant definitions
*/


/*
** function prototypes
*/ 
void wait_until_key_pressed(void);


void wait_until_key_pressed(void)
{
    unsigned char i, j;
    

    do {
        loop_until_bit_is_clear(PINA,PINA7);     /* wait until key is pressed */
        
        for (i=0;i<255;i++) for (j=0;j<255;j++); /* debounce */
            
        if (bit_is_clear(PINA,PINA7)) break;
    } while (1);
    loop_until_bit_is_set(PINA,PINA7);            /* wait until key is released */
 
}

void mydelay(unsigned char v)
{
	unsigned char j;
	unsigned int i;
	for (j=0;j<v;j++) for (i=0;i<2000;i++) asm volatile ("nop"::);
}

#define demomode 1
#define demodelay 200

#ifdef demomode
int main(void)
{
	////unsigned char pos; 
	unsigned char i;
	char buffer[5];
	
	DDRA &= ~(1<<PA7); // cbi(DDRA,PA7); /* Pin PA7 input */
    PORTA |= (1<<PA7); // sbi(PORTA,PA7);/* Pin PA7 pull-up enabled */

	DDRB=0xFF;	// dbg only
	PORTB=0x88; // dbg only

    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);

    for (;;) {                           /* loop forever */
        /* 
         * Test 1:  write text to display
         */
    
        /* clear display and home cursor */
        lcd_clrscr();
        
        /* put string to display (line 1) with linefeed */
        lcd_puts("LCD Test Line 1 a little longer very long longer and long and long very long line this one\n");
		
		mydelay(demodelay);
		lcd_scrollup();
		mydelay(demodelay);
		
		lcd_clrscr();
		for (i='!';i<='z';i++) {
			lcd_putc(i);
			mydelay(20);
		}
		mydelay(demodelay);
		for (i='!';i<='z';i++) lcd_putc(i);
		mydelay(demodelay);
		/*
		for (i=0;i<40;i++) {
			lcd_command(LCD_MOVE_DISP_LEFT);
			// mydelay(40);
			wait_until_key_pressed();
		}
		wait_until_key_pressed();
		*/
		
		
		lcd_clrscr();
		lcd_gotoxy(0,0);
		for (i=0;i<LCD_LINES*3;i++) {
			itoa(i+1, buffer, 10);
			lcd_puts(buffer);
			lcd_puts(".line\n");
			mydelay(200);
		}
		mydelay(demodelay);
		
		lcd_clrscr();
		lcd_puts("Line 1\n");
		lcd_puts("Line 2\n");
		lcd_puts("Line 3\n");
		lcd_puts("Line 4");
		mydelay(demodelay);
		lcd_puts("Line 12345678901234567890");
		mydelay(demodelay);
		mydelay(demodelay);
		
		for (i=0;i<LCD_LINES-1;i++) {
			lcd_scrollup();
			mydelay(100);
		}
		
		lcd_scrollup();
		lcd_command(LCD_DISP_ON_CURSOR_BLINK);
		
		mydelay(demodelay);
				
		lcd_clrscr();
		lcd_gotoxy(0,0);
        lcd_puts("Line 1");
		mydelay(demodelay);
		lcd_gotoxy(0,1);
		lcd_puts("Line 2");
		///pos = lcd_waitbusy();   // read busy-flag and address counter
		///PORTB=pos;
		mydelay(demodelay);
		lcd_gotoxy(0,3);
		mydelay(demodelay);
		lcd_puts("Line 4");
		mydelay(demodelay);
		lcd_gotoxy(0,2);
		lcd_puts("Line 3");
		mydelay(demodelay);
		
		 /* move cursor to position 7 on line 2 */
        lcd_gotoxy(7,3);  
        
        /* write single char to display */
        lcd_putc(':');
		
        /* wait until push button PD2 (INT0) is pressed */
        mydelay(demodelay);
        
        
        /*
         * Test 2: use lcd_command() to turn on cursor
         */
        
        /* turn on cursor */
        //lcd_command(LCD_DISP_ON_CURSOR);
		lcd_command(LCD_DISP_ON_CURSOR_BLINK);

        /* put string */
        lcd_puts( "CurOn");
		lcd_gotoxy(8,3);  
        
        /* wait until push button PD2 (INT0) is pressed */
        mydelay(demodelay);// wait_until_key_pressed();


        /*
         * Test 3: display shift
         */
        
        lcd_clrscr();     /* clear display home cursor */

        /* put string from program memory to display */
        lcd_puts_P( "Line 1 longer than 14 characters" );
		mydelay(demodelay);
        lcd_puts_P( "and also Line 2 longer than 14 characters and even more" );
        mydelay(demodelay);
		
        /* move BOTH lines one position to the left */
        //lcd_command(LCD_MOVE_DISP_LEFT);
        
        /* wait until push button PD2 (INT0) is pressed */
        mydelay(demodelay);

		/* 
		lcd_clrscr();
		lcd_puts_P( "Hey Thomas!     Drueck mal auf  den SW7 Knopf!" );
		wait_until_key_pressed();
		lcd_clrscr();
		lcd_puts_P( "Machst auch alles was man Dir sagt he?");
		wait_until_key_pressed();
		*/

        /* turn off cursor */
        lcd_command(LCD_DISP_ON);
        
    }
}
#else	
int main(void)
{
	////unsigned char pos; 
	unsigned char i;
	char buffer[5];
	
    cbi(DDRA,PA7); /* Pin PA7 input */
    sbi(PORTA,PA7);/* Pin PA7 pull-up enabled */

	DDRB=0xFF;	// dbg only
	PORTB=0x88; // dbg only

    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);

    for (;;) {                           /* loop forever */
        /* 
         * Test 1:  write text to display
         */
    
        /* clear display and home cursor */
        lcd_clrscr();
        
        /* put string to display (line 1) with linefeed */
        lcd_puts("LCD Test Line 1 a little longer very long longer and long and long very long line this one\n");
		wait_until_key_pressed();
		
		lcd_scrollup();
		wait_until_key_pressed();
		
		lcd_command(LCD_DISP_ON_CURSOR_BLINK);
		
		lcd_clrscr();
		for (i='!';i<='z';i++) {
			lcd_putc(i);
			mydelay(20);
		}
		wait_until_key_pressed();
		
		/*
		for (i=0;i<40;i++) {
			lcd_command(LCD_MOVE_DISP_LEFT);
			// mydelay(40);
			wait_until_key_pressed();
		}
		wait_until_key_pressed();
		*/
		
		
		lcd_clrscr();
		lcd_gotoxy(0,0);
		for (i=0;i<LCD_LINES*3;i++) {
			itoa(i+1, buffer, 10);
			lcd_puts(buffer);
			lcd_puts(".line\n");
			mydelay(200);
			// wait_until_key_pressed();
		}
		wait_until_key_pressed();
		
		lcd_clrscr();
		lcd_puts("Line 1\n");
		lcd_puts("Line 2\n");
		lcd_puts("Line 3\n");
		lcd_puts("Line 4");
		wait_until_key_pressed();
		lcd_puts("Line 12345678901234567890");
		wait_until_key_pressed();
		
		for (i=0;i<LCD_LINES-1;i++) {
			lcd_scrollup();
			mydelay(100);
		}
		
		lcd_scrollup();
		wait_until_key_pressed();
				
		lcd_clrscr();
		lcd_gotoxy(0,0);
        lcd_puts("Line 1");
		wait_until_key_pressed();
		lcd_gotoxy(0,1);
		lcd_puts("Line 2");
		///pos = lcd_waitbusy();   // read busy-flag and address counter
		///PORTB=pos;
		wait_until_key_pressed();
		lcd_gotoxy(0,3);
		wait_until_key_pressed();
		lcd_puts("Line 4");
		wait_until_key_pressed();
		lcd_gotoxy(0,2);
		lcd_puts("Line 3");
		wait_until_key_pressed();
		
		
        /* move cursor to position 8 on line 2 */
        lcd_gotoxy(7,1);  
        
        /* write single char to display */
        lcd_putc(':');
        
		 /* move cursor to position 8 on line 2 */
        lcd_gotoxy(7,2);  
        
        /* write single char to display */
        lcd_putc(':');
		
		 /* move cursor to position 8 on line 2 */
        lcd_gotoxy(7,3);  
        
        /* write single char to display */
        lcd_putc(':');
		
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();
        
        
        /*
         * Test 2: use lcd_command() to turn on cursor
         */
        
        /* turn on cursor */
        //lcd_command(LCD_DISP_ON_CURSOR);
		lcd_command(LCD_DISP_ON_CURSOR_BLINK);

        /* put string */
        lcd_puts( "CurOn");
		lcd_gotoxy(8,3);  
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();


        /*
         * Test 3: display shift
         */
        
        lcd_clrscr();     /* clear display home cursor */

        /* put string from program memory to display */
        lcd_puts_P( "Line 1 longer than 14 characters" );
		wait_until_key_pressed();
        lcd_puts_P( "and also Line 2 longer than 14 characters and even more" );
        wait_until_key_pressed();
		
        /* move BOTH lines one position to the left */
        //lcd_command(LCD_MOVE_DISP_LEFT);
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();

        /* turn off cursor */
        lcd_command(LCD_DISP_ON);
        
    }
}
#endif

