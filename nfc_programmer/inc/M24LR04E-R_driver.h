
#ifndef __M24LR04_H
#define __M24LR04_H

#include "app_manager.h"

#define M24LR04E_I2C_ADDRESS    	 				0xA6
#define M24LR04E_I2C_TIMEOUT             	(uint32_t)0x000FF

#define M24LR04E_WHO_I_AM_ADDRESS         			0x0000
#define M24LR04E_CONFIG_ADDRESS         				0x0005
#define M24LR04E_MESSAGE_CONFIG_ADDRESS     		0x0008
#define M24LR04E_TEXT_ADDRESS            				0x000C  

#define M24LR04E_WHO_I_AM_VALUE									0xE1
#define M24LR04E_MESSAGE_CONFIG_VALUE						0x540265
#define M24LR04E_MESSAGE_START									0x6E
#define M24LR04E_MESSAGE_STOP										0xFE

#define M24LR04E_PAGE_SIZE                      4

void M24LR04E_init(void);
void M24LR04E_deinit(void);

void M24LR04E_read_byte(uint16_t address, uint8_t* buffer);
void M24LR04E_read_buffer(uint16_t address, uint8_t buffer_length, uint8_t* buffer);
void M24LR04E_write_byte(uint16_t address, uint8_t value);
void M24LR04E_write_page(uint16_t address, uint8_t* buffer);

#endif
