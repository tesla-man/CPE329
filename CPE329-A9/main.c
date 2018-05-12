#include "msp.h"


/**
 * main.c
 */
volatile uint8_t flag;
int main(void) {
    volatile unsigned int i;

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    // GPIO Setup
    P1->OUT &= ~BIT0;                       // Clear LED to start
    P1->DIR |= BIT0;                        // Set P1.0/LED to output
    P5->SEL1 |= BIT4;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT4;

    // Enable global interrupt
    __enable_irq();

    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);

    // Sampling time, S&H=16, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 12-bit conversion results

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable ADC conv complete interrupt
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;

    while (1)
    {
       if(flag){
           ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
           flag = 0;
       }

    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {
    static uint16_t conv;
    static double voltage;
    conv = ADC14->MEM[0];
    voltage = 3.24*((double)conv/16384);
    flag = 1;
}