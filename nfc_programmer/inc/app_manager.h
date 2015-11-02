
#ifndef __APP_MANAGER_H
#define __APP_MANAGER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

/** I2C config */
#define I2C                              I2C1
#define I2C_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define DMA_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define I2C_SDA_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SCL_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2C_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define I2C_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2C Pins */
#define I2C_SCL_PIN                    GPIO_PIN_8
#define I2C_SCL_GPIO_PORT              GPIOB
#define I2C_SCL_AF                     GPIO_AF4_I2C1
#define I2C_SDA_PIN                    GPIO_PIN_9
#define I2C_SDA_GPIO_PORT              GPIOB
#define I2C_SDA_AF                     GPIO_AF4_I2C1

/* Definition for I2C's DMA */
#define I2C_TX_DMA_CHANNEL             DMA_CHANNEL_1
#define I2C_TX_DMA_STREAM              DMA1_STREAM_6

/* Definition for I2C's NVIC */
#define I2C_DMA_IRQn                	DMA1_Channel2_3_IRQn
#define I2C_DMA_IRQHandler          	DMA1_Channel2_3_IRQHandler

#define COUNTOF(__BUFFER__)   				(sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define I2C_ADDRESS        						0x30F

/* Timing samples with SYSCLK 32MHz set in SystemClock_Config() */ 
#define I2C_TIMING_100KHZ       			0x10A13E56 /* Analog Filter ON, Rise Time 400ns, Fall Time 100ns */ 
#define I2C_TIMING_400KHZ       			0x00B1112E /* Analog Filter ON, Rise Time 250ns, Fall Time 100ns */ 

#define TEXT_FRAME_MAX_LENGTH					40

typedef struct 
{
	uint8_t mode;
	uint8_t *text_frame;
	uint8_t text_frame_length;
} app_config_t, *app_config_p;

typedef enum MODE
{
	NFC_BOARD_WAIT = 0,
	DATA_WAIT,
	DATA_RECEIVED,
	DATA_SEND
} mode;


#define TEXT			"Artur krolem kodu"

void Error_Handler(void);

void system_clock_init(void);

#endif /* __MAIN_H */
