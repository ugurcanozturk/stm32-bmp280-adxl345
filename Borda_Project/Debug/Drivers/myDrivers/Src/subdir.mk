################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/myDrivers/Src/ADXL.c \
../Drivers/myDrivers/Src/BMP280.c 

OBJS += \
./Drivers/myDrivers/Src/ADXL.o \
./Drivers/myDrivers/Src/BMP280.o 

C_DEPS += \
./Drivers/myDrivers/Src/ADXL.d \
./Drivers/myDrivers/Src/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/myDrivers/Src/%.o Drivers/myDrivers/Src/%.su: ../Drivers/myDrivers/Src/%.c Drivers/myDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/EmbeddedDrivers/Borda_Project/Drivers/myDrivers/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-myDrivers-2f-Src

clean-Drivers-2f-myDrivers-2f-Src:
	-$(RM) ./Drivers/myDrivers/Src/ADXL.d ./Drivers/myDrivers/Src/ADXL.o ./Drivers/myDrivers/Src/ADXL.su ./Drivers/myDrivers/Src/BMP280.d ./Drivers/myDrivers/Src/BMP280.o ./Drivers/myDrivers/Src/BMP280.su

.PHONY: clean-Drivers-2f-myDrivers-2f-Src

