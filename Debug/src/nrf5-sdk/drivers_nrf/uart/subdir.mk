################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/nrf5-sdk/drivers_nrf/uart/nrf_drv_uart.c 

OBJS += \
./src/nrf5-sdk/drivers_nrf/uart/nrf_drv_uart.o 

C_DEPS += \
./src/nrf5-sdk/drivers_nrf/uart/nrf_drv_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/nrf5-sdk/drivers_nrf/uart/%.o: ../src/nrf5-sdk/drivers_nrf/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -munaligned-access -O0 -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -ggdb -DDEBUG -DNRF52_PAN_74 -DSWI_DISABLE0 -DNRF52832_XXAA -DS132 -DSOFTDEVICE_PRESENT=1 -DNRF_SD_BLE_API_VERSION=5 -DBOARD_PCA10040 -DNRF52 -I"../include" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/softdevice/s132/headers" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/softdevice/common" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/ble/common" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/ble/ble_advertising" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/ble/ble_services/ble_lbs" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/ble/nrf_ble_gatt" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/ble/peer_manager" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/delay" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/gpiote" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/common" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/hal" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/uart" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/drivers_nrf/nrf_soc_nosd" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/boards" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/device" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/atomic" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/balloc" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/bsp" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/button" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/cli" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/experimental_log" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/experimental_log/src" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/experimental_section_vars" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/experimental_memobj" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/fds" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/fstorage" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/queue" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/strerror" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/sensorsim" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/util" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/uart" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/libraries/timer" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/toolchain" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/toolchain/cmsis/include" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/external/segger_rtt" -I"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/external/fprintf" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


