################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/segger-rtt/subdir.mk
-include src/nrf5-sdk/toolchain/gcc/subdir.mk
-include src/nrf5-sdk/toolchain/subdir.mk
-include src/nrf5-sdk/softdevice/common/subdir.mk
-include src/nrf5-sdk/libraries/util/subdir.mk
-include src/nrf5-sdk/libraries/uart/subdir.mk
-include src/nrf5-sdk/libraries/timer/subdir.mk
-include src/nrf5-sdk/libraries/strerror/subdir.mk
-include src/nrf5-sdk/libraries/fstorage/subdir.mk
-include src/nrf5-sdk/libraries/experimental_section_vars/subdir.mk
-include src/nrf5-sdk/libraries/experimental_memobj/subdir.mk
-include src/nrf5-sdk/libraries/experimental_log/subdir.mk
-include src/nrf5-sdk/libraries/button/subdir.mk
-include src/nrf5-sdk/libraries/bsp/subdir.mk
-include src/nrf5-sdk/libraries/balloc/subdir.mk
-include src/nrf5-sdk/drivers_nrf/uart/subdir.mk
-include src/nrf5-sdk/drivers_nrf/gpiote/subdir.mk
-include src/nrf5-sdk/drivers_nrf/common/subdir.mk
-include src/nrf5-sdk/boards/subdir.mk
-include src/nrf5-sdk/ble/nrf_ble_gatt/subdir.mk
-include src/nrf5-sdk/ble/common/subdir.mk
-include src/nrf5-sdk/ble/ble_advertising/subdir.mk
-include src/fprintf/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ble_tp.hex \

SECONDARY_SIZE += \
ble_tp.siz \


# All Target
all: ble_tp.elf secondary-outputs

# Tool invocations
ble_tp.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -munaligned-access -O0 -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -ggdb -T nrf52_link.ld -L"../ldscripts" -L"C:\Users\Administrateur\Desktop\nRF5_SDK_14.1.0_1dda907/components/toolchain/gcc" -Wl,-Map,"ble_tp.map" --specs=nano.specs -o "ble_tp.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ble_tp.hex: ble_tp.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ble_tp.elf"  "ble_tp.hex"
	@echo 'Finished building: $@'
	@echo ' '

ble_tp.siz: ble_tp.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "ble_tp.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) ble_tp.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
