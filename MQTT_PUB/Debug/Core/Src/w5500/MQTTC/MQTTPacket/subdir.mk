################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.c \
../Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.c 

OBJS += \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.o \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.o 

C_DEPS += \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.d \
./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/w5500/MQTTC/MQTTPacket/%.o Core/Src/w5500/MQTTC/MQTTPacket/%.su Core/Src/w5500/MQTTC/MQTTPacket/%.cyclo: ../Core/Src/w5500/MQTTC/MQTTPacket/%.c Core/Src/w5500/MQTTC/MQTTPacket/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/Src/w5500 -I../Core/Src/w5500/MQTTC -I../Core/Src/w5500/MQTTC/MQTTPacket -I../Core/Src/w5500/W5500 -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-w5500-2f-MQTTC-2f-MQTTPacket

clean-Core-2f-Src-2f-w5500-2f-MQTTC-2f-MQTTPacket:
	-$(RM) ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectClient.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTConnectServer.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTDeserializePublish.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTFormat.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTPacket.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSerializePublish.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeClient.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTSubscribeServer.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeClient.su ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.cyclo ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.d ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.o ./Core/Src/w5500/MQTTC/MQTTPacket/MQTTUnsubscribeServer.su

.PHONY: clean-Core-2f-Src-2f-w5500-2f-MQTTC-2f-MQTTPacket

