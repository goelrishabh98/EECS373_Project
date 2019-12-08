################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../touchscreen.c 

OBJS += \
./main.o \
./touchscreen.o 

C_DEPS += \
./main.d \
./touchscreen.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_ace -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_gpio -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_pdma -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers\mss_spi -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_timer -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_uart -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config\mss_ace -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3 -ID:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


