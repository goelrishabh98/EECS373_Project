#include "stepper.h"
#include "interface.h"
#include "xbee.h"



#define farEnoughThresh 100.0
#define horizontalScale 5.0
#define verticalScale 10.0

uint8_t textInput[RX_BUFF_SIZE];	//Stores text input only, use other arrays to store freeform drawing data points
int textInputCounter = 0;		//Indexes into textInput array so input does not overwrite each other in the 0th index
int textInputDrawnCounter = 0;	//Remembers where in the array we have drawn until

void uart0_rx_handler( mss_uart_instance_t * this_uart )
{
	//Read buffer into textInput array at [textInputCounter]
	int rx_size = MSS_UART_get_rx( this_uart, textInput + textInputCounter * sizeof(uint8_t), sizeof(textInput) );
	textInputCounter += rx_size;
	//Make sure counter does not index into out of bounds memory. hard fault bois
	if(textInputCounter >= RX_BUFF_SIZE) {
		textInputCounter = 0;
	}
	newInput = 1;	//Sets the new input flag to true
}

void drawHardCoded() {
	MSS_TIM2_start();
	MSS_TIM1_start();
	makeLine(-20.0, 0.0);
	int i = 0;
	//Draw from last drawn character to the next carriage return (when user presses enter, \r is placed into buffer
	for(i = textInputDrawnCounter; textInput[i] != '\r'; ++i) {
		//Draw character
		drawCharacter(textInput[i]);
		//Erase as it goes along and replace with arbitrary character for easier debugging
		textInput[i] = 'D';
	}
	//Once done drawing
	MSS_TIM1_stop();
	MSS_TIM2_stop();
	newInput = 0;	//Once done drawing, reset the flag to false
	//Character in ith index is '\r'. Set textInputDrawnCounter to one after \r
	textInputDrawnCounter = i + 1;
	if(textInputDrawnCounter >= RX_BUFF_SIZE) {
		textInputDrawnCounter = 0;
	}
}

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
		sendMessage(&servoRetract, 1, 0x373A);
		//makeLine(currentX / 10.0 + 29.75 - 42.5, currentY / 10.0 + 20.5 - 28.5);
		makeLine((currentX) / horizontalScale - 25.0, (currentY) / verticalScale - 10.5);
		sendMessage(&servoExtend, 1, 0x373A);
		//Loop through each pair of received values
		for(i = 2; i < parsedCounter; i += 2) {
			//Scale the difference between next position and current position. Move that relative distance
			//makeLine((receivedParsed[i] - currentX) / 10.0 + 29.75, (receivedParsed[i+1] - currentY) / 10.0 + 20.5);
			//If distance between the current point and the next point is more than a threshold, then lift up marker
			uint8_t farEnough = (pow(receivedParsed[i] - currentX, 2) + pow(receivedParsed[i+1] - currentY, 2)) > farEnoughThresh;
			if(farEnough) {
				sendMessage(&servoRetract, 1, 0x373A);
			}
			makeLine((receivedParsed[i] - currentX) / horizontalScale, (receivedParsed[i+1] - currentY) / verticalScale);
			if(farEnough) {
				sendMessage(&servoExtend, 1, 0x373A);
			}
			//Update current position to new position
			currentX = receivedParsed[i];
			currentY = receivedParsed[i+1];
		}
		//Once done drawing
		MSS_TIM1_stop();
		MSS_TIM2_stop();
		newInput = 0;
		//makeLine(0,0);
		sendMessage(&servoRetract, 1, 0x373A);



		makeLine(0, 0);
		MSS_UART_enable_irq( &g_mss_uart1,( MSS_UART_RBF_IRQ ) );
		parsedCounter = 0;
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

//Current Dimensions: 57, 85
//center: 42.5, 28.5
int main(){
	uint8_t servoExtend[1] = "e";
	uint8_t servoRetract[1] = "r";

	//Initializes UART0 and UART1
	MSS_UART_init( &g_mss_uart0, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT );
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	//Set UART0 rx handler to trigger after one byte comes in. NOTE!! MUST USE PROVIDED MACROS. BLOOD SWEAT AND TEARS WENT INTO FINDING THAT OUT
	MSS_UART_set_rx_handler( &g_mss_uart0, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE );
	//Set UART1 rx handler to trigger after 14 bytes come in. NOTE!! MUST USE PROVIDED MACROS. BLOOD SWEAT AND TEARS WENT INTO FINDING THAT OUT
	MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_FOURTEEN_BYTES);
	stepper_config(SIXTEENTH, SIXTEENTH);
	interfaceConfig(57, 85);
	sendMessage(servoRetract, 1, 0x373A);


	while(1) {
		switch(mode) {
		case -1:	//User has not chosen mode yet
			break;

		case 37:		//Text
			if(newInput) {
				drawHardCoded();
			}
			break;

		case 95:		//Shape
			if(newInput) {
				MSS_TIM2_start();
				MSS_TIM1_start();
				drawCharacter(shapeInput);
				newInput = 0;
				MSS_TIM1_stop();
				MSS_TIM2_stop();
			}
			break;

		case 126:		//Freeform
			if(newInput) {
				drawFreeform();
			}
			else {
				makeLine(0,0);
			}
			break;

		default:
			break;
		}
	}

	return 0;
}
