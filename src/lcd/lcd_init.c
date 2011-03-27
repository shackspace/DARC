/*
 * lcd_init.c
 *
 * LCD initialization (based on dogm128 library)
 *
 * (c) 2011 Christoph Friedrich (christoph@christophfriedrich.de)
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Less License, as specified in the README file.
 *
 * For more information about less, or for information on how to 
 * contact the author, see the README file.
 */

#include <util/delay.h>

#include "lcd.h"

unsigned char lcd_memory[LCD_MEMORY_SIZE];

void lcd_Delay(uint16_t val) {
	while (val != 0)  {
		_delay_loop_2((F_CPU / 4000) - 7);
		val--;
	}
}

void lcd_init_display(void) {
  dog_delay(10);
  dog_spi_disable_client();	/* force reset of the spi subsystem of the ST7565R */
  dog_delay(10);
  dog_spi_enable_client();
  dog_delay(10);
  dog_cmd_mode();

  /* mostly taken from the EA dogm description */
  dog_spi_out(0x040);		/* set display start line to 0 */
  dog_spi_out(0x0a1);		/* ADC set to reverse */
  dog_spi_out(0x0c0);		/* common output mode */
  dog_spi_out(0x0a6);		/* display normal, bit val 0: LCD pixel off. */
  dog_spi_out(0x0a2);		/* LCD bias 1/9 */
  dog_spi_out(0x02f);		/* all power  control circuits on */
  dog_spi_out(0x0f8);		/* set booster ratio to */
  dog_spi_out(0x000);		/* 4x */
  dog_spi_out(0x027);		/* set V0 voltage resistor ratio to large */
  dog_spi_out(0x081);		/* set contrast */
  dog_spi_out(0x018);		/* contrast value, EA default: 0x016 */
  dog_spi_out(0x0ac);		/* indicator */
  dog_spi_out(0x000);		/* disable */
  dog_spi_out(0x0af);		/* display on */

  dog_spi_out(0x0a5);		/* display all points, ST7565, UC1610 */
  dog_delay(300);
  dog_spi_out(0x0a4);		/* normal display  */
  dog_delay(300);
  dog_spi_disable_client();
}

void lcd_init() {
	dog_spi_init();
	dog_init_display();
}