################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../src/nrf5-sdk/toolchain/gcc/gcc_startup_nrf52.S 

OBJS += \
./src/nrf5-sdk/toolchain/gcc/gcc_startup_nrf52.o 

S_UPPER_DEPS += \
./src/nrf5-sdk/toolchain/gcc/gcc_startup_nrf52.d 


# Each subdirectory must supply rules for building sources it contributes
src/nrf5-sdk/toolchain/gcc/%.o: ../src/nrf5-sdk/toolchain/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -munaligned-access -O0 -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -ggdb -x assembler-with-cpp -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


