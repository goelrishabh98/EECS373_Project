void begin(uint32_t freq){

	uint8_t cmd, x, numArgs;
	const uint8_t *addr = initcmd;

	if(!freq){
		freq = SPI_DEFAULT_FREQ;
	}
	initSPI(freq);

	sendCommand(SWRESET);
	//delay(150)
	while((cmd = read_byte))



}
