#include "msp.h"
#include "uart.h"
#include "delay.h"

/**
 * main.c
 */
volatile uint8_t flago;
volatile  int voltage;
int main(void) {
    volatile unsigned int i;

    initClock();

    P5->SEL1 |= BIT4 | BIT5;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT4 | BIT5;


    uartInit();
    // Enable global interrupt
    __enable_irq();

    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);

    // Sampling time, S&H=16, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 14-bit conversion results


    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1 | ADC14_MCTLN_DIF | ADC14_MCTLN_VRSEL_14;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable ADC conv complete interrupt
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;

    while (1)
    {
       if(flago){
           ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
           flago = 0;
       }
       //uartWrite(voltage);
       delay_ms(500);
    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {
    static uint16_t conv;
    conv = ADC14->MEM[0];
    voltage = (6596*(conv-8191))/8191;
    flago = 1;
}
