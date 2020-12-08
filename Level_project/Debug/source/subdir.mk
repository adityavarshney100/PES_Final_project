################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LEDs.c \
../source/Level_project.c \
../source/delay.c \
../source/i2c.c \
../source/mma8451.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/LEDs.o \
./source/Level_project.o \
./source/delay.o \
./source/i2c.o \
./source/mma8451.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/LEDs.d \
./source/Level_project.d \
./source/delay.d \
./source/i2c.d \
./source/mma8451.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\board" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\source" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\drivers" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\CMSIS" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\utilities" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


