/*******************************************************************************
 * (c) Copyright 2009-2016 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion MSS IAP bare metal software driver public API.
 *
 * SVN $Revision: 8629 $
 * SVN $Date: 2016-10-25 17:43:08 +0530 (Tue, 25 Oct 2016) $
 */
#ifndef MSS_IAP_H_
#define MSS_IAP_H_

void enable_IAP(void);
void disable_IAP(void);
void IAP_Wait(void);
void IAP_IRSCAN_in(void);
void IAP_IRSCAN_out(unsigned char* outbuf);
void IAP_do_DRSCAN_in(unsigned int bits_to_shift,unsigned long value);
unsigned long IAP_do_DRSCAN_out(unsigned int bits_to_shift,unsigned long value);
unsigned char IAP_do_IRSCAN_out(void);
void IAP_goto_jtag_state( unsigned char jtag_state, unsigned int cycles );
#endif /*MSS_IAP_H_*/
