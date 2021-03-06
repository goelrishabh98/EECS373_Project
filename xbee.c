#include <stdio.h>
#include <inttypes.h>
#include "drivers/mss_uart/mss_uart.h"

//NOTE: Maximum amount of data you can send (i.e maximum value of inputMessageLength) is messageLength - 15
#define messageLength 16
#define RX_BUFF_SIZE 64

uint8_t g_rx_buff[RX_BUFF_SIZE];

//Takes in an array of uint8_t containing address and destination address
//Constructs frame appropriately and sends it out
void sendMessage(uint8_t* inputMessage, uint8_t inputMessageLength, uint16_t destAddr) {
	int i;
	uint8_t message[messageLength];
	message[0] = 0x7E;	//Delimiter, does not change
	message[1] = (messageLength - 4) >> 8;	//Length MSB
	message[2] = (messageLength - 4) & 0xFF;	//Length LSB
	message[3] = 0;	//Frame type: 0 = TX Request 64 bit addr
	message[4] = 1;	//Frame ID
	//5-12: Destination addresses
	for(i = 5; i < 11; ++i) {
		message[i] = 0;
	}
	message[11] = (destAddr >> 8) & 0xFF;
	message[12] = destAddr & 0xFF;
	message[13] = 0;	//Options
	for(i = 0; i < inputMessageLength; ++i) {
		message[i + 14] = *(inputMessage + i * sizeof(uint8_t));
	}
	uint8_t sum = 0;
	for(i = 3; i < messageLength - 1; ++i) {
		sum += message[i];
	}
	message[messageLength - 1] = (0xFF - sum) & 0xFF;
	MSS_UART_polled_tx(&g_mss_uart1, message, sizeof(message));
}

//When something is received, trigger an interrupt that fills g_rx_buff with the received data
void uart1_rx_handler( mss_uart_instance_t * this_uart ) {
      MSS_UART_get_rx( this_uart, &g_rx_buff, sizeof(g_rx_buff) );
}

int main()
{

	//uint8_t message[20] = {0x7E, 0, 0x10, 0, 1, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0xEC};
	uint8_t message[5] = "hello";
	uint8_t servoExtend[1] = "e";	//Message to send to Arduino to extend marker
	uint8_t servoRetract[1] = "r";	//Message to send to Arduino to retract marker
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
	while(1) {
		//sendMessage(&message, messageLength - 15, 0xFFFF);
	}
	return 0;
}