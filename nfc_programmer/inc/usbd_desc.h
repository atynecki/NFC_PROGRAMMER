
#ifndef __USBD_DESC_H
#define __USBD_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"

#define	DEVICE_ID1          		(0x1FF80050)
#define DEVICE_ID2          		(0x1FF80054)
#define DEVICE_ID3          		(0x1FF80064)

#define	USB_SIZ_STRING_SERIAL		0x1A

extern USBD_DescriptorsTypeDef 	CDC_Desc;

#endif /* __USBD_DESC_H */
