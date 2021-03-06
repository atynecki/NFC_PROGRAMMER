
#ifndef __APP_MANAGER_H
#define __APP_MANAGER_H

#include "stm32l0xx_hal.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"
#include "M24LR04E-R_driver.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

#define USE_USB_CLKSOURCE_CRSHSI48   1
//#define USE_USB_CLKSOURCE_PLL        1

/** I2C config */
#define I2C                              I2C1
#define I2C_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define DMA_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define I2C_SDA_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SCL_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2C_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define I2C_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()
#define I2C_TIMING_100KHZ       				0x10A13E56 /* Analog Filter ON, Rise Time 400ns, Fall Time 100ns */

/* Definition for I2C pins */
#define I2C_SCL_PIN                    	GPIO_PIN_8
#define I2C_SCL_GPIO_PORT              	GPIOB
#define I2C_SCL_AF                     	GPIO_AF4_I2C1
#define I2C_SDA_PIN                    	GPIO_PIN_9
#define I2C_SDA_GPIO_PORT              	GPIOB
#define I2C_SDA_AF                     	GPIO_AF4_I2C1

/* Definition for I2C NVIC */
#define I2C_IRQn                    		I2C1_IRQn
#define I2C_IRQHandler              		I2C1_IRQHandler

/** Applictaion value */
#define MAX_TEXT_LEN                      40
#define DISPLAY_LINE_NUMBER								 3
#define SIGN_IN_LINE										 	14
#define NOTIFY_LENGHT										 	 7	

#define COUNTOF(__BUFFER__)   						(sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/** Applictaion manager structure */
typedef struct 
{
	uint8_t mode;
	uint8_t start_flag;
	uint8_t text_frame[MAX_TEXT_LEN+2];
	uint8_t text_frame_length;
	uint8_t USB_text_received;
	uint8_t error_code;
} app_config_t, *app_config_p;

/** Mode definition */
typedef enum MODE
{
	NFC_DETECT = 0,
	USB_SEND_TEXT,
	TEXT_RECEIVED,
	TEXT_SEND
} mode;

/** Mode definition */
typedef enum ERROR_FLAG
{
	APP_OK = 0,
	CLOCK_ERROR,
	USB_ERROR,
	DISPLAY_ERROR,
	I2C_ERROR,
	SEND_ERROR,
	APP_ERROR
} error_code;

/** Application text definition */

#define CONNECT_NFC_BOARD_PART1				"CONNECT"
#define CONNECT_NFC_BOARD_PART2				"NFC BOARD"

#define USB_SEND_TEXT_PART1						"SEND TEXT"
#define USB_SEND_TEXT_PART2						"TO PROGRAM"
#define USB_SEND_TEXT_PART3						"MAX 40 SIGNS"

#define CONTINUE_TEXT_PART1						"PROGRAM END"
#define CONTINUE_TEXT_PART2						"PUSH BUTTON"
#define CONTINUE_TEXT_PART3						"TO CONTINUE"

#define SUCCESS_TEXT									"SUCCESS"
#define ERROR_TEXT										"ERROR"

void system_clock_init(void);
void USB_init(void);
void LED_button_init(void);

void display_welcome_view(void);
void connect_nfc_board_message(void);
void USB_send_data_message(void);
void continue_message(void);
void error_message (uint8_t error_code);

void check_nfc_connect(void);

void text_buffer_init(void);
void get_USB_text(uint8_t value);

void USB_send_notify(void);
void display_received_text(void);

ErrorStatus send_text_to_nfc(void);
void LEDs_blink(void);

app_config_p get_app_config(void);
void Error_Handler(void);

#endif
