#include "msp.h"
#include "lcd.h"
#include "gpio.h"
#include "delay.h"

void main(void){
    initClock();


	lcdInit();

	sendString("I'm a piece of");
	sendStringXY("shit", 1, 2);

	while(1){
	}

}
