/*
 * stm32f407xx_gpio.c
 *
 *  Created on: Apr 12, 2025
 *      Author: nhduong
 */

#include "stm32f407xx_gpio.h"

/**
 * @brief  Enables or disables the clock for the specified GPIO peripheral.
 * @param  pGPIOx: Pointer to GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  State: ENABLE or DISABLE.
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
 * @param  hGPIO: Pointer to a GPIO_Handle_t structure that contains
 *         the configuration information for the specified GPIO peripheral.
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
