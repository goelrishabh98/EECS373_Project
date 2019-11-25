#include "mss_spi.h"

#define TFTWIDTH  240
#define TFTHEIGHT 320

#define read_byte(addr) (*(const unsigned char *)(addr))

void begin(uint32_t freq =0);
void setRotation(uint8_t r);
void invertDisplay(bool i);
void sendSPI(uint8_t data);
void sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes);
void delay(uint32_t time);
