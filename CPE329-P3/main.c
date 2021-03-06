#include "msp.h"
#include "uart.h"
#include "delay.h"
#include "interrupt.h"
#include "gpio.h"
#include "term.h"
#include "math.h"

/**
 * main.c
 */
volatile uint8_t strig=0;
volatile  int dcavg, vpp = 0;
volatile uint16_t rms = 0,  freq;
volatile uint32_t capture = 0;
volatile uint8_t mode = 0;

int main(void) {
    volatile unsigned int i;

    initClock();

    P1->DIR |=BIT0;
    P1->OUT &=~BIT0;

    P1->REN |=BIT1;
    P1->OUT |=BIT1;

    P2->REN |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->SEL0 |= BIT4;

    P5->SEL1 |= BIT4 | BIT5;                 // Configure P5.4 for ADC
    P5->SEL0 |= BIT4 | BIT5;


    uartInit();

    termDmmSplash();
    delay_ms(2000);
    termMain();

    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CM_1 | // Capture rising edge,
            TIMER_A_CCTLN_CCIS_0 |          // Use CCI2A=ACLK,
            TIMER_A_CCTLN_CCIE |            // Enable capture interrupt
            TIMER_A_CCTLN_CAP |             // Enable capture mode,
            TIMER_A_CCTLN_SCS;              // Synchronous capture

    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2 | // Use SMCLK as clock source,
            TIMER_A_CTL_MC_2 |              // Start timer in continuous mode
            //TIMER_A_CTL_ID__8 |
            TIMER_A_CTL_IE  |
            TIMER_A_CTL_CLR;                // clear TA0R


    // Enable global interrupt
    __enable_irq();

    // Enable ADC interrupt in NVIC module
    initNVIC(ADC14_IRQn);
    initNVIC(TA0_N_IRQn);

    // Sampling time, S&H=16, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2      |
                  ADC14_CTL0_SHP         |
                  ADC14_CTL0_ON          |
                  ADC14_CTL0_SSEL__SMCLK |
                  ADC14_CTL0_DIV_7       |
                  ADC14_CTL0_MSC         |
                  ADC14_CTL0_CONSEQ_2;

    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 14-bit conversion results


    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1 |
                      ADC14_MCTLN_DIF    |
                      ADC14_MCTLN_VRSEL_14;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;            // Enable ADC conv complete interrupt
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;

    updateTermMode(mode);

    while (1)
    {
       delay_ms(50);
       updateRMS(rms);
       freq = 48000000/capture;
       updateFREQ(freq);
       updatedcavg(dcavg);
       updatevpp(vpp);
       if(!(gpioRead(PORT1, PIN1))){
           mode ^= 1;
           updateTermMode(mode);

           if(mode){
               disableNVIC(ADC14_IRQn);
           }
           else{
               initNVIC(ADC14_IRQn);
           }
       }

    }
}

/* ADC interrupt handler
 * This handler is run each time the ADC completes a conversion.
 * When the capture timer detects a rising edge, the strig
 * flag is set which allows ADC values to be used in the RMS,
 * VDC, and VPP calculations.
 */
void ADC14_IRQHandler(void) {
    static uint16_t conv = 0, k = 0;
    static uint64_t asum = 0;
    static int dsum, dcv = 0, vpos = 0;

    conv = (ADC14->MEM[0]);
    dcv = (6596*(conv-8191))/8191 - 3;

        if(strig){
            asum = asum + (uint32_t) (abs(dcv) * abs(dcv));
            dsum = dsum + dcv;
            if(vpos < abs(dcv)) vpos = abs(dcv);
            k++;
        }
        else{
            if(k){
                rms = sqrt(asum/k);
                dcavg = dsum/k;
                vpp = (vpos-abs(dcavg))*2;
                vpos = 0;
                k = 0;
                asum = 0;
                dsum = 0;
            }
        }
}

/*Timer A0 interrupt handler
 * This handler is run each time a rising edge of the input signal
 * on pin 2.4 occurs. When the interrupt occurs, the timer is reset
 * so that the next interrupt will provide a capture value which
 * represents the period of the input signal. The TAIFG is also
 * checked to count any timer overflows that occur during very low
 * frequency measurements.
 */
void TA0_N_IRQHandler(void) {
    static uint16_t ovf = 0;

    if((TIMER_A0->CTL) & TIMER_A_CTL_IFG){
        if(ovf<756){
            ovf++;
        }
        else{
            strig ^= 1;
        }
        TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;
    }

    if(TIMER_A0->CCTL[1] & TIMER_A_CCTLN_CCIFG){
        capture = TIMER_A0->CCR[1] + ovf*65535 + 149;
        strig ^= 1;
        ovf = 0;
    }

    TIMER_A0->CTL |= TIMER_A_CTL_CLR;
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
}
