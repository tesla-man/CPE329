/*
 * lcd.c
 *
 *  Created on: Apr 9, 2018
 *      Author: Contovasilis
 */

#include "lcd.h"
#include "delay.h"
#include "gpio.h"

char colStartIndex[2] = {0, 0x40};

unsigned char cstchar1[8] =  {0b00000,
                              0b00000,
                              0b00001,
                              0b00011,
                              0b00110,
                              0b01100,
                              0b01100,
                              0b01100};

unsigned char cstchar2[8] =  {0b00000,
                              0b00000,
                              0b11111,
                              0b11111,
                              0b00000,
                              0b00000,
                              0b00000,
                              0b00000};

unsigned char cstchar3[8] =  {0b00000,
                              0b00000,
                              0b10000,
                              0b11000,
                              0b01100,
                              0b00110,
                              0b00110,
                              0b00110};

unsigned char cstchar4[8] =  {0b00000,
                              0b00000,
                              0b10000,
                              0b11000,
                              0b01100,
                              0b00110,
                              0b00110,
                              0b00110};



void lcdInit(){
    delay_ms(50);      //startup delay

    gpioStruct gpio;

    gpio.port = CPORT;
    gpio.pins = RS | RW | ENA;
    gpio.type = OUTPUT;
    gpio.af = AF0;
    gpio_init(&gpio);

    gpio.port = DPORT;
    gpio.pins = DB4 | DB5 | DB6 | DB7;
    gpio.type = OUTPUT;
    gpio.af = AF0;
    gpio_init(&gpio);

    sendCmdNib(FUNCTION);
    delay_us(50);
    sendCommand(FUNCTION);
    delay_us(50);
    sendCommand(FUNCTION);
    delay_us(50);
    sendCommand(DISPCFG);
    sendCommand(CLEAR);
    sendCommand(ENTRY);
    createChar(0, cstchar1);
    createChar(1, cstchar2);
    createChar(2, cstchar3);
}

void checkBF()
{
    gpioStruct gpio;
    gpio.port = DPORT;
    gpio.pins = DB7;
    gpio.type = INPUT;
    gpio.af = AF0;
    gpio_init(&gpio);

    gpioClear(CPORT, RS);
    gpioSet(CPORT, RW);
    gpioSet(CPORT, ENA);
    while(gpioRead(DPORT, DB7));

    gpioClear(CPORT, ENA);
    gpioClear(CPORT, RW);
    gpio.port = DPORT;
    gpio.pins = DB7;
    gpio.type = OUTPUT;
    gpio.af = AF0;
    gpio_init(&gpio);
}

void sendCmdNib(uint8_t cmd){
    checkBF();
    gpioClear(CPORT, RS);           //clear RS
    gpioClear(CPORT, RW);           //clear RW
    gpioSet(CPORT, ENA);           //set ENA
    gpioSet(DPORT, cmd);           //send command byte or nibble
    gpioClear(CPORT, ENA);         //clear ENA
    gpioClear(DPORT, 0xF0);        //clear data port
}

void sendChrNib(uint8_t chr){
    checkBF();
    gpioSet(CPORT, RS);            //set RS
    gpioClear(CPORT, RW);          //clear RW
    gpioSet(CPORT, ENA);           //set ENA
    gpioSet(DPORT, chr);           //send character byte or nibble
    gpioClear(CPORT, ENA);         //clear ENA
    gpioClear(CPORT, RS);          //clear RS
    gpioClear(DPORT, 0xF0);        //clear data port
}

void sendCommand(uint8_t cmd){
    sendCmdNib(cmd);
    sendCmdNib(cmd<<4);
}


void sendCharacter(uint8_t chr){
    sendChrNib(chr);
    sendChrNib(chr<<4);
}

void sendCharacterXY(uint8_t chr, uint8_t x, uint8_t y){
    moveCursor(x, y);
    sendChrNib(chr);
    sendChrNib(chr<<4);
}

void sendString(char *str){
    while(*str > 0){
        sendCharacter(*str++);        //send each character in string
    }
}

void sendStringXY(char *str, uint8_t x, uint8_t y){
    moveCursor(x, y);
    while(*str > 0){
        sendCharacter(*str++);        //send each character in string
    }
}

void sendInteger(int IntegerToDisplay, uint8_t length)
{
    char StringToDisplay[16];
    sprintf(StringToDisplay, "%-*d", length, IntegerToDisplay);
    sendString(StringToDisplay);
}

void sendIntegerXY(int IntegerToDisplay, uint8_t x, uint8_t y, uint8_t length){
    char StringToDisplay[16];
    sprintf(StringToDisplay, "%-*d", length, IntegerToDisplay);
    moveCursor(x, y);
    sendString(StringToDisplay);
}

void moveCursor(uint8_t x, uint8_t y){
    sendCommand(DDRAM_MSK + colStartIndex[y-1] + (x-1));
}

void createChar(unsigned char location, unsigned char *ptr){
    uint8_t i;
    sendCommand(CGRAM_MSK | (location << 3));
    for(i=0;i<8;i++){
        sendCharacter(ptr[i]);
    }
    moveCursor(1,1);
}
