#include "stepper.h"
#include "interface.h"
#include "xbee.h"

uint8_t textInput[RX_BUFF_SIZE];
int textInputCounter = 0;		//Indexes into textInput array so input does not overwrite each other in the 0th index
int textInputDrawnCounter = 0;	//Remembers where in the array we have drawn until
uint8_t newInput = 0;	//0 if no new input, 1 otherwise

void uart0_rx_handler( mss_uart_instance_t * this_uart )
{
	//uint8_t g_rx_buff[100];
	int rx_size = MSS_UART_get_rx( this_uart, textInput + textInputCounter * sizeof(uint8_t), sizeof(textInput) );
	textInputCounter += rx_size;
	if(textInputCounter > RX_BUFF_SIZE) {
		textInputCounter = 0;
	}
	newInput = 1;
}

void drawHardCoded() {
	int i = 0;
	//Draw from last drawn character to the next carriage return
	for(i = textInputDrawnCounter; textInput[i] == '\r'; ++i) {
		//Draw character
		drawCharacter(textInput[i]);
	}
	newInput = 0;
	//Character in ith index is '\r'. Set textInputDrawnCounter to one after \r
	textInputDrawnCounter = i + 1;
	if(textInputDrawnCounter >= RX_BUFF_SIZE) {
		textInputDrawnCounter = 0;
	}
}

//Current Dimensions: 57, 85
//center: 42.5, 28.5
int main(){
	uint8_t servoExtend[1] = "e";
	uint8_t servoRetract[1] = "r";

	MSS_UART_init( &g_mss_uart0, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT );
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler( &g_mss_uart0, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE );
	//MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
	stepper_config(SIXTEENTH, SIXTEENTH);
	interfaceConfig(57, 85);
	int mode = 0;
	//MSS_UART_polled_tx( &g_mss_uart0, servoExtend, sizeof(servoExtend));

	while(1) {
		switch(mode) {
		case -1:	//User has not chosen mode yet
			break;

		case 0:		//Text
			if(newInput) {
				drawHardCoded();
			}
			break;

		case 1:		//Shape
			break;

		case 2:		//Freeform
			if(newInput) {
				drawFreeform();
			}
			break;
		default:
			break;
		}
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
