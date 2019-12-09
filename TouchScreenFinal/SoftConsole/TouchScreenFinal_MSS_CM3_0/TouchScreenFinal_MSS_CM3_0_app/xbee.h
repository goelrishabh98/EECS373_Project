/*
 * xbee.h
 *
 *  Created on: Dec 8, 2019
 *      Author: rgroc
 */

#ifndef XBEE_H_
#define XBEE_H_

#include <stdio.h>
#include <inttypes.h>
#include "drivers/mss_uart/mss_uart.h"

void sendMessage(uint8_t* inputMessage, uint8_t inputMessageLength, uint16_t destAddr);
void uart1_rx_handler( mss_uart_instance_t * this_uart );


#endif /* XBEE_H_ */
