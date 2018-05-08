#include "spi.h"
#include "uart.h"
#include "delay.h"
#include "msp.h"

int main(void)
{
    uint16_t data;
    initClock();
    spiInit();
    uartInit();

    __enable_irq(); //scoop poop

    while(1){
        if((data=checkCR())<4096){
            driveDAC(data);
        }
    }
}
