#include "msp.h"
#include "gpio.h"
#include "keypad.h"
#include "interrupt.h"
#include "timer.h"
#include "delay.h"
/**
 * main.c
 */
void main(void)
{

   P2->DIR |= BIT4;
    P2->SEL0 |= BIT4;

    P1->DIR |= BIT0;


    initClock();            //enable HFXT @ 48MHZ

    timerStruct timer;
    timer.channel = TIM0;
    timer.divide = DIV8;
    timer.mode = UPDN;
    timer.source = SMCLK;
    timer.intccr = CCR0;
    TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_6;
    TIMER_A0->CCR[0] = 8580;
    TIMER_A0->CCR[1] = 1;
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_2;
    timer_init(&timer);


    initKeypad();           //init keypad
    __enable_irq();

    uint8_t keyop = 0, keycnt = 10, keyint = 0;
    uint16_t position = 648;

    TIMER_A0->CCR[1] = 648; //start centered

    while(1){

        if(flag){
            if(key&0x10){
                keyint = keyint + ((key & 0x0F)*keycnt);
                keycnt = 1;
            }
            else{
                keyop = key & 0x0F;
                keycnt = 10;
            }
            flag = 0;
        }


        if(keyop == 0x0A){          //asterisk
            position = position + (keyint * 20);
            if(position>825){
                position = 825;
            }

            TIMER_A0->CCR[1] = position;    //set servo position
            keyint = 0;
            keyop = 0;
        }
        if(keyop == 0x03){          //pound
            position =position - (keyint * 20);
            if(position<470){
                position = 470;
            }
            TIMER_A0->CCR[1] = position;   //set servo position
            keyint = 0;
            keyop = 0;
        }
    }
}
