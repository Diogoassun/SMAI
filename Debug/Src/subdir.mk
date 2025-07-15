################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32f103C8T6_it.c \
../Src/afio.c \
../Src/dma.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/ir.c \
../Src/iwdg.c \
../Src/main.c \
../Src/nrf24l01.c \
../Src/pwm.c \
../Src/pwr.c \
../Src/rcc.c \
../Src/rtc.c \
../Src/spi.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/timer.c 

OBJS += \
./Src/STM32f103C8T6_it.o \
./Src/afio.o \
./Src/dma.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/ir.o \
./Src/iwdg.o \
./Src/main.o \
./Src/nrf24l01.o \
./Src/pwm.o \
./Src/pwr.o \
./Src/rcc.o \
./Src/rtc.o \
./Src/spi.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/timer.o 

C_DEPS += \
./Src/STM32f103C8T6_it.d \
./Src/afio.d \
./Src/dma.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/ir.d \
./Src/iwdg.d \
./Src/main.d \
./Src/nrf24l01.d \
./Src/pwm.d \
./Src/pwr.d \
./Src/rcc.d \
./Src/rtc.d \
./Src/spi.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB=STM32F103xB -c -I../Inc -I../F1_Header/Include -I../F1_Header/Device/ST/STM32F1xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/STM32f103C8T6_it.cyclo ./Src/STM32f103C8T6_it.d ./Src/STM32f103C8T6_it.o ./Src/STM32f103C8T6_it.su ./Src/afio.cyclo ./Src/afio.d ./Src/afio.o ./Src/afio.su ./Src/dma.cyclo ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/ir.cyclo ./Src/ir.d ./Src/ir.o ./Src/ir.su ./Src/iwdg.cyclo ./Src/iwdg.d ./Src/iwdg.o ./Src/iwdg.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/nrf24l01.cyclo ./Src/nrf24l01.d ./Src/nrf24l01.o ./Src/nrf24l01.su ./Src/pwm.cyclo ./Src/pwm.d ./Src/pwm.o ./Src/pwm.su ./Src/pwr.cyclo ./Src/pwr.d ./Src/pwr.o ./Src/pwr.su ./Src/rcc.cyclo ./Src/rcc.d ./Src/rcc.o ./Src/rcc.su ./Src/rtc.cyclo ./Src/rtc.d ./Src/rtc.o ./Src/rtc.su ./Src/spi.cyclo ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

