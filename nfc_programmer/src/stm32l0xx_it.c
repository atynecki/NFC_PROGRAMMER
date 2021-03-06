
#include "app_manager.h"

extern I2C_HandleTypeDef I2CHandle;
extern PCD_HandleTypeDef hpcd;

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  Error_Handler();
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/**
  * @brief  This function handles Switch interrupt
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

/**
  * @brief  This function handles I2C event interrupt request  
  * @param  None
  * @retval None   
  */
void I2C_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&I2CHandle);
  HAL_I2C_ER_IRQHandler(&I2CHandle);
}

/**
  * @brief  This function handles USB Handler
  * @param  None
  * @retval None
  */
void USB_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd);
}
