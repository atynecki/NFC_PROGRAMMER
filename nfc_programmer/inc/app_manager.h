
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

#define TEXT			"Artur krolem kodu"

void Error_Handler(void);

void system_clock_init(void);

#endif /* __MAIN_H */
