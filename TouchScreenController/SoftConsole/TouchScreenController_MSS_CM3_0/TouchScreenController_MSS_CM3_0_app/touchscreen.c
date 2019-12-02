#include "touchscreen.h"

const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};

void touchscreen_begin(){

	uint8_t cmd, x, numArgs;
	const uint8_t *addr = initcmd;

	MSS_SPI_init(&g_mss_spi1);
	MSS_GPIO_init();
	MSS_GPIO_config(DC, MSS_GPIO_OUTPUT_MODE);
	ACE_init();

	//ace_y = ACE_get_channel_handle((const uint8_t*)"ADCDirectInput_0");
	//ace_x = ACE_get_channel_handle((const uint8_t*)"ADCDirectInput_1");
	
	configureSPI(8);

	sendCommandOnly(ILI9341_SWRESET);
	delay(150);
	while((cmd = read_byte(addr++))>0){
		x = read_byte(addr++);
		numArgs = x & 0x7F;
		sendCommand(cmd, &addr, numArgs);
		addr += numArgs;
		if(x & 0x80){
			delay(150);
		}
	}
}

//TSPoint getTouchPoint(){
//	int x,y,z;
//	int samples[2];
//	int valid = 1;
//
//	MSS_GPIO_config(yp, MSS_GPIO_INPUT_MODE);
//	MSS_GPIO_config(yn, MSS_GPIO_INPUT_MODE);
//	MSS_GPIO_config(xp, MSS_GPIO_OUTPUT_MODE);
//	MSS_GPIO_config(xn, MSS_GPIO_OUTPUT_MODE);
//
//	MSS_GPIO_set_output(xp, 1);
//	MSS_GPIO_set_output(xn, 0);
//	//delay 20 microseconds
//	samples[0] = ACE_get_ppe_sample(ace_y);
//	samples[1] = ACE_get_ppe_sample(ace_y);
//	if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
//     	valid = 0;
//   	} else {
// 	   samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
//    }
//
//	x = (1023-samples[1]);
//
//	MSS_GPIO_config(yp, MSS_GPIO_OUTPUT);
//	MSS_GPIO_config(yn, MSS_GPIO_OUTPUT);
//	MSS_GPIO_config(xp, MSS_GPIO_INPUT);
//	MSS_GPIO_config(xn, MSS_GPIO_INPUT);
//
//	MSS_GPIO_set_output(yp, 1);
//	MSS_GPIO_set_output(yn, 0);
//
//	//delay 20 microseconds
//	samples[0] = ACE_get_ppe_sample(ace_x);
//	samples[1] = ACE_get_ppe_sample(ace_x);
//
//	if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
//     	valid = 0;
//   	} else {
// 	   samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
//    }
//
//	y = (1023-samples[1]);
//
//	MSS_GPIO_config(yp, MSS_GPIO_INPUT);
//	MSS_GPIO_config(yn, MSS_GPIO_OUTPUT);
//	MSS_GPIO_config(xp, MSS_GPIO_OUTPUT);
//	MSS_GPIO_config(xn, MSS_GPIO_INPUT);
//
//	MSS_GPIO_set_output(xp, 0);
//	MSS_GPIO_set_output(yn, 1);
//
//	int z1 = ACE_get_ppe_sample(ace_x);
//	int z2 = ACE_get_ppe_sample(ace_y);
//
//	if (_rxplate != 0) {
//     // now read the x
//     float rtouch;
//     rtouch = z2;
//     rtouch /= z1;
//     rtouch -= 1;
//     rtouch *= x;
//     rtouch *= _rxplate;
//     rtouch /= 1024;
//
//     z = rtouch;
//   } else {
//     z = (1023-(z2-z1));
//   }
//
//   if (! valid) {
//     z = 0;
//   }
//
//   return TSPoint(x, y, z);
//
//}

void drawPixel(uint16_t x, uint16_t y, uint16_t color){
	setAddr(x, y, x, y);
	sendCommand16(ILI9341_RAMWR, color);
}


void drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
	setAddr(x, y, x+w-1, y+h-1);
	sendCommandOnly(ILI9341_RAMWR);

	for(y=h; y>0; y--){
		for(x = w; x>0; x--){
			sendData(&color, 16);
		}
		sendData(&color, 16);
	}
}
void drawRectanglePixel(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
	uint16_t i, j;

	for(i = x; i<x+w; i++){
		for(j = y; j<y+h; j++){
			drawPixel(i, j, color);
		}
	}
}		

void drawFillScreen(uint16_t color){
	drawRectangle(0, 0, ILI9341_TFTWIDTH-1, ILI9341_TFTHEIGHT-1, color);
}

void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
	
	sendCommandOnly(ILI9341_CASET);
	sendData(&x0, 8);
	sendData(&x1, 8);
	sendCommandOnly(ILI9341_PASET);
	sendData(&y0, 8);
	sendData(&y1, 8);
}

void sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes){

//	set_SPI_CS();
//	set_DC_LOW();
//	configureSPI(8);
//	sendSPI(commandByte);
//
//	configureSPI(numDataBytes);
//	set_DC_HIGH();
//
//	sendSPI(dataBytes);
//
//	clear_SPI_CS();
	int i;
	configureSPI(8);
	set_SPI_CS();
	set_DC_LOW();
	sendSPI(commandByte);

		set_DC_HIGH();
		for(i=0; i<numDataBytes; i++){
			sendSPI(*dataBytes);
			dataBytes++;
		}
		clear_SPI_CS();
}

void sendCommand16(uint8_t commandByte, uint16_t *dataBytes){

	set_SPI_CS();
	set_DC_LOW();
	configureSPI(8);

	sendSPI(commandByte);

	configureSPI(16);
	set_DC_HIGH();

	sendSPI(*dataBytes);

	clear_SPI_CS();
}

void sendData(uint8_t *dataBytes, uint8_t numDataBytes){
	int i;
	set_SPI_CS();
	set_DC_HIGH();
	configureSPI(8);

	for(i=0; i<numDataBytes; i++){
		sendSPI(*dataBytes);
		dataBytes++;
	}
	clear_SPI_CS();
}

void delay(uint32_t time){

	uint32_t start = MSS_TIM1_get_current_value();
	uint32_t val = start - (int)(time/0.01);

	MSS_TIM1_start();
	while(MSS_TIM1_get_current_value()>val){
		//do nothing
	}
	MSS_TIM1_stop();
}

void sendCommandOnly(uint8_t commandByte){
	set_SPI_CS();
	set_DC_LOW();
	sendSPI(commandByte);
	clear_SPI_CS();
}


void configureSPI(uint8_t frameSize){
	MSS_SPI_configure_master_mode(
		&g_mss_spi1, 
		MSS_SPI_SLAVE_0,
		MSS_SPI_MODE0,
		MSS_SPI_PCLK_DIV_64,
		frameSize
	);
}

void sendSPI(uint32_t data){
	
	MSS_SPI_transfer_frame( &g_mss_spi1, data);
	
}

void set_SPI_CS(){
	MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);
}

void clear_SPI_CS(){
	MSS_SPI_clear_slave_select( &g_mss_spi1, MSS_SPI_SLAVE_0 );
}

void set_DC_HIGH(){
	MSS_GPIO_set_output(DC, 1);
}

void set_DC_LOW(){
	MSS_GPIO_set_output(DC, 0);
}
