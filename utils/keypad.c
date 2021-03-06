/*
 * keypad.c
 *
 *  Created on: Apr 16, 2018
 *      Author: Contovasilis
 */
#include "keypad.h"
#include "interrupt.h"
#include <stdlib.h>

void initKeypad(){
    gpioStruct gpio;                        //define struct
    gpio.port = CLPORT;                     //select column ports
    gpio.pins = CLPINS;                     //select column pins
    gpio.type = INPUT_PD;                   //initialize GPIOs as inputs with pull-downs
    gpio.af = AF0;
    gpio_init(&gpio);                       //configure struct

    gpio.port = RWPORT;                     //select row ports
    gpio.pins = RWPINS;                     //select row pins
    gpio.type = OUTPUT;                     //initialize GPIOs as outputs
    gpio.af = AF0;
    gpio_init(&gpio);                       //configure struct

    gpioSet(RWPORT, RWPINS);               //set all row pins low

    initExtInt(CLPORT, CLPINS, RISING);     //initialize external interrupts on
                                            //column pins with falling edge trigger

    enableExtInt(CLPORT, CLPINS);           //enable external interrupts
    initNVIC(PORT2_IRQn);                   //enable NVIC for column port
                                             //enable global interrupts

}

void scanKeypad(uint8_t iflg){
    static uint8_t chrArray[12] = {'1','4','7','*','2','5','8','0','3','6','9','#'};
                                                        //array with keypad characters
    uint8_t col = 0;                                    //initialize column iterator
    while(col<4){                                       //begin iteration loop
        gpioClear(RWPORT, (RWPINS) & ~(R1<<col));      //set all except one row pin low
        if(gpioRead(CLPORT, CLPINS) & iflg){           //read column that produced the
                                                        //interrupt
            key = chrArray[col + ((iflg>>4) & ~(0x02))];//set key to character pressed
            break;                                      //break if pressed key was found
        }
        col++;                                          //repeat with next row set low if
                                                        //pressed key was not found
        gpioSet(RWPORT, RWPINS);                       //reset all rows high
    }
    gpioSet(RWPORT, RWPINS);                           //reset all rows high for next key
                                                        //interrupt
}

void PORT2_IRQHandler(void)               //ISR handler for port 2
{
    disableExtInt(CLPORT, CLPINS);        //disable column interrupts to avoid multiple interrupts
    scanKeypad(readIFG(CLPORT,CLPINS));   //find which key in the row was pressed
    flag = 1;
    enableExtInt(CLPORT, CLPINS);         //re-enable column interrupts
}

