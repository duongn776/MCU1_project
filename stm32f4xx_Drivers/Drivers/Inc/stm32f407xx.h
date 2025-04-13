/*
 * stm3f407xx.h
 *
 *  Created on: Apr 8, 2025
 *      Author: nhduong
 */

#ifndef INC_STM3F407XX_H_
#define INC_STM3F407XX_H_

#include<stddef.h>
#include<stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))



/**********************************Processor Specific Details **********************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0          ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1          ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2          ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3          ((__vo uint32_t*)0xE000E10C)


/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0          ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1          ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2          ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3          ((__vo uint32_t*)0xE000E18C)


/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE        ((__vo uint32_t*)0xE000E400)

/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED  4

/*
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASE      0x08000000U    /*!< Base address of Flash memory  */
#define SRAM1_BASE      0x20000000U    /*!< Base address of SRAM1 with 112KB */
#define SRAM2_BASE      0x2001C000U    /*!< Base address of SRAM2 = SRAM1_BASE + 112*1024 */
#define ROM_BASE        0x1FFF0000U    /*!< Base address of system ROM  */
#define SRAM            SRAM1_BASE     /*!< Alias for SRAM1 */

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASE                         0x40000000U
#define APB1PERIPH_BASE                     PERIPH_BASE
#define APB2PERIPH_BASE                     0x40010000U
#define AHB1PERIPH_BASE                     0x40020000U
#define AHB2PERIPH_BASE                     0x50000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */

#define GPIOA_BASE                   (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE                   (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE                   (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE                   (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE                   (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE                   (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE                   (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE                   (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE                   (AHB1PERIPH_BASE + 0x2000)
#define RCC_BASE                     (AHB1PERIPH_BASE + 0x3800)
/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */
#define I2C1_BASE                       (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE                       (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASE                       (APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASE                       (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE                       (APB1PERIPH_BASE + 0x3C00)

#define USART2_BASE                     (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE                     (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE                      (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE                      (APB1PERIPH_BASE + 0x5000)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASE                       (APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASE                       (APB2PERIPH_BASE + 0x3000)
#define SYSCFG_BASE                     (APB2PERIPH_BASE + 0x3800)
#define USART1_BASE                     (APB2PERIPH_BASE + 0x1000)
#define USART6_BASE                     (APB2PERIPH_BASE + 0x1400)


/**********************************peripheral register definition structures **********************************/

typedef struct
{
    __vo uint32_t MODER;                        /*!< GPIO port mode register, Address offset: 0x00 */
    __vo uint32_t OTYPER;                       /*!< GPIO port output type register, Address offset: 0x04 */
    __vo uint32_t OSPEEDR;                      /*!< GPIO port output speed register, Address offset: 0x08 */
    __vo uint32_t PUPDR;                        /*!< GPIO port pull-up/pull-down register, Address offset: 0x0C */
    __vo uint32_t IDR;                          /*!< GPIO port input data register, Address offset: 0x10 */
    __vo uint32_t ODR;                          /*!< GPIO port output data register, Address offset: 0x14 */
    __vo uint32_t BSRR;                         /*!< GPIO port bit set/reset register, Address offset: 0x18 */
    __vo uint32_t LCKR;                         /*!< GPIO port configuration lock register, Address offset: 0x1C */
    __vo uint32_t AFR[2];                       /*!< GPIO alternate function registers, Address offset: 0x20-0x24 */
} GPIO_TypeDef;


/*
 * peripheral register definition structure for RCC
 */
typedef struct
{
  __vo uint32_t CR;            /*!< RCC clock control register, Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /*!< PLL configuration register, Address offset: 0x04 */
  __vo uint32_t CFGR;          /*!< RCC clock configuration register, Address offset: 0x08 */
  __vo uint32_t CIR;           /*!< RCC clock interrupt register, Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /*!< AHB1 peripheral reset register, Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /*!< AHB2 peripheral reset register, Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /*!< AHB3 peripheral reset register, Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, Address offset: 0x1C */
  __vo uint32_t APB1RSTR;      /*!< APB1 peripheral reset register, Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /*!< APB2 peripheral reset register, Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, Address offset: 0x28-0x2C */
  __vo uint32_t AHB1ENR;       /*!< AHB1 peripheral clock enable register, Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /*!< AHB2 peripheral clock enable register, Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /*!< AHB3 peripheral clock enable register, Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, Address offset: 0x3C */
  __vo uint32_t APB1ENR;       /*!< APB1 peripheral clock enable register, Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /*!< APB2 peripheral clock enable register, Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, Address offset: 0x48-0x4C */
  __vo uint32_t AHB1LPENR;     /*!< AHB1 peripheral clock enable in low-power mode, Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /*!< AHB2 peripheral clock enable in low-power mode, Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /*!< AHB3 peripheral clock enable in low-power mode, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, Address offset: 0x5C */
  __vo uint32_t APB1LPENR;     /*!< APB1 peripheral clock enable in low-power mode, Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /*!< APB2 peripheral clock enable in low-power mode, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, Address offset: 0x68-0x6C */
  __vo uint32_t BDCR;          /*!< Backup domain control register, Address offset: 0x70 */
  __vo uint32_t CSR;           /*!< Control and status register, Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, Address offset: 0x78-0x7C */
  __vo uint32_t SSCGR;         /*!< Spread spectrum clock generation register, Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /*!< PLLI2S configuration register, Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /*!< PLLSAI configuration register, Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /*!< Dedicated clock configuration register, Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /*!< Clock gated enable register, Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /*!< Dedicated clock configuration register 2, Address offset: 0x94 */
} RCC_TypeDef;

/*
 * peripheral register definition structure for EXTI
 */
typedef struct
{
    __vo uint32_t IMR;    /*!< Interrupt mask register, Address offset: 0x00 */
    __vo uint32_t EMR;    /*!< Event mask register, Address offset: 0x04 */
    __vo uint32_t RTSR;   /*!< Rising trigger selection register, Address offset: 0x08 */
    __vo uint32_t FTSR;   /*!< Falling trigger selection register, Address offset: 0x0C */
    __vo uint32_t SWIER;  /*!< Software interrupt event register, Address offset: 0x10 */
    __vo uint32_t PR;     /*!< Pending register, Address offset: 0x14 */
} EXTI_TypeDef;

/*
 * peripheral register definition structure for SPI
 */
typedef struct
{
    __vo uint32_t CR1;        /*!< Control register 1, Address offset: 0x00 */
    __vo uint32_t CR2;        /*!< Control register 2, Address offset: 0x04 */
    __vo uint32_t SR;         /*!< Status register, Address offset: 0x08 */
    __vo uint32_t DR;         /*!< Data register, Address offset: 0x0C */
    __vo uint32_t CRCPR;      /*!< CRC polynomial register, Address offset: 0x10 */
    __vo uint32_t RXCRCR;     /*!< RX CRC register, Address offset: 0x14 */
    __vo uint32_t TXCRCR;     /*!< TX CRC register, Address offset: 0x18 */
    __vo uint32_t I2SCFGR;    /*!< I2S configuration register, Address offset: 0x1C */
    __vo uint32_t I2SPR;      /*!< I2S prescaler register, Address offset: 0x20 */
} SPI_TypeDef;

/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
    __vo uint32_t MEMRMP;       /*!< Memory remap register, Address offset: 0x00 */
    __vo uint32_t PMC;          /*!< Peripheral mode configuration register, Address offset: 0x04 */
    __vo uint32_t EXTICR[4];    /*!< External interrupt configuration registers, Address offset: 0x08-0x14 */
    uint32_t      RESERVED1[2];  /*!< Reserved, Address offset: 0x18-0x1C */
    __vo uint32_t CMPCR;        /*!< Compensation cell control register, Address offset: 0x20 */
    uint32_t      RESERVED2[2];  /*!< Reserved, Address offset: 0x24-0x28 */
    __vo uint32_t CFGR;         /*!< Configuration register, Address offset: 0x2C */
} SYSCFG_TypeDef;

/*
 * peripheral register definition structure for I2C
 */
typedef struct
{
  __vo uint32_t CR1;        /*!< Control register 1, Address offset: 0x00 */
  __vo uint32_t CR2;        /*!< Control register 2, Address offset: 0x04 */
  __vo uint32_t OAR1;       /*!< Own address register 1, Address offset: 0x08 */
  __vo uint32_t OAR2;       /*!< Own address register 2, Address offset: 0x0C */
  __vo uint32_t DR;         /*!< Data register, Address offset: 0x10 */
  __vo uint32_t SR1;        /*!< Status register 1, Address offset: 0x14 */
  __vo uint32_t SR2;        /*!< Status register 2, Address offset: 0x18 */
  __vo uint32_t CCR;        /*!< Clock control register, Address offset: 0x1C */
  __vo uint32_t TRISE;      /*!< Rise time register, Address offset: 0x20 */
  __vo uint32_t FLTR;       /*!< Filter register, Address offset: 0x24 */
} I2C_TypeDef;

/*
 * peripheral register definition structure for USART
 */
typedef struct
{
    __vo uint32_t SR;         /*!< Status register, Address offset: 0x00 */
    __vo uint32_t DR;         /*!< Data register, Address offset: 0x04 */
    __vo uint32_t BRR;        /*!< Baud rate register, Address offset: 0x08 */
    __vo uint32_t CR1;        /*!< Control register 1, Address offset: 0x0C */
    __vo uint32_t CR2;        /*!< Control register 2, Address offset: 0x10 */
    __vo uint32_t CR3;        /*!< Control register 3, Address offset: 0x14 */
    __vo uint32_t GTPR;       /*!< Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;


/*
 * peripheral definitions ( Peripheral base addresses typecasted to xxx_TypeDef)
 */

#define GPIOA               ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef*)GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef*)GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef*)GPIOI_BASE)

#define RCC                 ((RCC_TypeDef*)RCC_BASE)
#define EXTI                ((EXTI_TypeDef*)EXTI_BASE)
#define SYSCFG              ((SYSCFG_TypeDef*)SYSCFG_BASE)


#define SPI1                ((SPI_TypeDef*)SPI1_BASE)
#define SPI2                ((SPI_TypeDef*)SPI2_BASE)
#define SPI3                ((SPI_TypeDef*)SPI3_BASE)

#define I2C1                ((I2C_TypeDef*)I2C1_BASE)
#define I2C2                ((I2C_TypeDef*)I2C2_BASE)
#define I2C3                ((I2C_TypeDef*)I2C3_BASE)

#define USART1              ((USART_TypeDef*)USART1_BASE)
#define USART2              ((USART_TypeDef*)USART2_BASE)
#define USART3              ((USART_TypeDef*)USART3_BASE)
#define UART4               ((USART_TypeDef*)UART4_BASE)
#define UART5               ((USART_TypeDef*)UART5_BASE)
#define USART6              ((USART_TypeDef*)USART6_BASE)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_CLK_EN()      (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLK_EN()      (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLK_EN()      (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLK_EN()      (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLK_EN()      (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_CLK_EN()      (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_CLK_EN()      (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_CLK_EN()      (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_CLK_EN()      (RCC->AHB1ENR |= (1 << 8))


/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_CLK_EN() (RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_EN() (RCC->APB1ENR |= (1 << 22))
#define I2C3_CLK_EN() (RCC->APB1ENR |= (1 << 23))


/*
 * Clock Enable Macros for SPIx peripheralsbu
 */
#define SPI1_CLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_EN() (RCC->APB1ENR |= (1 << 15))


/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCCK_EN() (RCC->APB2ENR |= (1 << 4))
#define USART2_PCCK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_PCCK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_PCCK_EN()  (RCC->APB1ENR |= (1 << 19))
#define UART5_PCCK_EN()  (RCC->APB1ENR |= (1 << 20))
#define USART6_PCCK_EN() (RCC->APB1ENR |= (1 << 5))

/*
 * Clock Enable Macros for SYSCFG peripheral
 */
#define SYSCFG_CLK_EN() (RCC->APB2ENR |= (1 << 14))


/*
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_CLK_DIS()     (RCC->AHB1ENR &= ~(1 << 8))

/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_CLK_DIS() (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DIS() (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_CLK_DIS() (RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_CLK_DIS() (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DIS() (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DIS() (RCC->APB1ENR &= ~(1 << 15))


/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_CLK_DIS() (RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLK_DIS() (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DIS() (RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DIS()  (RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DIS()  (RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLK_DIS() (RCC->APB1ENR &= ~(1 << 5))

/*
 * Clock Disable Macros for SYSCFG peripheral
 */
#define SYSCFG_CLK_DIS() (RCC->APB2ENR &= ~(1 << 14))

/*
 *  Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)

/*
 *  Macros to reset SPIx peripherals
 */
#define SPI1_REG_RESET()                do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)  /*!< Reset SPI1 */
#define SPI2_REG_RESET()                do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)  /*!< Reset SPI2 */
#define SPI3_REG_RESET()                do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)  /*!< Reset SPI3 */

/*
 *  Macros to reset I2Cx peripherals
 */
#define I2C1_REG_RESET()             do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)  /*!< Reset I2C1 */
#define I2C2_REG_RESET()             do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)  /*!< Reset I2C2 */
#define I2C3_REG_RESET()             do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)  /*!< Reset I2C3 */

/*
 *  Macros to reset USARTx peripherals
 */
#define USART1_REG_RESET()           do{ (RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4)); }while(0)  /*!< Reset USART1 */
#define USART2_REG_RESET()           do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); }while(0)  /*!< Reset USART2 */
#define USART3_REG_RESET()           do{ (RCC->APB1RSTR |= (1 << 18)); (RCC->APB1RSTR &= ~(1 << 18)); }while(0)  /*!< Reset USART3 */
#define UART4_REG_RESET()            do{ (RCC->APB1RSTR |= (1 << 19)); (RCC->APB1RSTR &= ~(1 << 19)); }while(0)  /*!< Reset UART4 */
#define UART5_REG_RESET()            do{ (RCC->APB1RSTR |= (1 << 20)); (RCC->APB1RSTR &= ~(1 << 20)); }while(0)  /*!< Reset UART5 */

/*
 * This macro returns a code( between 0 to 7) for a given GPIO base address(x)
 */
#define GPIO_PORTCODE(x)      ( (x == GPIOA)?0: \
                                (x == GPIOB)?1: \
                                (x == GPIOC)?2: \
                                (x == GPIOD)?3: \
                                (x == GPIOE)?4: \
                                (x == GPIOF)?5: \
                                (x == GPIOG)?6: \
                                (x == GPIOH)?7: \
                                (x == GPIOI)?8: 0)

/*
 * IRQ Number Definitions for External Interrupts (EXTI)
 */
#define EXTI0_IRQn      6
#define EXTI1_IRQn      7
#define EXTI2_IRQn      8
#define EXTI3_IRQn      9
#define EXTI4_IRQn      10
#define EXTI9_5_IRQn    23
#define EXTI15_10_IRQn  40

/*
 * IRQ Number Definitions for Peripherals
 */
#define SPI1_IRQn           35
#define SPI2_IRQn           36
#define SPI3_IRQn           51
#define I2C1_EV_IRQn      	31
#define I2C1_ER_IRQn      	32
#define USART1_IRQn       	37
#define USART2_IRQn       	38
#define USART3_IRQn       	39
#define UART4_IRQn        	52
#define UART5_IRQn        	53
#define USART6_IRQn       	71


/*
 * Macros for all the possible priority levels
 */
#define IRQ_PRIORITY_0     0
#define IRQ_PRIORITY_1     1
#define IRQ_PRIORITY_2     2
#define IRQ_PRIORITY_3     3
#define IRQ_PRIORITY_4     4
#define IRQ_PRIORITY_5     5
#define IRQ_PRIORITY_6     6
#define IRQ_PRIORITY_7     7
#define IRQ_PRIORITY_15    15


// Some generic macros
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_RESET          RESET
#define FLAG_SET            SET


/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA                     0
#define SPI_CR1_CPOL                     1
#define SPI_CR1_MSTR                     2
#define SPI_CR1_BR                       3
#define SPI_CR1_SPE                      6
#define SPI_CR1_LSBFIRST                 7
#define SPI_CR1_SSI                      8
#define SPI_CR1_SSM                      9
#define SPI_CR1_RXONLY                  10
#define SPI_CR1_DFF                     11
#define SPI_CR1_CRCNEXT                 12
#define SPI_CR1_CRCEN                   13
#define SPI_CR1_BIDIOE                  14
#define SPI_CR1_BIDIMODE                15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN                 0
#define SPI_CR2_TXDMAEN                 1
#define SPI_CR2_SSOE                    2
#define SPI_CR2_FRF                     4
#define SPI_CR2_ERRIE                   5
#define SPI_CR2_RXNEIE                  6
#define SPI_CR2_TXEIE                   7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE                     0
#define SPI_SR_TXE                      1
#define SPI_SR_CHSIDE                   2
#define SPI_SR_UDR                      3
#define SPI_SR_CRCERR                   4
#define SPI_SR_MODF                     5
#define SPI_SR_OVR                      6
#define SPI_SR_BSY                      7
#define SPI_SR_FRE                      8

/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE                      0
#define I2C_CR1_NOSTRETCH               7
#define I2C_CR1_START                   8
#define I2C_CR1_STOP                    9
#define I2C_CR1_ACK                     10
#define I2C_CR1_SWRST                   15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ                    0
#define I2C_CR2_ITERREN                 8
#define I2C_CR2_ITEVTEN                 9
#define I2C_CR2_ITBUFEN                 10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0                    0
#define I2C_OAR1_ADD71                   1
#define I2C_OAR1_ADD98                   8
#define I2C_OAR1_ADDMODE                15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB                      0
#define I2C_SR1_ADDR                    1
#define I2C_SR1_BTF                     2
#define I2C_SR1_ADD10                   3
#define I2C_SR1_STOPF                   4
#define I2C_SR1_RXNE                    6
#define I2C_SR1_TXE                     7
#define I2C_SR1_BERR                    8
#define I2C_SR1_ARLO                    9
#define I2C_SR1_AF                      10
#define I2C_SR1_OVR                     11
#define I2C_SR1_TIMEOUT                 14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL                     0
#define I2C_SR2_BUSY                    1
#define I2C_SR2_TRA                     2
#define I2C_SR2_GENCALL                 4
#define I2C_SR2_DUALF                   7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR                      0
#define I2C_CCR_DUTY                    14
#define I2C_CCR_FS                      15

/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK                   0
#define USART_CR1_RWU                   1
#define USART_CR1_RE                    2
#define USART_CR1_TE                    3
#define USART_CR1_IDLEIE                4
#define USART_CR1_RXNEIE                5
#define USART_CR1_TCIE                  6
#define USART_CR1_TXEIE                 7
#define USART_CR1_PEIE                  8
#define USART_CR1_PS                    9
#define USART_CR1_PCE                   10
#define USART_CR1_WAKE                  11
#define USART_CR1_M                     12
#define USART_CR1_UE                    13
#define USART_CR1_OVER8                 15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD                   0
#define USART_CR2_LBDL                  5
#define USART_CR2_LBDIE                 6
#define USART_CR2_LBCL                  8
#define USART_CR2_CPHA                  9
#define USART_CR2_CPOL                  10
#define USART_CR2_STOP                  12
#define USART_CR2_LINEN                 14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE                   0
#define USART_CR3_IREN                  1
#define USART_CR3_IRLP                  2
#define USART_CR3_HDSEL                 3
#define USART_CR3_NACK                  4
#define USART_CR3_SCEN                  5
#define USART_CR3_DMAR                  6
#define USART_CR3_DMAT                  7
#define USART_CR3_RTSE                  8
#define USART_CR3_CTSE                  9
#define USART_CR3_CTSIE                 10
#define USART_CR3_ONEBIT                11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE                     0
#define USART_SR_FE                     1
#define USART_SR_NE                     2
#define USART_SR_ORE                    3
#define USART_SR_IDLE                   4
#define USART_SR_RXNE                   5
#define USART_SR_TC                     6
#define USART_SR_TXE                    7
#define USART_SR_LBD                    8
#define USART_SR_CTS                    9

#include "stm32f407xx_gpio.h"
#include "stm32f407xx_spi.h"
#include "stm32f407xx_i2c.h"
#include "stm32f407xx_usart.h"
#include "stm32f407xx_rcc.h"

#endif /* INC_STM3F407XX_H_ */
