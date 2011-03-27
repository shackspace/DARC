/*
 * lcd.h
 *
 * LCD controller library
 *
 * (c) 2011 Christoph Friedrich (christoph@christophfriedrich.de)
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Less License, as specified in the README file.
 *
 * For more information about less, or for information on how to 
 * contact the author, see the README file.
 */

#ifndef __LCD_H__
#define __LCD_H__

//#define LCD_REVERSE			/* uncomment for 180 degree rotation */

#define LCD_PAGE_HEIGHT 8

#define LCD_WIDTH 128
#define LCD_HEIGHT 64

/* derived constants */
#define LCD_PAGE_CNT ((LCD_HEIGHT + LCD_PAGE_HEIGHT - 1) / LCD_PAGE_HEIGHT)
#define LCD_PAGE_WIDTH LCD_WIDTH
#define LCD_PAGE_SIZE LCD_PAGE_WIDTH / 8
#define LCD_MEMORY_SIZE (LCD_PAGE_SIZE * LCD_PAGE_CNT)

/* LCD Memory */
extern unsigned char lcd_memory[LCD_MEMORY_SIZE];

/* LCD Init (lcd_init.c) */
void lcd_Delay(uint16_t val);
void lcd_init_display(void);
void lcd_init();

/* LCD Page functions (lcd_page.c) */
void lcd_transfer_sub_page(uint8_t page, uint8_t offset);
void lcd_transfer_pages();

/* LCD SPI Interface (lcd_spi.c) */
void lcd_spi_init(void);
unsigned char lcd_spi_out(unsigned char data);
void lcd_spi_enable_client(void);
void lcd_spi_disable_client(void);
void lcd_cmd_mode(void);
void lcd_data_mode(void);

/* LCD utility functions (lcd_util.c) */
void lcd_clr(void);

#endif /* __LCD_H__ */