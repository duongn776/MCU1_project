/*
 * stm32f407xx_gpio.h
 *
 *  Created on: Apr 10, 2025
 *      Author: nhduong
 */

#ifndef INC_STM32F407XX_GPIO_H_
#define INC_STM32F407XX_GPIO_H_

#include "stm32f407xx.h"
/*
 * @brief GPIO pin configure struct definition
 */
typedef struct
{
    uint8_t Pin;                /*!< Specifies the GPIO pins to be configured.
                                     This parameter can be any value of @ref GPIO_pins_define       */

    uint8_t Mode;               /*!< Specifies the operating mode for the selected pins.
                                     This parameter can be a value of @ref GPIO_mode_define         */

    uint8_t Pull;               /*!< Specifies the Pull-up or Pull-down activation for the selected pins.
                                     This parameter can be a value of @ref GPIO_pull_define         */

    uint8_t Speed;              /*!< Specifies the speed for the selected pins.
                                     This paramter can be a value of @ref GPIO_speed_define         */

    uint8_t OPType;             /*!< Specifies the output type for the selected pins.
                                     This paramter can be a value of @ref GPIO_optype_define        */

    uint8_t Alternate;          /*!< Peripheral to be connected to the selected pins.
                                     This parameter can be a value of @ref GPIO_alternate_selection */
}GPIO_InitTypeDef;

/*
 * @brief GPIO handle struct definition
 */
typedef struct
{
    GPIO_TypeDef         *pGPIOx;    /*!< Pointer to GPIO peripheral base address    */

    GPIO_InitTypeDef      Init;  /*!< GPIO pin configuration settings            */
}GPIO_HandleTypeDef;

/**
  * @def GPIO_pins_define GPIO pins define
  */
#define GPIO_PIN_0                 0    /* Pin 0 selected    */
#define GPIO_PIN_1                 1    /* Pin 1 selected    */
#define GPIO_PIN_2                 2    /* Pin 2 selected    */
#define GPIO_PIN_3                 3    /* Pin 3 selected    */
#define GPIO_PIN_4                 4    /* Pin 4 selected    */
#define GPIO_PIN_5                 5    /* Pin 5 selected    */
#define GPIO_PIN_6                 6    /* Pin 6 selected    */
#define GPIO_PIN_7                 7    /* Pin 7 selected    */
#define GPIO_PIN_8                 8    /* Pin 8 selected    */
#define GPIO_PIN_9                 9    /* Pin 9 selected    */
#define GPIO_PIN_10                10   /* Pin 10 selected   */
#define GPIO_PIN_11                11   /* Pin 11 selected   */
#define GPIO_PIN_12                12   /* Pin 12 selected   */
#define GPIO_PIN_13                13   /* Pin 13 selected   */
#define GPIO_PIN_14                14   /* Pin 14 selected   */
#define GPIO_PIN_15                15   /* Pin 15 selected   */


/**
  * @def GPIO_mode_define GPIO mode define
  */
#define  GPIO_MODE_INPUT                        0   /*!< Input Mode                   */
#define  GPIO_MODE_OUTPUT                       1   /*!< Output  Mode                 */
#define  GPIO_MODE_ALTERNATE                    2   /*!< Alternate Function           */
#define  GPIO_MODE_ANALOG                       3   /*!< Analog Mode                     */
#define  GPIO_MODE_IT_FALLING                   4   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING                    5   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_RISING_FALLING            6   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */


/**
  * @def GPIO_optype_define GPIO output type define
  */
#define  GPIO_OPTYPE_PP                    0       /*!< Output Push Pull Mode                 */
#define  GPIO_OPTYPE_OD                    1       /*!< Output Open Drain Mode                */

/**
  * @def GPIO_speed_define  GPIO speed define
  */
#define  GPIO_SPEED_FREQ_LOW         0  /*!< IO works at 2 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_MEDIUM      1  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_HIGH        2  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
#define  GPIO_SPEED_FREQ_VERY_HIGH   3  /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */

 /**
   * @def GPIO_pull_define GPIO pull define
   */
#define  GPIO_NOPULL        0   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        1   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      2   /*!< Pull-down activation                */

/*
 * Peripheral Clock setup
 */
void GPIO_ClockControl(GPIO_TypeDef *pGPIOx, uint8_t State);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_HandleTypeDef *hGPIO);
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin);
uint16_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx);
void GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin, uint8_t Value);
void GPIO_WritePort(GPIO_TypeDef *pGPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_TypeDef *pGPIOx, uint8_t GPIO_Pin);

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t State);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandler(uint8_t GPIO_Pin);




#endif /* INC_STM32F407XX_GPIO_H_ */
