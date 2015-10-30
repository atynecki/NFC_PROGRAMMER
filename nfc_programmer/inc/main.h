
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

#define SPIx     SPI1
#define TIMx     TIM2

#define TIMER_DELAY_PERIOD      1000
#define TIMER_DELAY_PRESCALER   15
#define TIMx_CLK_ENABLE                __TIM2_CLK_ENABLE
#define TIMx_IRQn                      TIM2_IRQn
#define TIMx_IRQHandler                TIM2_IRQHandler

#define Text		"Artur jest krolem kodu"

#endif /* __MAIN_H */
