#include "mss_spi.h"

#define TFTWIDTH  240
#define TFTHEIGHT 320

#define read_byte(addr) (*(const unsigned char *)(addr))

void begin(uint32_t freq =0);
void setRotation(uint8_t r);
void invertDisplay(bool i);
void scrollTo()
