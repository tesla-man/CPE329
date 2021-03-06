/*
 * delay.c
 *
 *  Created on: Apr 4, 2018
 *      Author: Contovasilis
 */
#include "delay.h"
#include "msp.h"

inline delay_ms(uint32_t time){
    uint32_t ticks = FCPU * time * 10;

    while(ticks){
        ticks--;
    }
}

inline delay_us(uint32_t time){

    uint32_t ticks = ((FCPU * time) / 100) - 2;

    while(ticks){
        ticks--;
    }

}

void initClock(){

    PJ->SEL0 |= BIT2 | BIT3;                // Configure PJ.2/3 for HFXT function
    PJ->SEL1 &= ~(BIT2 | BIT3);

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
     PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

    CS->KEY = CS_KEY_VAL;

    CS->CTL2 |= CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE | CS_CTL2_HFXT_EN;
    while(CS->IFG & CS_IFG_HFXTIFG)
        CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;
    CS->CTL1 = CS_CTL1_SELM__HFXTCLK | CS_CTL1_SELS__HFXTCLK;

    CS->KEY = 0;
}

void set_DCO(uint16_t freq){

    CS->KEY = CS_KEY_VAL;

    switch(freq)
            {
            case FREQ_1_5_MHZ:
                CS->CTL0 = CS_CTL0_DCORSEL_0;
                break;
            case FREQ_3_MHZ:
                CS->CTL0 = CS_CTL0_DCORSEL_1;
                break;
            case FREQ_6_MHZ:
                CS->CTL0 = CS_CTL0_DCORSEL_2;
                break;
            case FREQ_12_MHZ:
                CS->CTL0 = CS_CTL0_DCORSEL_3;
                break;
            case FREQ_24_MHZ:
                CS->CTL0 = CS_CTL0_DCORSEL_4;
                break;
            case FREQ_48_MHZ:
                while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
                 PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
                while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
                FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
                FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;
                CS->CTL0 = CS_CTL0_DCORSEL_5;
                break;
            }

    CS->CTL1 = CS_CTL1_SELM__DCOCLK;
    CS->KEY = 0;
}


