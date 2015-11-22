
#include "app_manager.h"

int main(void)
{
  HAL_Init();

	/* Configure the system clock to get correspondent USB clock source */
  system_clock_init();
	
	LED_button_init();
	
	USB_init();
	
	display_welcome_view();
	
	get_app_config()->mode = NFC_DETECT;
	get_app_config()->start_flag = 1;
	get_app_config()->error_code = (uint8_t*)(ERROR_DEAFULT);
	
	HAL_Delay(1000);
	
  /* Infinite loop */
  while (1)
  {
		switch(get_app_config()->mode){
			case NFC_DETECT:
				if(get_app_config()->start_flag == 1){
					get_app_config()->start_flag = 0;
					connect_nfc_board_message();
					BSP_LED_Off(LED3);
					BSP_LED_Off(LED4);
				}
				check_nfc_connect();
				HAL_Delay(100);
				break;
				
			case USB_SEND_TEXT:
				if(get_app_config()->start_flag == 1) {
					get_app_config()->start_flag = 0;
					text_buffer_init();
					USB_send_data_message();
				}
				HAL_Delay(100);
				break;
				
			case TEXT_RECEIVED:
					USB_send_notify();
					display_received_text();
					BSP_LED_On(LED4);
					HAL_Delay(3000);
					get_app_config()->mode = TEXT_SEND;
			break;
			
			case TEXT_SEND:
			if(get_app_config()->start_flag == 1) {
				get_app_config()->start_flag = 0;
				send_text_to_nfc();
				continue_message();
			}
			LEDs_blink();
			break;
			
			default:
				error_message(get_app_config()->error_code);
			break;
				
		}
  }
}
