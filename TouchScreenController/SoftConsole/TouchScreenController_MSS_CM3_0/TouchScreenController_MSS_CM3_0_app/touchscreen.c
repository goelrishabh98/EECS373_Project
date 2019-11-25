void begin(){

	uint8_t cmd, x, numArgs;
	const uint8_t *addr = initcmd;
	const uint8_t frame_size = 8;

	MSS_SPI_init(&g_mss_spi1);
	MSS_SPI_configure_master_mode(
		&g_mss_spi1, 
		MSS_SPI_SLAVE_0,
		MSS_SPI_MODE0,
		MSS_SPI_PCLK_DIV_16,
		frame_size
	);

	sendCommand(SWRESET);
	//delay(150)
	while((cmd = read_byte(addr++))){
		x = read_byte(addr++);
		numArgs = x & 0x7F;
		sendCommand(cmd, addr, numArgs);
		addr += numArgs;
		if(x & 0x80){
			//delay(150);
		}
	}
}

void drawPixel(uint16_t x, uint16_t y, uint16_t color){
	setAddr(x, y, x, y);
	
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

void delay(uint32_t time){

	uint32_t start = MSS_TIM1_get_current_value();
	uint32_t val = start - (int)(time/0.01);

	MSS_TIM1_start();
	while(MSS_TIM1_get_current_value()>val){
		//do nothing
	}
	MSS_TIM1_stop();
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
