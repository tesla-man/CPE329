/*
 * spi.c
 *
 *  Created on: Apr 27, 2018
 *      Author: Contovasilis
 */

#include "spi.h"
#include "delay.h"
#include "gpio.h"

void spiInit(){

    gpioStruct gpio;

    gpio.port = PORT2;              //initialize spi pins
    gpio.pins = PIN0 | PIN1 | PIN3;
    gpio.type = OUTPUT;
    gpio.af = AF1;
    gpio_init(&gpio);

    //initialize spi peripheral
    EUSCI_A1->CTLW0 |=  EUSCI_A_CTLW0_SWRST;
    EUSCI_A1->CTLW0 =   EUSCI_A_CTLW0_SWRST    |
                        EUSCI_A_CTLW0_CKPH     |
                        EUSCI_A_CTLW0_MST      |
                        EUSCI_A_CTLW0_SYNC     |
                        EUSCI_A_CTLW0_UCSSEL_2 |
                        EUSCI_A_CTLW0_STEM     |
                        EUSCI_A_CTLW0_MODE_2   |
                        EUSCI_A_CTLW0_MSB      ;

    EUSCI_A1->BRW = 0x0002;           //spi runs at 24MHz
    EUSCI_A1->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

}

/*SPI write function
 * not used for optimization purposes
 */
void driveDAC(uint16_t value){
    EUSCI_A1->TXBUF = ((value & 0xF00) | 0x7000)>>8; //send upper 8 bits
    //while(!(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG));     //wait for tx buffer to empty

    EUSCI_A1->TXBUF = (value & 0xFF);                //send lower 8 bits
    //while((EUSCI_A1->STATW) & EUSCI_A_STATW_SPI_BUSY); //wait for SPI shift reg
}


