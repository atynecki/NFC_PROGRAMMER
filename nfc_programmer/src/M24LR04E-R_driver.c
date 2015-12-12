
#include "M24LR04E-R_driver.h"

I2C_HandleTypeDef I2CHandle;

/**
  * @brief  initializes the M24LR04E
  * @param  None
  * @retval None
  */
void M24LR04E_init () 
{
	I2CHandle.Instance              = I2C;
  I2CHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  I2CHandle.Init.Timing           = I2C_TIMING_100KHZ;
  I2CHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  I2CHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  I2CHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  I2CHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
  I2CHandle.Init.OwnAddress1      = 0xFE;
  I2CHandle.Init.OwnAddress2      = 0xFE;
  if(HAL_I2C_Init(&I2CHandle) != HAL_OK) {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();    
  }
}

/**
  * @brief  deinitializes the M24LR04E
  * @param  None
  * @retval None
  */
void M24LR04E_deinit () 
{
  if(HAL_I2C_DeInit(&I2CHandle) != HAL_OK) {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();    
  }
}

/**
  * @brief read one byte of data from the M24LR16E EEPROM
  * @param[in] EEPROM's internal address to read from
  * @param[in] pointer to the buffer that receives the data read from the EEPROM
  * @retval None
  */
void M24LR04E_read_byte (uint16_t address, uint8_t* buffer) {
  int32_t I2C_TimeOut = M24LR04E_I2C_TIMEOUT;

  if(HAL_I2C_Mem_Read(&I2CHandle, M24LR04E_I2C_ADDRESS, address, I2C_MEMADD_SIZE_16BIT, buffer, 1, I2C_TimeOut) != HAL_OK)
  {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();
  } 
}

/**
  * @brief read a block of data from the M24LR16E EEPROM
	* @param[in] EEPROM's internal address to read from
	* @param[in] number of bytes to read from the EEPROM
  * @param[in] pointer to the buffer that receives the data read from the EEPROM
  * @retval None
  */
void M24LR04E_read_buffer (uint16_t address, uint8_t buffer_length, uint8_t* buffer) {
  int32_t I2C_TimeOut = M24LR04E_I2C_TIMEOUT;
	
	if(HAL_I2C_Mem_Read(&I2CHandle, M24LR04E_I2C_ADDRESS, address, I2C_MEMADD_SIZE_16BIT, buffer, buffer_length, I2C_TimeOut) != HAL_OK)
  {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();
  }
}

/**
  * @brief  write one byte to EEPROM memory address
	* @param[in] EEPROM's internal address to write
  * @param[in] value to be written to M24LR16E
  * @retval None
  */
void M24LR04E_write_byte (uint16_t address, uint8_t value) {
  int32_t I2C_TimeOut = M24LR04E_I2C_TIMEOUT;
  
  if(HAL_I2C_Mem_Write(&I2CHandle, M24LR04E_I2C_ADDRESS, address, I2C_MEMADD_SIZE_16BIT, &value, 1, I2C_TimeOut) != HAL_OK)
  {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();
  } 
}

/**
  * @brief  write 4 bytes (page) to EEPROM memory address
  * @param[in] EEPROM's internal address to write
  * @param[in] pointer to the buffer to be written to M24LR16E
  * @retval None
  */
void M24LR04E_write_page (uint16_t address, uint8_t* buffer) {
  int32_t I2C_TimeOut = M24LR04E_I2C_TIMEOUT;
	
	if(HAL_I2C_Mem_Write(&I2CHandle, M24LR04E_I2C_ADDRESS, address, I2C_MEMADD_SIZE_16BIT, buffer, M24LR04E_PAGE_SIZE, I2C_TimeOut) != HAL_OK)
  {
		get_app_config()->error_code = I2C_ERROR;
    Error_Handler();
  } 
}
