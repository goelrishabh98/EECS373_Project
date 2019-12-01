################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_rtc/drivers/mss_rtc/mss_rtc.c 

OBJS += \
./drivers/mss_rtc/drivers/mss_rtc/mss_rtc.o 

C_DEPS += \
./drivers/mss_rtc/drivers/mss_rtc/mss_rtc.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_rtc/drivers/mss_rtc/%.o: ../drivers/mss_rtc/drivers/mss_rtc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_gpio -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_pdma -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_timer -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_uart -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3 -IC:\Users\bansarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


