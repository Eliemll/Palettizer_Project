################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/src/bsp.c \
../bsp/src/delay.c \
../bsp/src/factory_io.c 

OBJS += \
./bsp/src/bsp.o \
./bsp/src/delay.o \
./bsp/src/factory_io.o 

C_DEPS += \
./bsp/src/bsp.d \
./bsp/src/delay.d \
./bsp/src/factory_io.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/src/%.o bsp/src/%.su bsp/src/%.cyclo: ../bsp/src/%.c bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/app/inc" -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/core -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/device/inc -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/portable/GCC/ARM_CM0 -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/config -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/config -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/bsp/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsp-2f-src

clean-bsp-2f-src:
	-$(RM) ./bsp/src/bsp.cyclo ./bsp/src/bsp.d ./bsp/src/bsp.o ./bsp/src/bsp.su ./bsp/src/delay.cyclo ./bsp/src/delay.d ./bsp/src/delay.o ./bsp/src/delay.su ./bsp/src/factory_io.cyclo ./bsp/src/factory_io.d ./bsp/src/factory_io.o ./bsp/src/factory_io.su

.PHONY: clean-bsp-2f-src

