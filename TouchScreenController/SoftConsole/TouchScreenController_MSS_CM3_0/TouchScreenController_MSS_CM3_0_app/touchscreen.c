void begin(){

	uint8_t cmd, x, numArgs;
	const uint8_t *addr = initcmd;

	MSS_SPI_init(&g_mss_spi1);
	MSS_GPIO_init();
	ACE_init();

	ace_y = ACE_get_channel_handle((const uint8_t*)"ADCDirectInput_0");
	ace_x = ACE_get_channel_handle((const uint8_t*)"ADCDirectInput_1");
	
	configureSPI(8);

	sendCommand(SWRESET);
	delay(150);
	while((cmd = read_byte(addr++))){
		x = read_byte(addr++);
		numArgs = x & 0x7F;
		sendCommand(cmd, addr, numArgs);
		addr += numArgs;
		if(x & 0x80){
			delay(150);
		}
	}
}

TSPoint getTouchPoint(){
	int x,y,z;
	int samples[2];
	int valid = 1;

	MSS_GPIO_config(yp, MSS_GPIO_INPUT);
	MSS_GPIO_config(yn, MSS_GPIO_INPUT);
	MSS_GPIO_config(xp, MSS_GPIO_OUTPUT);
	MSS_GPIO_config(xn, MSS_GPIO_OUTPUT);

	MSS_GPIO_set_output(xp, 1);
	MSS_GPIO_set_output(xn, 0);
	//delay 20 microseconds
	samples[0] = ACE_get_ppe_sample(ace_y);
	samples[1] = ACE_get_ppe_sample(ace_y);
	if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
     	valid = 0;
   	} else {
 	   samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    }

	x = (1023-samples[1]);

	MSS_GPIO_config(yp, MSS_GPIO_OUTPUT);
	MSS_GPIO_config(yn, MSS_GPIO_OUTPUT);
	MSS_GPIO_config(xp, MSS_GPIO_INPUT);
	MSS_GPIO_config(xn, MSS_GPIO_INPUT);

	MSS_GPIO_set_output(yp, 1);
	MSS_GPIO_set_output(yn, 0);

	//delay 20 microseconds
	samples[0] = ACE_get_ppe_sample(ace_x);
	samples[1] = ACE_get_ppe_sample(ace_x);

	if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
     	valid = 0;
   	} else {
 	   samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    }

	y = (1023-samples[1]);

	MSS_GPIO_config(yp, MSS_GPIO_INPUT);
	MSS_GPIO_config(yn, MSS_GPIO_OUTPUT);
	MSS_GPIO_config(xp, MSS_GPIO_OUTPUT);
	MSS_GPIO_config(xn, MSS_GPIO_INPUT);

	MSS_GPIO_set_output(xp, 0);
	MSS_GPIO_set_output(yn, 1);

	int z1 = ACE_get_ppe_sample(ace_x);
	int z2 = ACE_get_ppe_sample(ace_y);

	if (_rxplate != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     rtouch *= x;
     rtouch *= _rxplate;
     rtouch /= 1024;
     
     z = rtouch;
   } else {
     z = (1023-(z2-z1));
   }

   if (! valid) {
     z = 0;
   }

   return TSPoint(x, y, z);

}

void drawPixel(uint16_t x, uint16_t y, uint16_t color){
	setAddr(x, y, x, y);
	sendCommand(ILI9341_RAMWR, color);
}


void drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
	setAddr(x, y, x+w-1, y+h-1);
	sendCommand(ILI9341_RAMWR);

	for(y=h; y>0; y--){
		for(x = w; x>0; x--){
			sendData(color);
		}
		sendData(color);
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
	drawRectangle(0, 0, x+ILI9341_WIDTH-1, y-ILI9341_HEIGHT-1, color);
}

void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
	
	sendCommand(ILI9341_CASET);
	sendData(x0);
	sendData(x1);
	sendCommand(ILI9341_PASET);
	sendData(y0);
}

void sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes){

	set_SPI_CS();
	set_DC_LOW();
	sendSPI(&commandByte);

	set_DC_HIGH();
	for(int i=0; i<numDataBytes; i++){
		sendSPI(*dataBytes);
		dataBytes++;
	}
	clear_SPI_CS();
}

void sendCommand(uint8_t commandByte, uint16_t dataBytes){

	set_SPI_CS();
	set_DC_LOW();
	configureSPI(16);

	sendSPI(&commandByte);

	set_DC_HIGH();
	for(int i=0; i<numDataBytes; i++){
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



void configureSPI(uint8_t frameSize){
	MSS_SPI_configure_master_mode(
		&g_mss_spi1, 
		MSS_SPI_SLAVE_0,
		MSS_SPI_MODE0,
		MSS_SPI_PCLK_DIV_16,
		frameSize
	);
}

void sendSPI(uint8_t *data){
	
	MSS_SPI_transfer_frame( &g_mss_spi1, *data);
	
}

void set_SPI_CS(){
	MSS_SPI_set_slave_select(&g_mss_spi1, MSS_SPI_SLAVE_0);
}

void clear_SPI_CS(){
	MSS_SPI_clear_slave_select( &g_mss_spi1, MSS_SPI_SLAVE_0 );
}

