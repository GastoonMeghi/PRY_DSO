################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/tasks/task-Clean_Room_controller_lpc1769.c \
../example/src/tasks/task-Door1_switch_lpc1769.c \
../example/src/tasks/task-Door2_switch_lpc1769.c \
../example/src/tasks/task-Emergency_switch_lpc1769.c \
../example/src/tasks/task-LockDoor1_led_lpc1769.c \
../example/src/tasks/task-LockDoor2_led_lpc1769.c \
../example/src/tasks/task-heartbeat_lpc1769.c \
../example/src/tasks/task-main.c \
../example/src/tasks/task-pantalla.c \
../example/src/tasks/task-procesamiento.c \
../example/src/tasks/task-pruebaPantalla.c \
../example/src/tasks/task-s3_switch_lpc1769.c \
../example/src/tasks/task-watchdog_lpc1769.c 

OBJS += \
./example/src/tasks/task-Clean_Room_controller_lpc1769.o \
./example/src/tasks/task-Door1_switch_lpc1769.o \
./example/src/tasks/task-Door2_switch_lpc1769.o \
./example/src/tasks/task-Emergency_switch_lpc1769.o \
./example/src/tasks/task-LockDoor1_led_lpc1769.o \
./example/src/tasks/task-LockDoor2_led_lpc1769.o \
./example/src/tasks/task-heartbeat_lpc1769.o \
./example/src/tasks/task-main.o \
./example/src/tasks/task-pantalla.o \
./example/src/tasks/task-procesamiento.o \
./example/src/tasks/task-pruebaPantalla.o \
./example/src/tasks/task-s3_switch_lpc1769.o \
./example/src/tasks/task-watchdog_lpc1769.o 

C_DEPS += \
./example/src/tasks/task-Clean_Room_controller_lpc1769.d \
./example/src/tasks/task-Door1_switch_lpc1769.d \
./example/src/tasks/task-Door2_switch_lpc1769.d \
./example/src/tasks/task-Emergency_switch_lpc1769.d \
./example/src/tasks/task-LockDoor1_led_lpc1769.d \
./example/src/tasks/task-LockDoor2_led_lpc1769.d \
./example/src/tasks/task-heartbeat_lpc1769.d \
./example/src/tasks/task-main.d \
./example/src/tasks/task-pantalla.d \
./example/src/tasks/task-procesamiento.d \
./example/src/tasks/task-pruebaPantalla.d \
./example/src/tasks/task-s3_switch_lpc1769.d \
./example/src/tasks/task-watchdog_lpc1769.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/tasks/%.o: ../example/src/tasks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNO_BOARD_LIB -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_chip_175x_6x\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\PRY_DSO\example\inc\UTFT" -I"C:\Users\Gaston\Documents\facultad\TDII\Proyecto\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


