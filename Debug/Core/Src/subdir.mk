################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADS7843.c \
../Core/Src/BMP390.c \
../Core/Src/BQ40Z50.c \
../Core/Src/Buttons.c \
../Core/Src/CD4052.c \
../Core/Src/ELSPIRE_OS.c \
../Core/Src/GlobalVariables.c \
../Core/Src/IS42S16400J.c \
../Core/Src/ModBusMaster.c \
../Core/Src/ModBusSlave.c \
../Core/Src/Save.c \
../Core/Src/SwitchOff.c \
../Core/Src/ThermoCalculator.c \
../Core/Src/ThermocoupleMath.c \
../Core/Src/ThermoresistanceMath.c \
../Core/Src/UART_IN.c \
../Core/Src/UART_OUT.c \
../Core/Src/UART_PRESSURE.c \
../Core/Src/Units.c \
../Core/Src/VirtualComPort.c \
../Core/Src/crc.c \
../Core/Src/dma.c \
../Core/Src/fmc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/ltdc.c \
../Core/Src/main.c \
../Core/Src/quadspi.c \
../Core/Src/rtc.c \
../Core/Src/sdmmc.c \
../Core/Src/spi.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_hal_timebase_tim.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

C_DEPS += \
./Core/Src/ADS7843.d \
./Core/Src/BMP390.d \
./Core/Src/BQ40Z50.d \
./Core/Src/Buttons.d \
./Core/Src/CD4052.d \
./Core/Src/ELSPIRE_OS.d \
./Core/Src/GlobalVariables.d \
./Core/Src/IS42S16400J.d \
./Core/Src/ModBusMaster.d \
./Core/Src/ModBusSlave.d \
./Core/Src/Save.d \
./Core/Src/SwitchOff.d \
./Core/Src/ThermoCalculator.d \
./Core/Src/ThermocoupleMath.d \
./Core/Src/ThermoresistanceMath.d \
./Core/Src/UART_IN.d \
./Core/Src/UART_OUT.d \
./Core/Src/UART_PRESSURE.d \
./Core/Src/Units.d \
./Core/Src/VirtualComPort.d \
./Core/Src/crc.d \
./Core/Src/dma.d \
./Core/Src/fmc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/ltdc.d \
./Core/Src/main.d \
./Core/Src/quadspi.d \
./Core/Src/rtc.d \
./Core/Src/sdmmc.d \
./Core/Src/spi.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_hal_timebase_tim.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 

OBJS += \
./Core/Src/ADS7843.o \
./Core/Src/BMP390.o \
./Core/Src/BQ40Z50.o \
./Core/Src/Buttons.o \
./Core/Src/CD4052.o \
./Core/Src/ELSPIRE_OS.o \
./Core/Src/GlobalVariables.o \
./Core/Src/IS42S16400J.o \
./Core/Src/ModBusMaster.o \
./Core/Src/ModBusSlave.o \
./Core/Src/Save.o \
./Core/Src/SwitchOff.o \
./Core/Src/ThermoCalculator.o \
./Core/Src/ThermocoupleMath.o \
./Core/Src/ThermoresistanceMath.o \
./Core/Src/UART_IN.o \
./Core/Src/UART_OUT.o \
./Core/Src/UART_PRESSURE.o \
./Core/Src/Units.o \
./Core/Src/VirtualComPort.o \
./Core/Src/crc.o \
./Core/Src/dma.o \
./Core/Src/fmc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/ltdc.o \
./Core/Src/main.o \
./Core/Src/quadspi.o \
./Core/Src/rtc.o \
./Core/Src/sdmmc.o \
./Core/Src/spi.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_hal_timebase_tim.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/gui/include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADS7843.d ./Core/Src/ADS7843.o ./Core/Src/ADS7843.su ./Core/Src/BMP390.d ./Core/Src/BMP390.o ./Core/Src/BMP390.su ./Core/Src/BQ40Z50.d ./Core/Src/BQ40Z50.o ./Core/Src/BQ40Z50.su ./Core/Src/Buttons.d ./Core/Src/Buttons.o ./Core/Src/Buttons.su ./Core/Src/CD4052.d ./Core/Src/CD4052.o ./Core/Src/CD4052.su ./Core/Src/ELSPIRE_OS.d ./Core/Src/ELSPIRE_OS.o ./Core/Src/ELSPIRE_OS.su ./Core/Src/GlobalVariables.d ./Core/Src/GlobalVariables.o ./Core/Src/GlobalVariables.su ./Core/Src/IS42S16400J.d ./Core/Src/IS42S16400J.o ./Core/Src/IS42S16400J.su ./Core/Src/ModBusMaster.d ./Core/Src/ModBusMaster.o ./Core/Src/ModBusMaster.su ./Core/Src/ModBusSlave.d ./Core/Src/ModBusSlave.o ./Core/Src/ModBusSlave.su ./Core/Src/Save.d ./Core/Src/Save.o ./Core/Src/Save.su ./Core/Src/SwitchOff.d ./Core/Src/SwitchOff.o ./Core/Src/SwitchOff.su ./Core/Src/ThermoCalculator.d ./Core/Src/ThermoCalculator.o ./Core/Src/ThermoCalculator.su ./Core/Src/ThermocoupleMath.d ./Core/Src/ThermocoupleMath.o ./Core/Src/ThermocoupleMath.su ./Core/Src/ThermoresistanceMath.d ./Core/Src/ThermoresistanceMath.o ./Core/Src/ThermoresistanceMath.su ./Core/Src/UART_IN.d ./Core/Src/UART_IN.o ./Core/Src/UART_IN.su ./Core/Src/UART_OUT.d ./Core/Src/UART_OUT.o ./Core/Src/UART_OUT.su ./Core/Src/UART_PRESSURE.d ./Core/Src/UART_PRESSURE.o ./Core/Src/UART_PRESSURE.su ./Core/Src/Units.d ./Core/Src/Units.o ./Core/Src/Units.su ./Core/Src/VirtualComPort.d ./Core/Src/VirtualComPort.o ./Core/Src/VirtualComPort.su ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/crc.su ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fmc.d ./Core/Src/fmc.o ./Core/Src/fmc.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/ltdc.d ./Core/Src/ltdc.o ./Core/Src/ltdc.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/quadspi.d ./Core/Src/quadspi.o ./Core/Src/quadspi.su ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sdmmc.d ./Core/Src/sdmmc.o ./Core/Src/sdmmc.su ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_hal_timebase_tim.d ./Core/Src/stm32h7xx_hal_timebase_tim.o ./Core/Src/stm32h7xx_hal_timebase_tim.su ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

