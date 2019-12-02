/* ************************************************************************ */
/*                                                                          */
/* (c) Copyright 2008-2016 Microsemi Corporation.  All rights reserved.     */
/*  Version 1.0.0        Release date March 30, 2010                        */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*  Module:         iap_hw_interface.c                                      */
/*                                                                          */
/*  Description:    user specific file containing IAP interface functions   */
/*                                                                          */
/* ************************************************************************ */
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

#include "a2fxxxm3.h"
#include "iap_hw_interface.h"
#include "dpuser.h"
#include "dpscan.h"
#include "dpalg.h"
#include "dpcom.h"
#include "mss_iap.h"

extern unsigned char opcode;
/*------------------------------------------------------------------------------
* IAP_STATUS_IDLE_MASK:
*   IDLE field of IAP STATUS register.
*------------------------------------------------------------------------------
* IDLE indicates the IAP state machine is IDLE and is ready to process another 
* command. If asserted then an APB write transaction is guaranteed not to 
* generate wait states.
*/

void IAP_DRSCAN_in(unsigned long start_bit_index, unsigned int bits_to_shift,unsigned char* inbuf)
{
    DPUINT bits_shifted;
    DPULONG shift_in_value;
    DPUINT idx;
    
    
    bits_shifted = 0;
    shift_in_value = 0;
    for(idx=0;idx<(bits_to_shift+7)/8;idx++)
    {
        if (inbuf != DPNULL)
        {
            shift_in_value |= ((inbuf[idx] >> start_bit_index) << (8*idx-bits_shifted));
        }
        
        if ( ((idx+1)*8 - bits_shifted) == 32)
        {
            IAP_do_DRSCAN_in(32,shift_in_value);
            shift_in_value=0;
            bits_shifted+=32;
        }
    }
    if (bits_shifted != bits_to_shift)
    {
        IAP_do_DRSCAN_in(bits_to_shift-bits_shifted,shift_in_value);
    }
    
}

void IAP_DRSCAN_out(unsigned int bits_to_shift,unsigned char* inbuf,unsigned char* outbuf)
{
    DPUINT bits_shifted;
    DPULONG shift_in_value;
    DPULONG return_value;
    DPUINT idx;
    DPINT i;
    
    bits_shifted = 0;
    shift_in_value = 0;
    
    for(idx=0;idx<(bits_to_shift+7)/8;idx++)
    {
        if (inbuf != DPNULL)
        {
            shift_in_value |= (inbuf[idx] << (8*idx-bits_shifted));
        }
        
        if ( ((idx+1)*8 - bits_shifted) == 32)
        {
            return_value = IAP_do_DRSCAN_out(32,shift_in_value);
            for(i=idx-3;i<=idx;i++)
            {
                outbuf[i] = return_value >> (i - (idx - 3))*8;
            }
            shift_in_value=0;
            bits_shifted+=32;
        }
    }
    if (bits_shifted != bits_to_shift)
    {
        
        return_value = IAP_do_DRSCAN_out(bits_to_shift-bits_shifted,shift_in_value);
        for(i = idx - (idx % 4); i < idx; i++)
        {
            outbuf[i] = return_value >> (i - (idx - (idx % 4)))*8;
        }
    }
    
}

void IAP_get_and_DRSCAN_in(unsigned char Variable_ID,unsigned int total_bits_to_shift, unsigned long start_bit_index)
{
    DPULONG page_start_bit_index;
    DPUINT bits_to_shift;
    DPUINT bits_shifted;
    DPULONG shift_in_value;
    DPUINT idx;
    DPUINT current_bits_to_shift;
    
    page_start_bit_index = start_bit_index & 0x7;
    shift_in_value = 0;
    
    requested_bytes =  (page_start_bit_index + total_bits_to_shift + 7) >> 3;
    while (requested_bytes)
    {
        page_buffer_ptr = dp_get_data(Variable_ID,start_bit_index);
        
        
        if (return_bytes >= requested_bytes )
        {
            return_bytes = requested_bytes;
            bits_to_shift = total_bits_to_shift;
        }
        else bits_to_shift = (DPUCHAR) (return_bytes * 8 - page_start_bit_index);
        
        bits_shifted = 0;
        current_bits_to_shift = 0;
        
        for(idx=0;idx<(bits_to_shift+7)/8;idx++)
        {
            shift_in_value |= (page_buffer_ptr[idx] << (8*idx-bits_shifted));
            current_bits_to_shift += 8;
            
            if ( current_bits_to_shift  == 32)
            {
                if (idx<4)
                {
                    shift_in_value >>= page_start_bit_index;
                    current_bits_to_shift -= page_start_bit_index;
                }
                if (current_bits_to_shift > (bits_to_shift - bits_shifted))
                {
                    current_bits_to_shift = bits_to_shift - bits_shifted;
                }
                IAP_do_DRSCAN_in(current_bits_to_shift,shift_in_value);
                bits_shifted+=current_bits_to_shift;
                shift_in_value=0;
                current_bits_to_shift = 0;
            }
        }
        if (bits_shifted != bits_to_shift)
        {
            if (idx < 4)
            {
                shift_in_value >>= page_start_bit_index;
            }
            current_bits_to_shift = bits_to_shift - bits_shifted;
            IAP_do_DRSCAN_in(current_bits_to_shift,shift_in_value);
            bits_shifted+=current_bits_to_shift;
            shift_in_value=0;
            current_bits_to_shift = 0;			
        }
        requested_bytes = requested_bytes - return_bytes;
        total_bits_to_shift = total_bits_to_shift - bits_to_shift;
        start_bit_index += bits_to_shift;
        page_start_bit_index = start_bit_index & 0x7;
    }
}

// This is needed for NVM programming.  It is true that the start_bit_index will always start at 0.
void IAP_get_and_DRSCAN_in_out(unsigned char Variable_ID,unsigned int total_bits_to_shift, unsigned long start_bit_index, unsigned char *tdo_data)
{
    // Find out the total number of bytes needed from the image.
    requested_bytes =  (DPULONG) (total_bits_to_shift + 7) >> 3;
    
    // Get the data from the image
    page_buffer_ptr = dp_get_data(Variable_ID,start_bit_index);
    
    // If not all the bytes are available, then we have to adjust the number of buts to shift.
    if (return_bytes >= requested_bytes )
    {
        return_bytes = requested_bytes;
    }
    else
    {
        #ifdef ENABLE_DEBUG          
        dp_display_text("\r\nError: Page buffer size is not big enough...");
        #endif
    }
    
    DRSCAN_out(total_bits_to_shift, page_buffer_ptr, tdo_data); 
    return;
}

