################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_gpio/mss_gpio.c 

OBJS += \
./drivers/mss_gpio/mss_gpio.o 

C_DEPS += \
./drivers/mss_gpio/mss_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_gpio/%.o: ../drivers/mss_gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_gpio -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_pdma -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_timer -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_uart -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3 -IC:\Users\sarth\Documents\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


