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
#define messageLength 16
#define RX_BUFF_SIZE 1400

uint8_t g_rx_buff[RX_BUFF_SIZE];
uint8_t yData;
uint8_t xData;
int receivedCounter = 0;
int parsedCounter = 0;
uint8_t receivedRaw[RECEIVEDBUFFERSIZE];
uint8_t receivedParsed[RECEIVEDBUFFERSIZE];
double receivedScaled[RECEIVEDBUFFERSIZE];
uint8_t servoRetract[1] = "r";
uint8_t servoExtend[1] = "e";

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
	uint8_t g_rx_buff[RX_BUFF_SIZE];
	int rx_size = MSS_UART_get_rx( this_uart, g_rx_buff, RX_BUFF_SIZE );
	memcpy(receivedRaw + receivedCounter * sizeof(uint8_t), g_rx_buff, rx_size);
	receivedCounter += rx_size;
	if(receivedCounter >= RECEIVEDBUFFERSIZE - 12) {
		receivedCounter = 0;
	}
	int i;
	//Raw data all read in
	for(i = 0; i < RECEIVEDBUFFERSIZE; ++i) {
		//uint8_t zeros[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		//If this is an RX packet from a specific XBee addr
		if(receivedRaw[i] == 0x7E && receivedRaw[i+3] == 0x81 && receivedRaw[i+4] == 0x37 && receivedRaw[i+5] == 0x3C) {
			yData = receivedRaw[i+11];
			xData = receivedRaw[i+12];
			receivedParsed[parsedCounter++] = xData;
			receivedParsed[parsedCounter++] = yData;
			//receivedScaled[parsedCounter++] = xData / 10.0 + 29.75;
			//receivedScaled[parsedCounter++] = yData / 10.0 + 15.75;
			receivedRaw[i] = 0;		//Remove delimiter from memory so data will not be read twice
			//memcpy(receivedRaw + i * sizeof(uint8_t), zeros, 12);
		}
	}
}


double deltaX;
double deltaY;

void drawFreeform() {
	int i;
	uint8_t currentX;	//Stores current position of freeform drawing for use in calculation of relative distances
	uint8_t currentY;
	//Only start if a pair of values are available
	if(parsedCounter > 1) {
		//Set current position to first received position
		currentX = receivedParsed[0];
		currentY = receivedParsed[1];
		//Move to starting position
		//sendMessage(&servoRetract, 1, 0x373A);
		makeLine(currentX / 10.0 + 29.75 - 42.5, currentY / 10.0 + 20.5 - 28.5);
		//sendMessage(&servoExtend, 1, 0x373A);
		//Loop through each pair of received values
		for(i = 2; i < parsedCounter; i += 2) {
			//Scale the difference between next position and current position. Move that relative distance
			makeLine((receivedParsed[i] - currentX) / 10.0 + 29.75, (receivedParsed[i+1] - currentY) / 10.0 + 20.5);
			//Update current position to new position
			currentX = receivedParsed[i];
			currentY = receivedParsed[i+1];
		}
	}







	//int currentX = receivedParsed[0] / 10.0 + 29.75;
	//int currentY = receivedParsed[1] / 10.0 + 15.75;
/*
	if(receivedCounter != 0) {
		//Move marker to starting position
			//TODO: Retract
			deltaX = receivedParsed[0] / 10.0 + 29.75 - 42.5;
			deltaY = receivedParsed[1] / 10.0 + 15.75 - 28.5;
			//makeLine(deltaX, deltaY);
			makeLine(receivedScaled[0] - 42.5, receivedScaled[1] - 28.5);
			//TODO: Extend
			for(i = 2; i < parsedCounter; i += 2) {
				//deltaX = receivedParsed[i] / 10.0 + 29.75 - currentX;
				//deltaY = receivedParsed[i+1] / 10.0 + 15.75 - currentY;
				makeLine(receivedScaled[i] - receivedScaled[i-2], receivedScaled[i+1] - receivedScaled[i-2]);
				//currentX = receivedParsed[i] / 10.0 + 29.75;
				//currentY = receivedParsed[i+1] / 10.0 + 15.75;
			}
	}
	*/
}

/*int main()
{

	//uint8_t message[20] = {0x7E, 0, 0x10, 0, 1, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0xEC};
	uint8_t message[5] = "hello";
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
	while(1) {
		//sendMessage(&message, 5, 0xFFFF);
	}
	return 0;
}*/

#endif /* XBEE_H_ */
