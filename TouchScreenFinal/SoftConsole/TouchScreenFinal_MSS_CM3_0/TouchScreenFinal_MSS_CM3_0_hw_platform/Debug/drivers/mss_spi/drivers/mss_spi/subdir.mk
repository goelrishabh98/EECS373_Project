################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_spi/drivers/mss_spi/mss_spi.c 

OBJS += \
./drivers/mss_spi/drivers/mss_spi/mss_spi.o 

C_DEPS += \
./drivers/mss_spi/drivers/mss_spi/mss_spi.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_spi/drivers/mss_spi/%.o: ../drivers/mss_spi/drivers/mss_spi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_ace -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_gpio -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_pdma -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers\mss_spi -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_timer -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_uart -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config\mss_ace -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3 -IF:\GitHub\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O1 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


