################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f407xx_gpio.c \
../Drivers/Src/stm32f407xx_spi.c 

OBJS += \
./Drivers/Src/stm32f407xx_gpio.o \
./Drivers/Src/stm32f407xx_spi.o 

C_DEPS += \
./Drivers/Src/stm32f407xx_gpio.d \
./Drivers/Src/stm32f407xx_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/workspace/MCU_workspace/stm32f4xx_Drivers/Drivers/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32f407xx_gpio.cyclo ./Drivers/Src/stm32f407xx_gpio.d ./Drivers/Src/stm32f407xx_gpio.o ./Drivers/Src/stm32f407xx_gpio.su ./Drivers/Src/stm32f407xx_spi.cyclo ./Drivers/Src/stm32f407xx_spi.d ./Drivers/Src/stm32f407xx_spi.o ./Drivers/Src/stm32f407xx_spi.su

.PHONY: clean-Drivers-2f-Src

