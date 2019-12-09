#include "touchscreen.h"
#include "xbee.h"

uint8_t message[5] = "hello";

int main()
{
	MSS_UART_init(&g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler( &g_mss_uart1, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
	touchscreen_begin();

	drawFillScreen(ILI9341_BLUE);
	drawRectanglePixel(5, 5, 110, 152, ILI9341_WHITE);
	drawRectanglePixel(5, 165, 110, 152, ILI9341_WHITE);
	drawRectanglePixel(120, 5, 115, 312, ILI9341_WHITE);

	drawText1(ILI9341_BLACK);
	drawText2(ILI9341_BLACK);
	drawText3(ILI9341_BLACK);

	while( 1 )
	{
		int x = getX();
		int y = getY();
		sendMessage(&message, 5, 0x000);

		if(x && y){
			if(abs(getX() - x) < 5 && abs(getY() - y) <5){
				drawRectanglePixel(x-2, y-2, 4, 4, ILI9341_YELLOW);

			}

		}
		delay(1);
	}
	return 0;
}
