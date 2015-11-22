
#include "app_manager.h"
#include "picture.h"

app_config_t app_config;
USBD_HandleTypeDef USBD_Device;
uint8_t* message_tab[DISPLAY_LINE_NUMBER];
uint8_t header_buffer[2];
uint8_t notify_buffer[USB_NOTIFY_BUFF_LEN] = {'S','U','C','C','E','S','S'};

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow:
  *  
  *            HSI48 used as USB clock source (USE_USB_CLKSOURCE_CRSHSI48 defined in main.h)
  *              - System Clock source            = HSI
  *              - HSI Frequency(Hz)              = 16000000
  *              - SYSCLK(Hz)                     = 16000000
  *              - HCLK(Hz)                       = 16000000
  *              - AHB Prescaler                  = 1
  *              - APB1 Prescaler                 = 1
  *              - APB2 Prescaler                 = 1
  *              - Flash Latency(WS)              = 0
  *              - Main regulator output voltage  = Scale1 mode
  *
  *            PLL(HSE) used as USB clock source (USE_USB_CLKSOURCE_PLL defined in main.h)
  *              - System Clock source            = PLL (HSE)
  *              - HSE Frequency(Hz)              = 8000000
  *              - SYSCLK(Hz)                     = 32000000
  *              - HCLK(Hz)                       = 32000000
  *              - AHB Prescaler                  = 1
  *              - APB1 Prescaler                 = 1
  *              - APB2 Prescaler                 = 1
  *              - PLL_MUL                        = 12
  *              - PLL_DIV                        = 3
  *              - Flash Latency(WS)              = 1
  *              - Main regulator output voltage  = Scale1 mode
  *
  * @param  None
  * @retval None
  */
void system_clock_init ()
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct ={0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};
	
#if defined (USE_USB_CLKSOURCE_CRSHSI48)
  static RCC_CRSInitTypeDef RCC_CRSInitStruct;
#endif
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
  clocked below the maximum system frequency, to update the voltage scaling value 
  regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Disable Power Control clock */
  __HAL_RCC_PWR_CLK_DISABLE();
  
#if defined (USE_USB_CLKSOURCE_CRSHSI48)
 
  /* Enable HSI Oscillator to be used as System clock source
     Enable HSI48 Oscillator to be used as USB clock source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  HAL_RCC_OscConfig(&RCC_OscInitStruct); 
 
  /* Select HSI48 as USB clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  
  /* Select HSI as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clock dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
    
  /*Configure the clock recovery system (CRS)**********************************/
  
  /*Enable CRS Clock*/
  __HAL_RCC_CRS_CLK_ENABLE(); 
  
  /* Default Synchro Signal division factor (not divided) */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;  
  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;  
  /* HSI48 is synchronized with USB SOF at 1KHz rate */
  RCC_CRSInitStruct.ReloadValue =  __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;  
  /* Set the TRIM[5:0] to the default value*/
  RCC_CRSInitStruct.HSI48CalibrationValue = 0x20;   
  /* Start automatic synchronization */ 
  HAL_RCCEx_CRSConfig (&RCC_CRSInitStruct);
  
#elif defined (USE_USB_CLKSOURCE_PLL)
  
  /* Enable HSE Oscillator */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLMUL      = RCC_PLLMUL_12;
  RCC_OscInitStruct.PLL.PLLDIV      = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }
  
  /*Select PLL 48 MHz output as USB clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    Error_Handler();
  }
  
#endif /*USE_USB_CLKSOURCE_CRSHSI48*/
}

void USB_init ()
{
	/* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* Start Device Process */
  USBD_Start(&USBD_Device);
}

void LED_button_init()
{
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
}


void display_welcome_view ()
{
	BSP_EPD_Init();
	BSP_EPD_DrawImage(0, 0, 72, 172, (uint8_t*) welcome_image);
	BSP_EPD_RefreshDisplay();
}

static void display_message (uint8_t** text_tab, uint8_t line_num)
{
	uint8_t counter;
	BSP_EPD_DrawImage(0, 0, 72, 172, (uint8_t*) header_image);
	
	for(counter = 0; counter<line_num; counter++){
		if(text_tab[counter] !=NULL)
			BSP_EPD_DisplayStringAt(0, LINE(counter), text_tab[counter], CENTER_MODE);
	}
	
	BSP_EPD_RefreshDisplay();
}

static void display_text (uint8_t** text_tab, uint8_t line_num)
{
	uint8_t counter;
	BSP_EPD_DrawImage(0, 0, 72, 172, (uint8_t*) header_image);
	
	for(counter = 0; counter<line_num; counter++){
		if(text_tab[counter] !=NULL)
			BSP_EPD_DisplayStringAt(0, LINE(counter), text_tab[counter], LEFT_MODE);
	}
	
	BSP_EPD_RefreshDisplay();
}

void connect_nfc_board_message ()
{
	message_tab[2] = NULL;
	message_tab[1] = (uint8_t*)(CONNECT_NFC_BOARD_PART1);
	message_tab[0] = (uint8_t*)(CONNECT_NFC_BOARD_PART2);
	
	display_message(message_tab, DISPLAY_LINE_NUMBER);
}

void USB_send_data_message ()
{
	message_tab[2] = NULL;
	message_tab[1] = (uint8_t*)(USB_SEND_TEXT_PART1);
	message_tab[0] = (uint8_t*)(USB_SEND_TEXT_PART2);
	
	display_message(message_tab, DISPLAY_LINE_NUMBER);
}

void continue_message ()
{
	message_tab[2] = (uint8_t*)(CONTINUE_TEXT_PART1);
	message_tab[1] = (uint8_t*)(CONTINUE_TEXT_PART2);
	message_tab[0] = (uint8_t*)(CONTINUE_TEXT_PART3);
	
	display_message(message_tab, DISPLAY_LINE_NUMBER);
}

void error_message (uint8_t* error_code)
{
	message_tab[2] = NULL;
	message_tab[1] = (uint8_t*)(ERROR_TEXT);
	message_tab[0] = error_code;
	
	display_message(message_tab, DISPLAY_LINE_NUMBER);
}

void text_buffer_init ()
{
	uint8_t counter;
	get_app_config()->text_frame_length = 0;
	for(counter=0; counter<MAX_TEXT_LEN+2; counter++){
		get_app_config()->text_frame[counter] = 0;
	}
	get_app_config()->USB_text_received = 0;
	
	get_app_config()->text_frame[get_app_config()->text_frame_length++] = 0xFE;
}

void USB_send_notify ()
{
	USBD_CDC_fops.Control(CDC_SEND_ENCAPSULATED_COMMAND, notify_buffer, USB_NOTIFY_BUFF_LEN);
}

void get_USB_text (uint8_t value)
{
	header_buffer[0] = header_buffer[1];
	header_buffer[1] = value;
	
	if((get_app_config()->USB_text_received == 1)&&(header_buffer[0] == '>') && (header_buffer[1] == '@')){
		get_app_config()->USB_text_received = 0;
		get_app_config()->text_frame[get_app_config()->text_frame_length-1] = 0xFE;
		get_app_config()->mode = TEXT_RECEIVED;
		get_app_config()->start_flag = 1;
	}
	
	if((get_app_config()->USB_text_received == 1) && (get_app_config()->text_frame_length < MAX_TEXT_LEN +1))
		get_app_config()->text_frame[get_app_config()->text_frame_length++] = value;
	
	if((get_app_config()->USB_text_received == 0) &&(header_buffer[0] == '@') && (header_buffer[1] == '<'))
		get_app_config()->USB_text_received = 1;
}

static void parse_text_to_line (uint8_t* text, uint8_t text_length, uint8_t** parse_text)
{
	uint8_t i;
	uint8_t counter;
	uint8_t* text_ptr;
	text_length-=2;
	if(text_length <= SIGN_IN_LINE){
		for(i=0; i<SIGN_IN_LINE; i++){
			parse_text[0][i] = text[i+1];
			parse_text[1][i] = 0;
			parse_text[2][i] = 0;
		}
	}
	else{
	}
}

void display_received_text ()
{
	uint8_t message_part1[SIGN_IN_LINE];
	uint8_t message_part2[SIGN_IN_LINE];
	uint8_t message_part3[SIGN_IN_LINE];
	uint8_t* parse_message_tab[DISPLAY_LINE_NUMBER] = {message_part1, message_part2, message_part3};
	
	parse_text_to_line(get_app_config()->text_frame, get_app_config()->text_frame_length, parse_message_tab);
	
	if(message_part1[0] != 0)
		message_tab[2] = message_part1;
	else
		message_tab[2] = NULL;
	
	if(message_part2[0] != 0)
		message_tab[1] = message_part2;
	else
		message_tab[1] = NULL;
	
	if(message_part3[0] != 0)
		message_tab[0] = message_part3;
	else
		message_tab[0] = NULL;
	
	display_message(message_tab, DISPLAY_LINE_NUMBER);
}

static ErrorStatus check_nfc_ready ()
{
	uint8_t read_value;

	M24LR04E_read_byte(M24LR04E_CONFIG1_ADDRESS, &read_value);
	if (read_value != 0xE1)
     return ERROR;
  
  M24LR04E_read_byte(M24LR04E_CONFIG2_ADDRESS, &read_value);
  if (read_value != 0x54)
      return ERROR;

  return SUCCESS;	
}

void check_nfc_connect ()
{
	uint8_t read_value;

	M24LR04E_init();
	M24LR04E_read_byte(M24LR04E_CONFIG1_ADDRESS, &read_value);
	if (read_value == 0xE1){
		BSP_LED_On(LED3);
		get_app_config()->mode = USB_SEND_TEXT;
		get_app_config()->start_flag = 1;
	}	
}

ErrorStatus send_text_to_nfc ()
{
	uint8_t iteration_num = 0;
	uint8_t counter;
	uint8_t text_length =  get_app_config()->text_frame_length;
  uint8_t *data_pointer = get_app_config()->text_frame;
  uint16_t text_address = M24LR04E_TEXT_ADDRESS;
  
  iteration_num = text_length/4;
  if(iteration_num%4 !=0)
    iteration_num+=1;
  
  M24LR04E_init();
  if(check_nfc_ready() == SUCCESS){
    for(counter=0; counter<iteration_num; counter++){
      M24LR04E_write_page(text_address, data_pointer);
			HAL_Delay(10);
			if(counter < iteration_num - 1){ 
				text_address+=4;
				data_pointer+=4;
			}
    }
  }
  else 
    return ERROR;

  M24LR04E_write_byte(M24LR04E_MESSAGE_LEN_ADDRESS, text_length+1);
  HAL_Delay(10);
  
  M24LR04E_deinit();
  
  return SUCCESS;
}

void LEDs_blink ()
{
	BSP_LED_Toggle(LED3);
	BSP_LED_Toggle(LED4);
	HAL_Delay(400);
}

/**
  * @brief EXTI line detection callback.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
    if(get_app_config()->mode == TEXT_RECEIVED){
			get_app_config()->mode = TEXT_SEND;
			get_app_config()->start_flag = 1;
		}
		else if(get_app_config()->mode == TEXT_SEND){
			get_app_config()->mode = NFC_DETECT;
			get_app_config()->start_flag = 1;
		}
  }
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  I2CxHandle: I2C handle 
  * @note   This example shows a simple way to report end of IT Tx transfer, and 
  *         you can add your own implementation. 
  * @retval None
  */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2CxHandle)
{
  /* Turn LED3 on: Transfer in transmission process is correct */
  BSP_LED_On(LED3);
 
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  I2CxHandle: I2C handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and 
  *         you can add your own implementation.
  * @retval None
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2CxHandle)
{
  /* Turn LED3 on: Transfer in reception process is correct */
  BSP_LED_On(LED3);
}

/**
  * @brief  I2C error callbacks
  * @param  I2CxHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
 void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2CxHandle)
{ 
  while(1)
  {
  } 
}

app_config_p get_app_config ()
{
	return &app_config;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler ()
{
	if(get_app_config()->mode != NFC_DETECT){
		while(1){ }
	}
}
