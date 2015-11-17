
/* Includes ------------------------------------------------------------------*/
#include "app_manager.h"

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */ 
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */
}


/**
  * @brief I2C MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - DMA configuration for transmission request by peripheral 
  *           - NVIC configuration for DMA interrupt request enable
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable peripherals and GPIO Clocks */
  /* Enable GPIO TX/RX clock */
  I2C_SCL_GPIO_CLK_ENABLE();
  I2C_SDA_GPIO_CLK_ENABLE();
  /* Enable I2C1 clock */
  I2C_CLK_ENABLE();   
  
  /* Configure peripheral GPIO */  
  /* I2C TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = I2C_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH  ;
  GPIO_InitStruct.Alternate = I2C_SCL_AF;
  
  HAL_GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStruct);
    
  /* I2C RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = I2C_SDA_PIN;
  GPIO_InitStruct.Alternate = I2C_SDA_AF;
    
  HAL_GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
    
  /* Configure the NVIC for I2C */ 
  HAL_NVIC_SetPriority(I2C_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(I2C_IRQn);
}

/**
  * @brief I2C MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
  /* Reset peripherals */
  I2C_FORCE_RESET();
  I2C_RELEASE_RESET();

  /* Disable peripherals and GPIO Clocks */
  /* Configure I2C Tx as alternate function  */
  HAL_GPIO_DeInit(I2C_SCL_GPIO_PORT, I2C_SCL_PIN);
  /* Configure I2C Rx as alternate function  */
  HAL_GPIO_DeInit(I2C_SDA_GPIO_PORT, I2C_SDA_PIN);
  
  /*##-3- Disable the NVIC for I2C ###########################################*/
  HAL_NVIC_DisableIRQ(I2C_IRQn);
}
