################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/w5500/DNS/dns.c 

OBJS += \
./Core/Src/w5500/DNS/dns.o 

C_DEPS += \
./Core/Src/w5500/DNS/dns.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/w5500/DNS/%.o Core/Src/w5500/DNS/%.su Core/Src/w5500/DNS/%.cyclo: ../Core/Src/w5500/DNS/%.c Core/Src/w5500/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/Src/w5500/DNS -I../Core/Src/w5500 -I../Core/Src/w5500/W5500 -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-w5500-2f-DNS

clean-Core-2f-Src-2f-w5500-2f-DNS:
	-$(RM) ./Core/Src/w5500/DNS/dns.cyclo ./Core/Src/w5500/DNS/dns.d ./Core/Src/w5500/DNS/dns.o ./Core/Src/w5500/DNS/dns.su

.PHONY: clean-Core-2f-Src-2f-w5500-2f-DNS

