/*
 * lcd_page.c
 *
 * LCD page support (based on dogm128 library)
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

void lcd_transfer_sub_page(uint8_t page, uint8_t offset) {
	uint8_t idx;
	uint8_t *memory = lcd_memory;
	
	buffer += page * LCD_PAGE_SIZE + offset;

	/* enable and reset com interface of the ST7565R */
	dog_spi_enable_client();

	/* set write position */
	dog_cmd_mode();
	dog_spi_out(0x0b0 | page);		/* select current page (ST7565R) */
	dog_spi_out(0x010);				/* set upper 4 bit of the col adr to 0 */
	dog_spi_out(0x000);				/* set lower 4 bit of the col adr to 0 */

	/* send a complete page */
	dog_data_mode();
	 
#ifdef LCD_REVERSE
	idx = 0;
	while (idx != LCD_PAGE_WIDTH) {
    	dog_spi_out(buffer[idx++]);
	}
#else /* DOG_REVERSE */
	idx = LCD_PAGE_WIDTH;
	while (idx != 0) {
		dog_spi_out(buffer[--idx]); 
	}
#endif

	/* disable com interface of the ST7565R */
	dog_spi_disable_client();
}

void lcd_transfer_pages() {
	uint8_t page = 0;
	while (page != LCD_PAGE_CNT) {
		lcd_transfer_sub_page(page, 0);
	}
}