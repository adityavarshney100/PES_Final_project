################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

OBJS += \
./startup/startup_mkl25z4.o 

C_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\board" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\source" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\drivers" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\CMSIS" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\utilities" -I"C:\Users\aditya.vny95\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Level_project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


