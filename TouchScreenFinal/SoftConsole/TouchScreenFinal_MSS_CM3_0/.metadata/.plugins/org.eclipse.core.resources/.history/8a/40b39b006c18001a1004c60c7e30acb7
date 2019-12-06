#include "touchscreen.h"

int main()
{
	touchscreen_begin();

	drawFillScreen(ILI9341_BLUE);
	drawRectanglePixel(5, 5, ILI9341_TFTWIDTH-10, ILI9341_TFTHEIGHT-10, ILI9341_WHITE);


	while( 1 )
	{
		int x = getX();
		int y = getY();
		int z = getZ();

		if(z > 10){
			drawPixel(x, y, ILI9341_YELLOW);
		}
	}
}
