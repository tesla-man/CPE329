/*
 * lcd.h
 *
 *  Created on: Apr 9, 2018
 *      Author: Contovasilis
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdio.h>

#define ID              1       //0-increment cursor left, 1-increment cursor right
#define SHIFT           0       //0-no shift, 1-shift whole display
#define DISP            1       //0-display off, 1-display on
#define CURSOR          0       //0-cursor off, 1-cursor on
#define BLINK           0       //0-no blink, 1-blink
#define SC              0       //0-shift shift cursor, 1-shift display
#define RL              1       //0-shift left, 1-shift right
#define DINT            0       //0-4bit mode, 1-8bit mode
#define LINE            1       //0-1 line mode, 1-2 line mode
#define FONT            0       //0-5x8 font, 1-5x11 font (not compatible)

#define CLEAR           0x01
#define HOME            0x02
#define ENTRY           ENTRY_MSK | ID<<1 | SHIFT
#define DISPCFG         DISPCFG_MSK | DISP<<2 | CURSOR<<1 | BLINK
#define CSRCFG          CSRCFG_MSK | SC<<3 | RL<<2
#define FUNCTION        FUNCTION_MSK | DINT<<4 | LINE<<3 | FONT<<2

#define ENTRY_MSK       0x04
#define DISPCFG_MSK     0x08
#define CSRCFG_MSK      0x10
#define FUNCTION_MSK    0X20

#define CGRAM_MSK       0x40
#define DDRAM_MSK       0x80

#define DPORT   PORT4

#define DB0     PIN0
#define DB1     PIN1
#define DB2     PIN2
#define DB3     PIN3
#define DB4     PIN4
#define DB5     PIN5
#define DB6     PIN6
#define DB7     PIN7

#define CPORT   PORT3

#define ENA     PIN5
#define RW      PIN6
#define RS      PIN7

void sendCmdNib(uint8_t cmd);
void sendChrNib(uint8_t cmd);
void sendCommand(uint8_t cmd);
void sendCharacter(uint8_t chr);
void sendCharacterXY(uint8_t chr, uint8_t x, uint8_t y);
void sendString(char *str);
void sendStringXY(char *str, uint8_t x, uint8_t y);
void sendInteger(int IntegerToDisplay, uint8_t length);
void sendIntegerXY(int IntegerToDisplay, uint8_t x, uint8_t y, uint8_t length);
void moveCursor(uint8_t x, uint8_t y);
void createChar(unsigned char location, unsigned char *ptr);
void lcdInit();
void checkBF();

#endif /* LCD_H_ */
