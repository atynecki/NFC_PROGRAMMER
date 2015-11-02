
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
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;
  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable peripherals and GPIO Clocks */
  /* Enable GPIO TX/RX clock */
  I2C_SCL_GPIO_CLK_ENABLE();
  I2C_SDA_GPIO_CLK_ENABLE();
  /* Enable I2C1 clock */
  I2C_CLK_ENABLE(); 
  /* Enable DMA2 clock */
  DMAx_CLK_ENABLE();   
  
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
    
  /* Configure the DMA streams */
  /* Configure the DMA handler for Transmission process */ 
  hdma_tx.Instance = DMA1_Channel2;
 
  hdma_tx.Init.Request             = DMA_REQUEST_6; 
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_HIGH;

  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hi2c,hdmatx,hdma_tx);
  
  /* Deinitialize the Stream for new transfer */
  HAL_DMA_DeInit(hi2c->hdmatx);
  
  /* Configure the DMA Stream */
  HAL_DMA_Init(hi2c->hdmatx);      
  
  /* Configure the DMA handler for Transmission process */
  hdma_rx.Instance = DMA1_Channel3;
    
  hdma_rx.Init.Request             = DMA_REQUEST_6;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

  /* Deinitialize the Stream for new transfer */
  HAL_DMA_DeInit(&hdma_rx);
  
  /* Configure the DMA Stream */
  HAL_DMA_Init(&hdma_rx);
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hi2c,hdmarx,hdma_rx);
    
  /* Configure the NVIC for DMA */ 
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0x03, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
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
  
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;

  /* Reset peripherals */
  I2C_FORCE_RESET();
  I2C_RELEASE_RESET();

  /* Disable peripherals and GPIO Clocks */
  /* Configure I2C Tx as alternate function  */
  HAL_GPIO_DeInit(I2C_SCL_GPIO_PORT, I2C_SCL_PIN);
  /* Configure I2C Rx as alternate function  */
  HAL_GPIO_DeInit(I2C_SDA_GPIO_PORT, I2C_SDA_PIN);
   
  /* Disable the DMA Streams */
  /* De-Initialize the DMA Stream associate to transmission process */
  HAL_DMA_DeInit(&hdma_tx); 
  /* De-Initialize the DMA Stream associate to reception process */
  HAL_DMA_DeInit(&hdma_rx);
  
  /* Disable the NVIC for DMA */
  HAL_NVIC_DisableIRQ(DMA1_Channel2_3_IRQn);
}
