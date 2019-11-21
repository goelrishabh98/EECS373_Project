################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/startup_gcc/newlib_stubs.c 

S_UPPER_SRCS += \
../CMSIS/startup_gcc/startup_a2fxxxm3.S 

OBJS += \
./CMSIS/startup_gcc/newlib_stubs.o \
./CMSIS/startup_gcc/startup_a2fxxxm3.o 

C_DEPS += \
./CMSIS/startup_gcc/newlib_stubs.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/startup_gcc/%.o: ../CMSIS/startup_gcc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_gpio -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_pdma -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_timer -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\drivers\mss_uart -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3 -IC:\Users\sarth\Dropbox\College\FA2019\EECS373\EECS373_Project\WhiteBoard_Plotter\SoftConsole\WhiteBoard_Plotter_MSS_CM3_0\WhiteBoard_Plotter_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/startup_gcc/%.o: ../CMSIS/startup_gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


