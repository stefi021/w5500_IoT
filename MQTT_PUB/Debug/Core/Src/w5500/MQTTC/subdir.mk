################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/w5500/MQTTC/MQTTClient.c \
../Core/Src/w5500/MQTTC/mqtt_interface.c 

OBJS += \
./Core/Src/w5500/MQTTC/MQTTClient.o \
./Core/Src/w5500/MQTTC/mqtt_interface.o 

C_DEPS += \
./Core/Src/w5500/MQTTC/MQTTClient.d \
./Core/Src/w5500/MQTTC/mqtt_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/w5500/MQTTC/%.o Core/Src/w5500/MQTTC/%.su Core/Src/w5500/MQTTC/%.cyclo: ../Core/Src/w5500/MQTTC/%.c Core/Src/w5500/MQTTC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/Src/w5500 -I../Core/Src/w5500/MQTTC -I../Core/Src/w5500/MQTTC/MQTTPacket -I../Core/Src/w5500/W5500 -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-w5500-2f-MQTTC

clean-Core-2f-Src-2f-w5500-2f-MQTTC:
	-$(RM) ./Core/Src/w5500/MQTTC/MQTTClient.cyclo ./Core/Src/w5500/MQTTC/MQTTClient.d ./Core/Src/w5500/MQTTC/MQTTClient.o ./Core/Src/w5500/MQTTC/MQTTClient.su ./Core/Src/w5500/MQTTC/mqtt_interface.cyclo ./Core/Src/w5500/MQTTC/mqtt_interface.d ./Core/Src/w5500/MQTTC/mqtt_interface.o ./Core/Src/w5500/MQTTC/mqtt_interface.su

.PHONY: clean-Core-2f-Src-2f-w5500-2f-MQTTC

