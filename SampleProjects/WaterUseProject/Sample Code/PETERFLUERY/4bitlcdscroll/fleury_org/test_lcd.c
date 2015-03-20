/*************************************************************************
Title:    testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://jump.to/fleury
File:     $Id: test_lcd.c,v 1.3 2003/12/10 19:32:48 peter Exp $
Software: AVR-GCC 3.3
Hardware: HD44780 compatible LCD text display
          ATS90S8515/ATmega if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
#include <stdlib.h>
#include <avr/io.h>
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
        loop_until_bit_is_clear(PIND,PIND2);     /* wait until key is pressed */
        
        for (i=0;i<255;i++) for (j=0;j<255;j++); /* debounce */
            
        if (bit_is_clear(PIND,PIND2)) break;
    } while (1);
    loop_until_bit_is_set(PIND,PIND2);            /* wait until key is released */
 
}


int main(void)
{
    char buffer[7];
    int  num=134;
    
    DDRD &=~ (1 << PD2);        /* Pin PD2 input              */
    PORTD |= (1 << PD2);        /* Pin PD2 pull-up enabled    */


    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);

    for (;;) {                           /* loop forever */
        /* 
         * Test 1:  write text to display
         */
    
        /* clear display and home cursor */
        lcd_clrscr();
        
        /* put string to display (line 1) with linefeed */
        lcd_puts("LCD Test Line 1\n");

        /* cursor is now on second line, write second line */
        lcd_puts("Line 2");
        
        /* move cursor to position 8 on line 2 */
        lcd_gotoxy(7,1);  
        
        /* write single char to display */
        lcd_putc(':');
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();
        
        
        /*
         * Test 2: use lcd_command() to turn on cursor
         */
        
        /* turn on cursor */
        lcd_command(LCD_DISP_ON_CURSOR);

        /* put string */
        lcd_puts( "CurOn");
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();


        /*
         * Test 3: display shift
         */
        
        lcd_clrscr();     /* clear display home cursor */

        /* put string from program memory to display */
        lcd_puts_P( "Line 1 longer than 14 characters\n" );
        lcd_puts_P( "Line 2 longer than 14 characters" );
        
        /* move BOTH lines one position to the left */
        lcd_command(LCD_MOVE_DISP_LEFT);
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();

        /* turn off cursor */
        lcd_command(LCD_DISP_ON);
        
        
        /*
         *   Test: Display integer values
         */
        
        lcd_clrscr();   /* clear display home cursor */
        
        /* convert interger into string */
        itoa( num , buffer, 10);
        
        /* put converted string to display */
        lcd_puts(buffer);
        
        /* wait until push button PD2 (INT0) is pressed */
        wait_until_key_pressed();
        
    }
}
