/*
 * xbee.h
 *
 *  Created on: Dec 2, 2019
 *      Author: bansarth
 */

#ifndef XBEE_H_
#define XBEE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "drivers/mss_uart/mss_uart.h"

//NOTE: Maximum amount of data you can send (i.e maximum value of inputMessageLength) is messageLength - 15
#define messageLength 16	//Master only needs to send 1 byte
#define RX_BUFF_SIZE 7500	//Arbitrarily big buffer to minimize risk of hard faulting
#define NUMPOINTS 600

//uint8_t g_rx_buff[RX_BUFF_SIZE];
uint8_t yData;
uint8_t xData;
int receivedCounter = 0;						//Indexes into receivedCounter so we do not overwrite previous data
int parsedCounter = 0;							//Indexes into receivedParsed, keeps track of (number of points * 2) parsed
uint8_t receivedRaw[RX_BUFF_SIZE];		//Stores the full xbee messages from freeform drawings
uint8_t receivedParsed[NUMPOINTS];		//Stores 0-255 x and y coordinates in the order: x0, y0, x1, y1...
int mode = -1;	//-1 when user has not chosen, 0 if text, 1 if shape, 2 if freeform
uint8_t servoRetract[1] = "r";
uint8_t servoExtend[1] = "e";
uint8_t newInput = 0;	//0 if no new input, 1 otherwise. Flag set by interrupts and cleared by drawing functions
uint8_t shapeInput = 0;

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
	//uint8_t g_rx_buff[RX_BUFF_SIZE];
	//int rx_size = MSS_UART_get_rx( this_uart, g_rx_buff, RX_BUFF_SIZE );
	int rx_size = MSS_UART_get_rx( this_uart, receivedRaw + receivedCounter * sizeof(uint8_t), RX_BUFF_SIZE );
	//memcpy(receivedRaw + receivedCounter * sizeof(uint8_t), g_rx_buff, rx_size);
	receivedCounter += rx_size;
	if(receivedCounter >= RECEIVEDBUFFERSIZE - 15) {
		receivedCounter = 0;
	}
	int i;
	//At this point, all raw data read into receivedRaw array
	for(i = 0; i < RECEIVEDBUFFERSIZE; ++i) {
		//If this is an RX packet from touchscreen containing data 0xFFFFFFFF__, then it is to change mode
		if(receivedRaw[i] == 0x7E && receivedRaw[i+3] == 0x81 && receivedRaw[i+4] == 0x37 && receivedRaw[i+5] == 0x3C &&
				receivedRaw[i+8] == 0xFF && receivedRaw[i+9] == 0xFF && receivedRaw[i+10] == 0xFF && receivedRaw[i+11] == 0xFF) {
			mode = receivedRaw[i+12];
			receivedRaw[i] = 0;		//Remove delimiter from memory so data will not be read twice
		}
		else if(receivedRaw[i] == 0x7E && receivedRaw[i+3] == 0x81 && receivedRaw[i+4] == 0x37 && receivedRaw[i+5] == 0x3C &&
				receivedRaw[i+8] == 0x11 && receivedRaw[i+9] == 0x11 && receivedRaw[i+10] == 0x11 && receivedRaw[i+11] == 0x11) {
			shapeInput = receivedRaw[i+12];
			newInput = 1;	//Sets the new input flag to true
		}
		//If this is an RX packet from a specific XBee addr containing freeform drawings
		else if(receivedRaw[i] == 0x7E && receivedRaw[i+3] == 0x81 && receivedRaw[i+4] == 0x37 && receivedRaw[i+5] == 0x3C) {
			/*
			yData = receivedRaw[i+9];
			xData = receivedRaw[i+10];
			receivedParsed[parsedCounter++] = xData;
			receivedParsed[parsedCounter++] = yData;
			*/
			yData = receivedRaw[i+11];
			xData = receivedRaw[i+12];
			receivedParsed[parsedCounter++] = xData;
			receivedParsed[parsedCounter++] = yData;
			receivedRaw[i] = 0;		//Remove delimiter from memory so data will not be read twice
			newInput = 1;
			if(parsedCounter >= NUMPOINTS) {
				//Disable RX handler
				MSS_UART_disable_irq( &g_mss_uart1, ( MSS_UART_RBF_IRQ) );
			}
		}

	}
}

#endif /* XBEE_H_ */
