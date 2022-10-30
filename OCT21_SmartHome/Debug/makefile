################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/04-APP/subdir.mk
-include Source/02-ECUA/Servo_Motor/Src/subdir.mk
-include Source/02-ECUA/Relay/Src/subdir.mk
-include Source/02-ECUA/Led/Src/subdir.mk
-include Source/02-ECUA/LM35/Src/subdir.mk
-include Source/02-ECUA/LCD/Src/subdir.mk
-include Source/02-ECUA/KeyPad/Src/subdir.mk
-include Source/02-ECUA/Hc05/Src/subdir.mk
-include Source/02-ECUA/Dc_Motor/Src/subdir.mk
-include Source/02-ECUA/Buzzer/Src/subdir.mk
-include Source/02-ECUA/Button/Src/subdir.mk
-include Source/01-MCAL/UART/Src/subdir.mk
-include Source/01-MCAL/Timer0/Src/subdir.mk
-include Source/01-MCAL/TIMER1/Src/subdir.mk
-include Source/01-MCAL/SPI/Src/subdir.mk
-include Source/01-MCAL/I2C/Src/subdir.mk
-include Source/01-MCAL/GINT/Src/subdir.mk
-include Source/01-MCAL/EXTINT/Src/subdir.mk
-include Source/01-MCAL/EEPROM/Src/subdir.mk
-include Source/01-MCAL/Dio/Src/subdir.mk
-include Source/01-MCAL/ADC/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
OCT21_SmartHome.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: OCT21_SmartHome.elf secondary-outputs

# Tool invocations
OCT21_SmartHome.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,OCT21_SmartHome.map -mmcu=atmega32 -o "OCT21_SmartHome.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

OCT21_SmartHome.lss: OCT21_SmartHome.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S OCT21_SmartHome.elf  >"OCT21_SmartHome.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: OCT21_SmartHome.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 OCT21_SmartHome.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) OCT21_SmartHome.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
