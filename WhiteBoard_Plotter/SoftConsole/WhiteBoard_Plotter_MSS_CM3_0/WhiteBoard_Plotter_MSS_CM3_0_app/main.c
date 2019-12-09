#include "stepper.h"
#include "interface.h"
#include "xbee.h"

//Current Dimensions: 57, 85
//center: 42.5, 28.5
int main(){
	stepper_config(SIXTEENTH, SIXTEENTH);
	interfaceConfig(57, 85);

	uint8_t servoExtend[1] = "e";
	uint8_t servoRetract[1] = "r";
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);


	int a = 1;
	while(1) {
		sendMessage(&servoRetract, 1, 0x373A);
		a = 1;
		sendMessage(&servoExtend, 1, 0x373A);
		a = 1;
	}
	/*
	makeLine(2.0, -0.7);
	sendMessage(servoExtend, 1, 0x373A);
	makeLine(0.0, -3.0);
	makeLine(-1.5, 1.5);
	makeLine(2.0, 0.0);
	//Get ready for next character
	sendMessage(servoRetract, 1, 0x373A);
	makeLine(0.5, 2.2);
	 */
	//makeLine(3, 0);
	//makeLine(0, -3);
	//makeLine(-3, 0);
	//makeLine(0, -3);
	//makeLine(3, 0);

	return 0;
}
