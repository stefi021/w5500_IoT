################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/w5500/HTTPServer/httpParser.c \
../Core/Src/w5500/HTTPServer/httpServer.c \
../Core/Src/w5500/HTTPServer/httpUtil.c 

OBJS += \
./Core/Src/w5500/HTTPServer/httpParser.o \
./Core/Src/w5500/HTTPServer/httpServer.o \
./Core/Src/w5500/HTTPServer/httpUtil.o 

C_DEPS += \
./Core/Src/w5500/HTTPServer/httpParser.d \
./Core/Src/w5500/HTTPServer/httpServer.d \
./Core/Src/w5500/HTTPServer/httpUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/w5500/HTTPServer/%.o Core/Src/w5500/HTTPServer/%.su Core/Src/w5500/HTTPServer/%.cyclo: ../Core/Src/w5500/HTTPServer/%.c Core/Src/w5500/HTTPServer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/Src/w5500/HTTPServer -I../Core/Src/w5500 -I../Core/Src/w5500/W5500 -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-w5500-2f-HTTPServer

clean-Core-2f-Src-2f-w5500-2f-HTTPServer:
	-$(RM) ./Core/Src/w5500/HTTPServer/httpParser.cyclo ./Core/Src/w5500/HTTPServer/httpParser.d ./Core/Src/w5500/HTTPServer/httpParser.o ./Core/Src/w5500/HTTPServer/httpParser.su ./Core/Src/w5500/HTTPServer/httpServer.cyclo ./Core/Src/w5500/HTTPServer/httpServer.d ./Core/Src/w5500/HTTPServer/httpServer.o ./Core/Src/w5500/HTTPServer/httpServer.su ./Core/Src/w5500/HTTPServer/httpUtil.cyclo ./Core/Src/w5500/HTTPServer/httpUtil.d ./Core/Src/w5500/HTTPServer/httpUtil.o ./Core/Src/w5500/HTTPServer/httpUtil.su

.PHONY: clean-Core-2f-Src-2f-w5500-2f-HTTPServer

