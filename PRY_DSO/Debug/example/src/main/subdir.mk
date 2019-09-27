################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/main/cr_startup_lpc175x_6x.c \
../example/src/main/main.c \
../example/src/main/sysinit.c 

OBJS += \
./example/src/main/cr_startup_lpc175x_6x.o \
./example/src/main/main.o \
./example/src/main/sysinit.o 

C_DEPS += \
./example/src/main/cr_startup_lpc175x_6x.d \
./example/src/main/main.d \
./example/src/main/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/main/%.o: ../example/src/main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNO_BOARD_LIB -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc\UTFT" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


