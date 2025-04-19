/*
 * stm32f407xx_spi.c
 *
 *  Created on: Apr 17, 2025
 *      Author: nhduong
 */

#include "stm32f407xx_spi.h"

/*
 * @def SPI Private Functions
 */
static void SPI_TxHandle_ISR(SPI_HandleTypeDef *hspi);
static void SPI_RxHandle_ISR(SPI_HandleTypeDef *hspi);
static void SPI_OvrHandle_ISR(SPI_HandleTypeDef *hspi);



/**
 * @brief  Enables or disables the clock for the specified SPIx peripheral.
 *
 * @param  pGPIOx where x can be (1,2 or 3) to select the SPI peripheral
 *
 * @param  State: ENABLE or DISABLE.
 *
 * @retval None
 */
void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t State)
{
	if (State == ENABLE)
	{
		if (pSPIx == SPI1)
		{
			SPI1_CLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_CLK_EN();
		}else {
			SPI3_CLK_EN();
		}
	}else {
		if (pSPIx == SPI1)
		{
			SPI1_CLK_DIS();
		}else if (pSPIx == SPI2)
		{
			SPI2_CLK_DIS();
		}else {
			SPI3_CLK_DIS();
		}
	}
}
/**
  * @brief  Initialize the SPI according to the specified parameters
  *         in the SPI_InitTypeDef and initialize the associated handle.
  *
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  *
  * @retval None
  */
void SPI_Init(SPI_HandleTypeDef *hspi)
{
	uint32_t tempreg = 0;

	// 1. Enable the SPI peripheral clock
	SPI_PeriClockControl(hspi->pSPIx, ENABLE);

	// 2. Configure device mode (Master/Slave)
	tempreg |= hspi->Init.Mode << SPI_CR1_MSTR;

	// 3. Configure bus configuration (Full-Duplex, Half-Duplex, or Simplex RX-only)
	if (hspi->Init.Direction == SPI_DIRECTION_FULLDUPLEX)
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if (hspi->Init.Direction == SPI_DIRECTION_HALFDUPLEX)
	{
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}
	else // SPI_DIRECTION_SIMPLEX_RXONLY
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	// 4. Set the Baud Rate Prescaler
	tempreg |= hspi->Init.BaudRatePrescaler << SPI_CR1_BR;

	// 5. Configure Data Frame Format (8-bit or 16-bit)
	tempreg |= hspi->Init.DataSize << SPI_CR1_DFF;

	// 6. Set Clock Polarity (CPOL)
	tempreg |= hspi->Init.CLKPolarity << SPI_CR1_CPOL;

	// 7. Set Clock Phase (CPHA)
	tempreg |= hspi->Init.CLKPhase << SPI_CR1_CPHA;

	// 8. Configure NSS management using helper functions
	if (hspi->Init.NSS == SPI_NSS_SOFT)
	{
		// Software Slave Management
		tempreg |= (1 << SPI_CR1_SSM);
		SPI_SSIConfig(hspi->pSPIx, ENABLE);  // Set SSI bit
	}
	else // SPI_NSS_HARD
	{
		tempreg &= ~(1 << SPI_CR1_SSM);
		SPI_SSOEConfig(hspi->pSPIx, ENABLE); // Enable SSOE bit
	}

	// 10. Write final configuration to CR1 register
	hspi->pSPIx->CR1 = tempreg;
}

/**
  * @brief  De-Initialize the SPI peripheral.
  *
  * @param  pSPIx pointer to a SPI_TypeDef structure that contains
  *               the configuration information for SPI module.
  *
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef *pSPIx)
{
	if (pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}else if (pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if (pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}
/**
  * @brief  Enable or disable the SPI peripheral.
  *
  * @param  pSPIx Pointer to the SPI peripheral base address.
  *
  * @param  State Set to ENABLE or DISABLE.
  *
  * @retval None
  */
void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t State)
{
	if (State == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	} else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/**
  * @brief  Configure the Internal Slave Select (SSI) bit.
  *
  *         This is useful when software slave management (SSM) is enabled.
  *         The SSI bit is used to select the master mode by simulating NSS.
  *
  * @param  pSPIx Pointer to the SPI peripheral base address.
  *
  * @param  State Set to ENABLE or DISABLE.
  *
  * @retval None
  */
void SPI_SSIConfig(SPI_TypeDef *pSPIx, uint8_t State)
{
	if (State == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	} else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

/**
  * @brief  Configure the Slave Select Output Enable (SSOE).
  *
  *         When SSOE is enabled and the SPI is in master mode, the NSS pin is
  *         automatically managed by hardware (pulled low when enabled).
  *
  * @param  pSPIx Pointer to the SPI peripheral base address.
  * @param  State Set to ENABLE or DISABLE.
  *
  * @retval None
  */
void SPI_SSOEConfig(SPI_TypeDef *pSPIx, uint8_t State)
{
	if (State == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	} else {
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

/**
  * @brief  Transmit an amount of data in blocking mode.
  *
  * @param  pSPIx pointer to SPI peripheral (e.g., SPI1, SPI2, SPI3).
  *
  * @param  pData pointer to data buffer (uint8_t or uint16_t).
  *
  * @param  Len number of data elements to be sent.
  *
  * @retval None
  */
void SPI_Transmit(SPI_TypeDef *pSPIx, uint8_t *pData, uint32_t Len)
{
	while (Len > 0)
	{
		// Wait until TXE (Transmit buffer empty) flag is set
		while(SPI_GetFlag(pSPIx, SPI_FLAG_TXE) == FLAG_RESET);

		// Check the DFF (Data Frame Format) bit in CR1 to determine data size
		if ((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			// 16-bit data format
			// Load 2 bytes (uint16_t) into the data register
			pSPIx->DR = *((uint16_t*)pData);

			// Decrease length by 2 and move data pointer by 2
			Len -= 2;
			pData += 2;
		}
		else
		{
			// 8-bit data format
			// Load 1 byte (uint8_t) into the data register
			pSPIx->DR = *pData;

			// Decrease length by 1 and move data pointer by 1
			Len--;
			pData++;
		}
	}

	// Wait until BSY (Busy flag) is reset, to make sure SPI is done transmitting
	while(SPI_GetFlag(pSPIx, SPI_FLAG_BSY));
}

/**
  * @brief  Receive an amount of data in blocking mode.
  *
  * @param  pSPIx pointer to SPI peripheral (e.g., SPI1, SPI2, SPI3)
  *
  * @param  pRxBuffer pointer to data buffer (uint8_t or uint16_t) to store received data.
  *
  * @param  Len number of data elements to be received.
  *
  * @retval None
  */
void SPI_Receive(SPI_TypeDef *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while (Len > 0)
	{
		// Wait until RXNE (Receive buffer not empty) flag is set
		while(SPI_GetFlag(pSPIx, SPI_FLAG_RXNE) == FLAG_RESET);

		// Check the DFF (Data Frame Format) bit in CR1 to determine data size
		if ((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			// 16-bit data format
			// Read 2 bytes (uint16_t) from data register into receive buffer
			*((uint16_t*)pRxBuffer) = pSPIx->DR;

			// Decrease length by 2 and move buffer pointer forward by 2
			Len -= 2;
			pRxBuffer += 2;
		}
		else
		{
			// 8-bit data format
			// Read 1 byte (uint8_t) from data register into receive buffer
			*pRxBuffer = pSPIx->DR;

			// Decrease length by 1 and move buffer pointer forward by 1
			Len--;
			pRxBuffer++;
		}
	}

	// Wait until BSY (Busy flag) is reset, to ensure SPI is not busy
	while(SPI_GetFlag(pSPIx, SPI_FLAG_BSY));
}

/**
  * @brief  Transmit an amount of data in non-blocking mode using Interrupts.
  *
  * @param  hspi Pointer to a SPI_HandleTypeDef structure that contains
  *              the configuration information for the SPI module.
  *
  * @param  pData Pointer to data buffer (uint8_t or uint16_t data elements).
  *
  * @param  Len   Amount of data elements to be sent.
  *
  * @retval SPI state (e.g., SPI_STATE_BUSY_TX or SPI_STATE_READY)
  */
uint8_t SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Len)
{
    // get current TX state
    uint8_t State = hspi->TxState;

    if (State != SPI_STATE_BUSY_TX)
    {
        // Save the TX buffer address and length info
        hspi->pTxBuff = pData;
        hspi->TxLen = Len;

        // Mark SPI as busy in transmission
        hspi->TxState = SPI_STATE_BUSY_TX;

        // Enable the TXEIE (TX buffer empty interrupt enable) bit in CR2
        // to get interrupt when TXE flag is set
        hspi->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    }
    return State;
}

/**
  * @brief  Receive an amount of data in non-blocking mode using Interrupt.
  *
  * @param  hspi    Pointer to a SPI_HandleTypeDef structure that contains
  *                 the configuration information for the SPI module.
  *
  * @param  pData   Pointer to reception data buffer (uint8_t or uint16_t elements).
  *
  * @param  Len     Amount of data elements to be received.
  *
  * @retval SPI state (e.g., SPI_STATE_BUSY_RX or SPI_STATE_READY)
  */
uint8_t SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Len)
{
    // Get current RX state
    uint8_t State = hspi->RxState;

    if (State != SPI_STATE_BUSY_RX)
    {
        // Save the RX buffer address and length info
        hspi->pRxBuff = pData;
        hspi->RxLen = Len;

        // Mark the SPI peripheral as busy in RX
        hspi->RxState = SPI_STATE_BUSY_RX;

        // Enable RXNEIE (Receive Buffer Not Empty Interrupt Enable)
        // to trigger interrupt when RXNE flag is set
        hspi->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
    }
    return State;
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
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t State)
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
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	// Each NVIC_IPR register holds 4 IRQs, and each priority field is 8 bits wide (only top bits used)
	uint8_t ipr_index = IRQNumber / 4; // Which IPR register
	uint8_t ipr_section = IRQNumber % 4; // Which section inside the IPR register

	uint8_t shift_amount = (8 * ipr_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE + ipr_index) |= (IRQPriority << shift_amount);
}

/**
  * @brief  Handle SPI interrupt request.
  *
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  *
  * @retval None
  */
void SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
	uint8_t itflag, itsource;

	// check SPI in tx mode
	itflag = hspi->pSPIx->SR & (1 << SPI_SR_TXE);
	itsource = hspi->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if (itflag && itsource)
	{
		// handle txe
		SPI_TxHandle_ISR(hspi);
	}

	// check SPI in rx mode
	itflag = hspi->pSPIx->SR & (1 << SPI_SR_RXNE);
	itsource = hspi->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

	if (itflag && itsource)
	{
		// handle rxne
		SPI_RxHandle_ISR(hspi);
	}

	// check SPI for ovr flag
	itflag = hspi->pSPIx->SR & (1 << SPI_SR_OVR);
	itsource = hspi->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);

	if (itflag && itsource)
	{
		// handle ovr error
		SPI_OvrHandle_ISR(hspi);
	}
}

/**
  * @brief  Close SPI transmission (disable TXE interrupt, reset state).
  *
  * @param  hspi: Pointer to the SPI handle structure.
  *
  * @retval None
  */
void SPI_CloseTx(SPI_HandleTypeDef *hspi)
{
	hspi->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE);
	hspi->pTxBuff = NULL;
	hspi->TxLen = 0;
	hspi->TxState = SPI_STATE_READY;

}

/**
  * @brief  Close SPI reception (disable RXNE interrupt, reset state).
  *
  * @param  hspi: Pointer to the SPI handle structure.
  *
  * @retval None
  */
void SPI_CloseRx(SPI_HandleTypeDef *hspi)
{
	hspi->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE);
	hspi->pRxBuff = NULL;
	hspi->RxLen = 0;
	hspi->RxState = SPI_STATE_READY;

}

/**
  * @brief  Clear the Overrun (OVR) flag by reading DR and SR.
  *
  * @param  pSPIx: Pointer to the SPI peripheral base address.
  *
  * @retval None
  */
void SPI_ClearOVRFlag(SPI_TypeDef *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}

// help function

/**
  * @brief  TXE interrupt handler for SPI transmission.
  * @param  hspi: Pointer to the SPI handle structure.
  * @retval None
  */
static void SPI_TxHandle_ISR(SPI_HandleTypeDef *hspi)
{
	if (hspi->pSPIx->CR1 & (1 << SPI_CR1_DFF)) // 16-bit mode
	{
		hspi->pSPIx->DR = *((uint16_t *)hspi->pTxBuff);
		hspi->TxLen -= 2;
		hspi->pTxBuff += 2;
	}
	else // 8-bit mode
	{
		hspi->pSPIx->DR = *(hspi->pTxBuff);
		hspi->TxLen--;
		hspi->pTxBuff++;
	}

	if (hspi->TxLen == 0)
	{
		SPI_CloseTx(hspi);
		SPI_ApplicationEventCallback(hspi, SPI_EVENT_TX_COMPLETE);
	}
}

/**
  * @brief  RXNE interrupt handler for SPI reception.
  *
  * @param  hspi: Pointer to the SPI handle structure.
  *
  * @retval None
  */
static void SPI_RxHandle_ISR(SPI_HandleTypeDef *hspi)
{
	if (hspi->pSPIx->CR1 & (1 << SPI_CR1_DFF)) // 16-bit mode
	{
		*((uint16_t *)hspi->pRxBuff) = (uint16_t)hspi->pSPIx->DR;
		hspi->RxLen -= 2;
		hspi->pRxBuff += 2;
	}
	else // 8-bit mode
	{
		*(hspi->pRxBuff) = (uint8_t)hspi->pSPIx->DR;
		hspi->RxLen--;
		hspi->pRxBuff++;
	}

	if (hspi->RxLen == 0)
	{
		SPI_CloseRx(hspi);
		SPI_ApplicationEventCallback(hspi, SPI_EVENT_RX_COMPLETE);
	}
}

/**
  * @brief  OVR (Overrun) error interrupt handler.
  *
  * @param  hspi: Pointer to the SPI handle structure.
  *
  * @retval None
  */
static void SPI_OvrHandle_ISR(SPI_HandleTypeDef *hspi)
{
	uint8_t temp;
	if (hspi->TxState != SPI_STATE_BUSY_TX)
	{
		temp = hspi->pSPIx->DR;
		temp = hspi->pSPIx->SR;
	}
	(void)temp;
	SPI_ApplicationEventCallback(hspi, SPI_ERROR_OVR);
}



/**
  * @brief  Application callback for SPI events (TX, RX complete, OVR error).
  *
  * @param  hspi: Pointer to the SPI handle structure.
  *
  * @param  AppEv: SPI event type (e.g., TX_COMPLETE, RX_COMPLETE, OVR).
  *
  * @retval None
  */
__weak void SPI_ApplicationEventCallback(SPI_HandleTypeDef *hspi, uint8_t AppEv)
{
	// Weak implementation, user should override this in their application code
}







