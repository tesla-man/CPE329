#include "msp.h"
#include "delay.h"


int main(void) {

    set_DCO(FREQ_24_MHZ);            // Set DCO to 24MHz
    P1->SEL0 &= ~BIT0;               // Clear bit 0 of the P1->SEL0 register
    P1->SEL1 &= ~BIT0;               // Clear bit 0 of the P1->SEL1 register
    P1->DIR |= BIT0;                 // P1.0 set as output



while(1){

   delay_ms(500);      // Delay 100us
   P1->OUT ^= BIT0;                 // Toggle P1.0 LED OFF
}
}

