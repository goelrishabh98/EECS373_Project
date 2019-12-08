#include "touchscreen.h"

int main()
{
	touchscreen_begin();

	drawFillScreen(ILI9341_BLUE);
	drawRectanglePixel(5, 5, 110, 152, ILI9341_WHITE);
	drawRectanglePixel(5, 165, 110, 152, ILI9341_WHITE);
	drawRectanglePixel(120, 5, 115, 312, ILI9341_WHITE);

	drawText1(ILI9341_BLACK);
	//drawText2(ILI9341_BLACK);
	//drawText3(ILI9341_BLACK);

	while( 1 )
	{
		int x = 240 - getX();
		int y = 320 - getY();
		int z = getZ(x);

		if(z >= 0){
			drawRectanglePixel(x-2, y-2, 4, 4, ILI9341_YELLOW);
		}
	}
	return 0;
}
