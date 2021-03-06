/*
 * timer.h
 *  Created on: Apr 23, 2018
 *      Author: Contovasilis
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "msp.h"

#define HAL_CCR(x)        (uint32_t)&TIMER_A0->CCR[x] -  (uint32_t)TIMER_A0
#define HAL_CTL           (uint32_t)&TIMER_A0->CTL -  (uint32_t)TIMER_A0
#define HAL_CCTL(x)       (uint32_t)&TIMER_A0->CCTL[x] -  (uint32_t)TIMER_A0
#define HWREG32(x)        (*((volatile uint32_t *)(x)))
#define HWREG16(x)      (*((volatile uint16_t *)(x)))

#define CCR0            0
#define CCR1            1
#define CCR2            2
#define CCR3            3
#define CCR4            4
#define CCR5            5
#define CCR6            6

static uint32_t TIMER_NUM_TO_BASE[] =
{       (uint32_t)TIMER_A0,
        (uint32_t)TIMER_A1,
        (uint32_t)TIMER_A2,
        (uint32_t)TIMER_A3
};

typedef enum TIM_CH{
    TIM0 = 0x00,
    TIM1,
    TIM2,
    TIM3
}TIM_CH;

typedef enum TIM_MC{
    STOP = 0x00,
    UP,
    CONT,
    UPDN
}TIM_MC;

typedef enum TIM_ID{
    DIV1 = 0x00,
    DIV2,
    DIV4,
    DIV8
}TIM_ID;

typedef enum TIM_SSEL{
    TACLK = 0x00,
    ACLK,
    SMCLK,
    INCLK
}TIM_SSEL;

typedef struct timerStruct{
    TIM_CH      channel;
    TIM_MC      mode;
    TIM_ID      divide;
    TIM_SSEL    source;
    uint8_t    intccr;
}timerStruct;

void timer_init(timerStruct* timer);
void timerCCR0(uint8_t channel, uint16_t ccrvalue);
void timerCCR1(uint8_t channel, uint16_t ccrvalue);

#endif /* TIMER_H_ */
