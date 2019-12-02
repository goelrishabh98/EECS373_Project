/* ************************************************************************ */
/*                                                                          */
/* (c) Copyright 2008-2016 Microsemi Corporation.  All rights reserved.     */
/*  DirectC Version 2.7     Release date August 30, 2010                    */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*  Module:         dpuser.c                                                */
/*                                                                          */
/*  Description:    user specific file containing JTAG interface functions  */
/*                  and delay function                                      */
/*                                                                          */
/****************************************************************************/
/* 
PLEASE READ: BEFORE INSTALLING THIS SOFTWARE, CAREFULLY READ THE FOLLOWING 
MICROSEMI SOC CORP LICENSE AGREEMENT REGARDING THE USE OF THIS SOFTWARE. 
INSTALLING THIS SOFTWARE INDICATES THAT YOU ACCEPT AND UNDERSTAND THIS AGREEMENT 
AND WILL ABIDE BY IT. 

Note: This license agreement (“License”) only includes the following software: 
DirectC. DirectC is licensed under the following terms and conditions.

Hereinafter, Microsemi SoC Corp. shall be referred to as “Licensor” or “Author,” 
whereas the other party to this License shall be referred to as “Licensee.” Each 
party to this License shall be referred to, singularly, as a “Party,” or, 
collectively, as the “Parties.”

Permission to use, copy, modify, and/or distribute DirectC for any purpose, with
or without fee, is hereby granted by Licensor to Licensee, provided that the 
above Copyright notice and this permission notice appear in all copies, 
modifications and/or distributions of DirectC.

DIRECTC IS PROVIDED "AS IS" AND THE AUTHOR/LICENSOR DISCLAIMS ALL WARRANTIES 
WITH REGARD TO DIRECTC INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS. IN NO EVENT SHALL AUTHOR/LICENSOR BE LIABLE TO LICENSEE FOR ANY DAMAGES, 
INCLUDING SPECIAL, DIRECT,INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF 
CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
WITH THE USE OR PERFORMANCE OF DIRECTC.

Export Control: Information furnished to Licensee may include United States 
origin technical data. Accordingly, Licensee is responsible for complying with, 
and warrants to Licensor that it will comply with, all U.S. export control laws 
and regulations, including the provisions of the Export Administration Act of 
1979 and the Export Administration Regulations promulgated thereunder, the Arms 
Export Control Act, and the sanctions laws administered by the Office of Foreign 
Assets Control including any other U.S. Government regulation applicable to the 
export, re-export, or disclosure of such controlled technical data (or the 
products thereof) to Foreign Nationals, whether within or without the U.S., 
including those employed by, or otherwise associated with, Licensee. Licensee 
shall obtain Licensor’s written consent prior to submitting any request for 
authority to export any such technical data.

ADR: Any dispute between the Parties arising from or related to this License or 
the subject matter hereof, including its validity, construction or performance 
thereunder, shall be exclusively resolved through arbitration by a mutually 
acceptable impartial and neutral arbitrator appointed by the Judicial 
Arbitration and Mediation Services (JAMS) in accordance with its rules and 
procedures. If the Parties are not able to agree on an arbitrator within 10 days 
of the date of request for mediation is served, then JAMS shall appoint an 
arbitrator. Notice of arbitration shall be served and filed with the JAMS main 
offices in Irvine, California. Each Party shall be responsible for all costs 
associated with the preparation and representation by attorneys, or any other 
persons retained thereby, to assist in connection with any such Arbitration. 
However, all costs charged by the mutually agreed upon Arbitration entity shall 
be equally shared by the Parties. The Party seeking Mediation and/or Arbitration 
as provided herein agrees that the venue for any such Mediation and Arbitration 
shall be selected by the other Party and that such venue must be Los Angeles, 
California; New York, New York; or Chicago, Illinois; whereby the applicable law 
and provisions of the Evidence Code of the State selected thereby shall be 
applicable and shall govern the validity, construction and performance of this 
License.

Governing Law: This license will be governed by the laws of the State of 
California, without regard to its conflict of law provisions.

Entire Agreement: This document constitutes the entire agreement between the 
Parties with respect to the subject matter herein and supersedes all other 
communications whether written or oral.
*/

#include "main.h"
#include "a2fxxxm3.h"
#include "mss_uart.h"
#include "dpuser.h"
#ifdef ENABLE_IAP_SUPPORT
#include "iap_hw_interface.h"
#endif
#ifdef ENABLE_GPIO_SUPPORT
#include "dpjtag.h"
#endif
#include "dpalg.h"
#include "dpdef.h"
#include "dputil.h"

/* This variable is used to select external programming vs IAP programming */
DPUCHAR hardware_interface;
/* This variable is used to enable private client eNVM programming */
DPUCHAR enable_mss_support = (DPUCHAR)FALSE;
/* This variable is used to reset the device when exiting IAP operation */
DPUCHAR enable_system_reset_on_exit = (DPUCHAR)TRUE;



/*
* User attention: 
* Module: dp_delay
* 		purpose: Execute a time delay for a specified amount of time.
* Arguments: 
* 		microseconeds: 32 bit value containing the amount of wait time in microseconds.
* Return value: None
* 
*/
void dp_delay(DPULONG microseconds)
{
    volatile DPULONG i;
    volatile DPULONG j;
    
    #error "Please modify this function to time delays. Please refer to the Required Source Code Modifications section of the DirectC user's guide."
    
    for(i=0;i<microseconds;i++) {
            for (j=0;j<50;j++) ;
        }
}
#ifdef ENABLE_DEBUG
void dp_display_text(DPCHAR * text)
{
    
    unsigned int length;
    length = 0;
    while (text[length++]!='\0');
    
    MSS_UART_polled_tx (&g_mss_uart0, (unsigned char *)text,length);
    
    while(MSS_UART_tx_complete(&g_mss_uart0) == 0);
}

void dp_display_value( unsigned long value ,int Descriptive)
{
    
    uint8_t value_text[256];
    int text_size;
    if (Descriptive == HEX)
    {
        text_size = int_to_hex_int( value, value_text, 8);
    }
    else 
    {
        text_size = int_to_dec_int( value, value_text, 8);
    }
    
    MSS_UART_polled_tx (&g_mss_uart0, value_text, text_size);
    while(MSS_UART_tx_complete(&g_mss_uart0) == 0);
}

void dp_display_array(unsigned char * outbuf, unsigned int bytes, int Descriptive)
{
    int idx;
    for (idx=0;idx<bytes;idx++)
    {
        dp_display_value(outbuf[bytes-1-idx],Descriptive);
        dp_display_text(" ");
    }
}
#endif


