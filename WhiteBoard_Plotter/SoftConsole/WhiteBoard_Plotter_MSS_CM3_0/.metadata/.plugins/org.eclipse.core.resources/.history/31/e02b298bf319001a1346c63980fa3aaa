################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CortexM3/GNU/hal_assert.c 

S_UPPER_SRCS += \
../hal/CortexM3/GNU/hal.S \
../hal/CortexM3/GNU/hw_reg_access.S 

OBJS += \
./hal/CortexM3/GNU/hal.o \
./hal/CortexM3/GNU/hal_assert.o \
./hal/CortexM3/GNU/hw_reg_access.o 

C_DEPS += \
./hal/CortexM3/GNU/hal_assert.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_uart -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


