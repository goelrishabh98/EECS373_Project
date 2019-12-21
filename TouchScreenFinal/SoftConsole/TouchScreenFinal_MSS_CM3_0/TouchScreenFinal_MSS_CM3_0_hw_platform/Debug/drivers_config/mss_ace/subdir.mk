################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers_config/mss_ace/ace_config.c 

OBJS += \
./drivers_config/mss_ace/ace_config.o 

C_DEPS += \
./drivers_config/mss_ace/ace_config.d 


# Each subdirectory must supply rules for building sources it contributes
drivers_config/mss_ace/%.o: ../drivers_config/mss_ace/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_ace -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_gpio -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_pdma -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers\mss_spi -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_timer -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_uart -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config\mss_ace -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3 -IC:\Users\rgroc\OneDrive\Documents\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O1 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


