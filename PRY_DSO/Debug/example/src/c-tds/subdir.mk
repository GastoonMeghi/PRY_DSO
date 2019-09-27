################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/c-tds/monittor_lpc1769.c \
../example/src/c-tds/scheduler_lpc1769.c \
../example/src/c-tds/system_lpc1769.c 

OBJS += \
./example/src/c-tds/monittor_lpc1769.o \
./example/src/c-tds/scheduler_lpc1769.o \
./example/src/c-tds/system_lpc1769.o 

C_DEPS += \
./example/src/c-tds/monittor_lpc1769.d \
./example/src/c-tds/scheduler_lpc1769.d \
./example/src/c-tds/system_lpc1769.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/c-tds/%.o: ../example/src/c-tds/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNO_BOARD_LIB -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc\UTFT" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


