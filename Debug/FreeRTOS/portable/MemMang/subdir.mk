################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_1.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_1.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_1.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o FreeRTOS/portable/MemMang/%.su FreeRTOS/portable/MemMang/%.cyclo: ../FreeRTOS/portable/MemMang/%.c FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/app/inc" -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/core -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/device/inc -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/portable/GCC/ARM_CM0 -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/config -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/config -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/bsp/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-MemMang

clean-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS/portable/MemMang/heap_1.cyclo ./FreeRTOS/portable/MemMang/heap_1.d ./FreeRTOS/portable/MemMang/heap_1.o ./FreeRTOS/portable/MemMang/heap_1.su

.PHONY: clean-FreeRTOS-2f-portable-2f-MemMang

