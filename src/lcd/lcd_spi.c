/*
 * lcd_spi.c
 *
 * LCD SPI Interace based on dogm128 library
 *
 * (c) 2011 Christoph Friedrich (christoph@christophfriedrich.de)
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Less License, as specified in the README file.
 *
 * For more information about less, or for information on how to 
 * contact the author, see the README file.
 */

#include <avr/io.h>

#include "lcd.h"

#define _LCD_SPI_DDR(PCHAR) DDR ## PCHAR
#define LCD_SPI_DDR(PCHAR) _LCD_SPI_DDR(PCHAR)
#define _LCD_SPI_PORT(PCHAR) PORT ## PCHAR
#define LCD_SPI_PORT(PCHAR) _LCD_SPI_PORT(PCHAR)

#ifndef LCD_SPI_SCL_PORT
#define LCD_SPI_SCL_PORT B
#endif

#ifndef LCD_SPI_SCL_PIN
#define LCD_SPI_SCL_PIN 5
#endif

#ifndef LCD_SPI_MOSI_PORT
#define LCD_SPI_MOSI_PORT B
#endif 

#ifndef LCD_SPI_MOSI_PIN
#define LCD_SPI_MOSI_PIN 3
#endif 

#ifndef LCD_SPI_A0_PORT
#define LCD_SPI_A0_PORT B
#endif 

#ifndef LCD_SPI_A0_PIN
#define LCD_SPI_A0_PIN 1
#endif 

#ifndef LCD_SPI_SS_PORT
#define LCD_SPI_SS_PORT B
#endif 

#ifndef LCD_SPI_SS_PIN
#define LCD_SPI_SS_PIN 2
#endif 

/**
 * Initilaize the SPI interface
 */
void lcd_spi_init(void) {
	/* setup port directions */
	LCD_SPI_DDR(LCD_SPI_MOSI_PORT) |= _BV(LCD_SPI_MOSI_PIN);
	LCD_SPI_DDR(LCD_SPI_A0_PORT) |= _BV(LCD_SPI_A0_PIN);
	LCD_SPI_DDR(LCD_SPI_SCL_PORT) |= _BV(LCD_SPI_SCL_PIN);
	LCD_SPI_DDR(LCD_SPI_SS_PORT) |= _BV(LCD_SPI_SS_PIN);

	SPCR = 0;
	SPCR =  (1 << SPE) | (1 << MSTR) | (0 << SPR1) | (0 << SPR0) | (0 << CPOL) | (0 << CPHA);
}

/**
 * Writes a char to the SPI interface
 */
unsigned char lcd_spi_out(unsigned char data) {
	/* send data */
	SPDR = data;
	
	/* wait for transmission */
	while (!(SPSR & (1 << SPIF)));
	
	/* clear the SPIF flag by reading SPDR */
	return  SPDR;
}

/**
 * Enable CS pin for LCD
 */
void lcd_spi_enable_client(void) {
	/* before the slave is enabled, esure that the clk pin has a logical zero */
	LCD_SPI_PORT(LCD_SPI_SCL_PORT) &= ~_BV(LCD_SPI_SCL_PIN);
  
	/* now enable the SPI slave */
	LCD_SPI_PORT(LCD_SPI_SS_PORT) &= ~_BV(LCD_SPI_SS_PIN);
}

/**
 * Disable CS pin for LCD
 */
void lcd_spi_disable_client(void) {
	/* disable the client (write a logical zero on the CS line) */
	LCD_SPI_PORT(LCD_SPI_SS_PORT) |= _BV(LCD_SPI_SS_PIN);
}

/**
 * Switch LCD to command mode
 */
void lcd_cmd_mode(void) {
	LCD_SPI_PORT(LCD_SPI_A0_PORT) &= ~_BV(LCD_SPI_A0_PIN);
}

/**
 * Switch LCD to data mode
 */
void lcd_data_mode(void) {
	LCD_SPI_PORT(LCD_SPI_A0_PORT) |= _BV(LCD_SPI_A0_PIN);
}