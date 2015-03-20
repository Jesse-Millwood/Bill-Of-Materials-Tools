#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "lcd_drv.h"

 
int main( void )
{
  lcd_init();
  lcd_xy( 0, 0 );
  lcd_puts( "Line 1" );
#ifdef LCD_LINE2
  lcd_xy( 0, 1 );
  lcd_puts( "Line 2" );
#ifdef LCD_LINE3
  lcd_xy( 0, 2 );
  lcd_puts( "Line 3" );
#ifdef LCD_LINE4
  lcd_xy( 0, 3 );
  lcd_puts( "Line 4" );
#endif  
#endif  
#endif  
  for(;;){
  }
}
