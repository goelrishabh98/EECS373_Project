################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CortexM3/cortex_nvic.c 

OBJS += \
./hal/CortexM3/cortex_nvic.o 

C_DEPS += \
./hal/CortexM3/cortex_nvic.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/%.o: ../hal/CortexM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_ace -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_gpio -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_pdma -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers\mss_spi -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_timer -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers\mss_uart -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\drivers_config\mss_ace -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3 -IE:\Github\EECS373_Project\TouchScreenFinal\SoftConsole\TouchScreenFinal_MSS_CM3_0\TouchScreenFinal_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


