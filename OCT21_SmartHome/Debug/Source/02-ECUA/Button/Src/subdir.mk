################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/02-ECUA/Button/Src/Button.c 

OBJS += \
./Source/02-ECUA/Button/Src/Button.o 

C_DEPS += \
./Source/02-ECUA/Button/Src/Button.d 


# Each subdirectory must supply rules for building sources it contributes
Source/02-ECUA/Button/Src/%.o: ../Source/02-ECUA/Button/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\ADC\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\00-Lib" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\Dio\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\EEPROM\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\EXTINT\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\GINT\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\I2C\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\SPI\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\Timer0\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\TIMER1\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\01-MCAL\UART\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Button\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Buzzer\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Dc_Motor\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Hc05\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\KeyPad\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\LCD\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Led\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\LM35\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Relay\Inc" -I"C:\Users\I.T Home\Desktop\projects_eclipse (Amit)\OCT21_SmartHome\Source\02-ECUA\Servo_Motor\Inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


