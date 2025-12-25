################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.c \
../TraceRecorder/streamports/Jlink_RTT/trcStreamPort.c 

OBJS += \
./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.o \
./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.o 

C_DEPS += \
./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.d \
./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.d 


# Each subdirectory must supply rules for building sources it contributes
TraceRecorder/streamports/Jlink_RTT/%.o TraceRecorder/streamports/Jlink_RTT/%.su TraceRecorder/streamports/Jlink_RTT/%.cyclo: ../TraceRecorder/streamports/Jlink_RTT/%.c TraceRecorder/streamports/Jlink_RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -c -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/app/inc" -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/core -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/cmsis/device/inc -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/FreeRTOS/portable/GCC/ARM_CM0 -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/config -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/include -I/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/TraceRecorder/streamports/Jlink_RTT/config -I"/home/molle/Bureau/SE4/FreeRTOS/FreeRTOS_Palletizer/bsp/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TraceRecorder-2f-streamports-2f-Jlink_RTT

clean-TraceRecorder-2f-streamports-2f-Jlink_RTT:
	-$(RM) ./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.cyclo ./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.d ./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.o ./TraceRecorder/streamports/Jlink_RTT/SEGGER_RTT.su ./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.cyclo ./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.d ./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.o ./TraceRecorder/streamports/Jlink_RTT/trcStreamPort.su

.PHONY: clean-TraceRecorder-2f-streamports-2f-Jlink_RTT

