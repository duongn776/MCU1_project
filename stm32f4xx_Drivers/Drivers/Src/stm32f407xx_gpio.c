/*
 * stm32f407xx_gpio.c
 *
 *  Created on: Apr 12, 2025
 *      Author: nhduong
 */

#include "stm32f407xx_gpio.h"

/**
 * @brief  Enables or disables the clock for the specified GPIO peripheral.
 *
 * @param  pGPIOx pGPIOx where x can be (A..I) to select the GPIO peripheral
 *
 * @param  State: ENABLE or DISABLE.
 *
 * @retval None
 */
void GPIO_ClockControl(GPIO_TypeDef *pGPIOx, uint8_t State)
{
    if(State == ENABLE)
    {
        if(pGPIOx == GPIOA) { GPIOA_CLK_EN(); }
        else if (pGPIOx == GPIOB) { GPIOB_CLK_EN(); }
        else if (pGPIOx == GPIOC) { GPIOC_CLK_EN(); }
        else if (pGPIOx == GPIOD) { GPIOD_CLK_EN(); }
        else if (pGPIOx == GPIOE) { GPIOE_CLK_EN(); }
        else if (pGPIOx == GPIOF) { GPIOF_CLK_EN(); }
        else if (pGPIOx == GPIOG) { GPIOG_CLK_EN(); }
        else if (pGPIOx == GPIOH) { GPIOH_CLK_EN(); }
        else if (pGPIOx == GPIOI) { GPIOI_CLK_EN(); }
    }
    else
    {
        if(pGPIOx == GPIOA) { GPIOA_CLK_DIS(); }
        else if (pGPIOx == GPIOB) { GPIOB_CLK_DIS(); }
        else if (pGPIOx == GPIOC) { GPIOC_CLK_DIS(); }
        else if (pGPIOx == GPIOD) { GPIOD_CLK_DIS(); }
        else if (pGPIOx == GPIOE) { GPIOE_CLK_DIS(); }
        else if (pGPIOx == GPIOF) { GPIOF_CLK_DIS(); }
        else if (pGPIOx == GPIOG) { GPIOG_CLK_DIS(); }
        else if (pGPIOx == GPIOH) { GPIOH_CLK_DIS(); }
        else if (pGPIOx == GPIOI) { GPIOI_CLK_DIS(); }
    }
}


/**
 * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
 *
 * @param  hGPIO Pointer to a GPIO_HandleTypeDef structure that contains
 *         the configuration information for the specified GPIO peripheral.
 *
 * @retval None
 */
void GPIO_Init(GPIO_HandleTypeDef *hGPIO)
{
	uint32_t tempreg = 0;

	// Enable the GPIO clock for the specific GPIO port
	GPIO_ClockControl(hGPIO->pGPIOx, ENABLE);

	// Step 1: Configure the mode of the GPIO pin
	if (hGPIO->Init.Mode <= GPIO_MODE_ANALOG)
	{
		// the non interrupt mode
		tempreg = (hGPIO->Init.Mode << (2 * hGPIO->Init.Pin));
		hGPIO->pGPIOx->MODER &= ~(0x3 << (2 * hGPIO->Init.Pin));
		hGPIO->pGPIOx->MODER |= tempreg;
	}else {
		// the interrupt mode
		if (hGPIO->Init.Mode == GPIO_MODE_IT_FALLING)
		{
			// Configure the FTSR
			EXTI->FTSR |= (1 << hGPIO->Init.Pin);

			// Clear the corresponding the RTSR
			EXTI->RTSR &= ~(1 << hGPIO->Init.Pin);
		}else if (hGPIO->Init.Mode == GPIO_MODE_IT_RISING)
		{
			// Configure the RTSR
			EXTI->RTSR |= (1 << hGPIO->Init.Pin);

			// Clear the corresponding the FTSR
			EXTI->FTSR &= ~(1 << hGPIO->Init.Pin);
		}else {
			// Configure both FTSR and RTSR
			EXTI->FTSR |= (1 << hGPIO->Init.Pin);

			EXTI->RTSR |= (1 << hGPIO->Init.Pin);
		}
		// Configure the GPIO port selection in SYSCFG_EXTICR
		uint32_t temp1 = hGPIO->Init.Pin / 4;
		uint32_t temp2 = hGPIO->Init.Pin % 4;
		uint8_t portCode = GPIO_PORTCODE(hGPIO->pGPIOx);
		SYSCFG_CLK_EN();
		SYSCFG->EXTICR[temp1] = portCode << (temp2 * 4);

		// Enable the EXTI interrupt delivery usig IMR
		EXTI->IMR |= 1 << hGPIO->Init.Pin;
	}

	// Step 2: Configure the speed
	tempreg = (hGPIO->Init.Speed << (2 * hGPIO->Init.Pin));
	hGPIO->pGPIOx->OSPEEDR &= ~(0x3 << (2 * hGPIO->Init.Pin));
	hGPIO->pGPIOx->OSPEEDR |= tempreg;

	// Step 3: Configure the pull settings
	tempreg = (hGPIO->Init.Pull << (2 * hGPIO->Init.Pin));
	hGPIO->pGPIOx->PUPDR &= ~(0x3 << (2 * hGPIO->Init.Pin));
	hGPIO->pGPIOx->PUPDR |= tempreg;

	// Step 4: Configure the output type
	tempreg = (hGPIO->Init.OPType << hGPIO->Init.Pin);
	hGPIO->pGPIOx->OTYPER &= ~(0x1 << hGPIO->Init.Pin);
	hGPIO->pGPIOx->OTYPER |= tempreg;

	// Step 5: Configure the alternate function mode
	if (hGPIO->Init.Alternate == GPIO_MODE_ALTERNATE)
	{
		uint8_t value1, value2;

		value1 = hGPIO->Init.Pin / 8;
		value2 = hGPIO->Init.Pin * 8;

		hGPIO->pGPIOx->AFR[value1] &= ~(0xF << (4 * value2));
		hGPIO->pGPIOx->AFR[value1] |= (hGPIO->Init.Alternate << (4 * value2));

	}
}

/**
 * @brief  Resets the GPIOx peripheral registers to their default reset values.
 *
 * @param  pGPIOx where x can be (A..I) to select the GPIO peripheral
 *
 * @retval None
 */
void GPIO_DeInit(GPIO_TypeDef *pGPIOx)
{
    if(pGPIOx == GPIOA) {GPIOA_REG_RESET();}
    else if (pGPIOx == GPIOB) {GPIOB_REG_RESET();}
    else if (pGPIOx == GPIOC) {GPIOC_REG_RESET();}
    else if (pGPIOx == GPIOD) {GPIOD_REG_RESET();}
    else if (pGPIOx == GPIOE) {GPIOE_REG_RESET();}
    else if (pGPIOx == GPIOF) {GPIOF_REG_RESET();}
    else if (pGPIOx == GPIOG) {GPIOG_REG_RESET();}
    else if (pGPIOx == GPIOH) {GPIOH_REG_RESET();}
    else if (pGPIOx == GPIOI) {GPIOI_REG_RESET();}
}

/**
  * @brief  Reads the specified input pin.
  *
  * @param  pGPIOx where x can be (A..I) to select the GPIO peripheral.
  *
  * @param  GPIO_Pin specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  *
  * @retval The input pin value.
  */
uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin)
{
	// Read (0 or 1) in the input data register
	uint8_t value = (uint8_t)((pGPIOx->IDR >> GPIO_Pin) & 0x00000001);
	return value;
}
/**
  * @brief  Reads the specified input port.
  *
  * @param  pGPIOx where x can be (A..I) to select the GPIO peripheral.
  *
  * @retval The input port value.
  */
uint16_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx)
{
	uint16_t value = (uint16_t)pGPIOx->IDR;
	return value;
}

/**
  * @brief  Sets or clears the selected data bit.
  *
  * @param  pGPIOx where x can be (A..I) to select the GPIO peripheral.
  *
  * @param  GPIO_Pin specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
  *
 * @param  PinState specifies the value to be written to the selected bit.
  *          This parameter can be one of the values:
  *            	GPIO_PIN_RESET: to clear the port pin
  *            	GPIO_PIN_SET: to set the port pin
  *
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin, uint8_t PinState)
{
	if(PinState == GPIO_PIN_SET)
	{
		// Write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << GPIO_Pin);
	}else {
		/// Write 0
		pGPIOx->ODR &= ~(1 << GPIO_Pin);
	}
}

/**
  * @brief  Sets or clears the selected data port bit.
  *
  * @note   This function uses GPIOx_BSRR register to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Pin specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
  *
  * @param  PinState specifies the value to be written to the selected bit.
  *          This parameter can be one of the values:
  *            GPIO_PIN_RESET: to clear the port pin
  *            GPIO_PIN_SET: to set the port pin
  *
  * @retval None
  */
void GPIO_WritePort(GPIO_TypeDef *pGPIOx, uint16_t PinState)
{
	pGPIOx->ODR = PinState;
}

/**
  * @brief  Toggles the specified GPIO pins.
  *
  * @param  GPIOx Where x can be (A..I) to select the GPIO peripheral.
  *
  * @param  GPIO_Pin Specifies the pins to be toggled.
  *
  * @retval None
  */
void GPIO_TogglePin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin)
{
	pGPIOx->ODR ^= (1 << GPIO_Pin);
}

/**
  * @brief  Enables or disables a specific interrupt in the NVIC.
  *
  * @param  IRQNumber IRQ number for the EXTI line or peripheral interrupt.
  *         (e.g., EXTI0_IRQn, EXTI1_IRQn, USART1_IRQn, etc.)
  *
  * @param  State ENABLE or DISABLE.
  *
  * @retval None
  */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t State)
{
	if (State == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}else {
		if (IRQNumber <= 31)
		{
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

/**
  * @brief  Sets the priority of a given interrupt in the NVIC.
  *
  * @param  IRQNumber IRQ number to configure (e.g., EXTI0_IRQn).
  *
  * @param  IRQPriority Priority level (0 = highest, larger = lower priority).
  *
  * @retval None
  */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	// Each NVIC_IPR register holds 4 IRQs, and each priority field is 8 bits wide (only top bits used)
	uint8_t ipr_index = IRQNumber / 4; // Which IPR register
	uint8_t ipr_section = IRQNumber % 4; // Which section inside the IPR register

	uint8_t shift_amount = (8 * ipr_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE + ipr_index) |= (IRQPriority << shift_amount);
}

/**
  * @brief  Handles the interrupt request for the specified GPIO pin.
  *
  * @param  GPIO_Pin The pin number (0 to 15) that triggered the interrupt.
  *
  * @retval None
  */
void GPIO_IRQHandler(uint8_t GPIO_Pin)
{
	if (EXTI->PR & (1 << GPIO_Pin))
	{
		// clear the interrupt pening bit by writting 1
		EXTI->PR |= (1 << GPIO_Pin);
	}
}





