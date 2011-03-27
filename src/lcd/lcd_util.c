/*
 * lcd_util.c
 *
 * LCD utility functions (based on dogm128 library)
 *
 * (c) 2011 Christoph Friedrich (christoph@christophfriedrich.de)
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Less License, as specified in the README file.
 *
 * For more information about less, or for information on how to 
 * contact the author, see the README file.
 */

#include "lcd.h"

/**
 * Clears the complete LCD memory
 */
void lcd_clr(void) {
	for (uint16_t i = 0; i < LCD_MEMORY_SIZE; i++) {
		lcd_memory[i] = 0;
	}
}

void dog_set_pixel(uint8_t x, uint8_t y)
{
	// address = (y * PAGE_CNT) + x
	
	uint8_t address = (y * LCD_PAGE_CNT) + x;
	lcd_memory[address]
	
  uint8_t tmp;
  tmp = y;
  tmp &= (unsigned char)7;
  tmp = dog_bit_to_mask[tmp];
#if defined(DOG_DOUBLE_MEMORY)
  if ( (y & 8) == 0 ) 
  {
    dog_page_buffer[x] |= tmp;
  }
  else
  {
    dog_page_buffer[x+DOG_WIDTH] |= tmp;
  }
#else
  dog_page_buffer[x] |= tmp;
#endif
}

void dog_SetPixel(uint8_t x, uint8_t y)
{
  if ( x < DOG_WIDTH )
    if ( y >= dog_min_y && y <=dog_max_y )
    {
      dog_set_pixel(x, y);
    }
}


