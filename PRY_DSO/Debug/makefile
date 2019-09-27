################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include example/src/tasks/subdir.mk
-include example/src/pantalla_TFT/subdir.mk
-include example/src/main/subdir.mk
-include example/src/c-tds/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: DSO.axf

# Tool invocations
DSO.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_chip_175x_6x\Debug" -Xlinker -Map="DSO.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "c-tds-project-4_Debug.ld" -o "DSO.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) DSO.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "DSO.axf"; # arm-none-eabi-objcopy -v -O binary "DSO.axf" "DSO.bin" ; # checksum -p LPC1769 -d "DSO.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
