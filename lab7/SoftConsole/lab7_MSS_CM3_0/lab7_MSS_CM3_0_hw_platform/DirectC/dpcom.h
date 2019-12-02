/* ************************************************************************ */
/*                                                                          */
/* (c) Copyright 2008-2016 Microsemi Corporation.  All rights reserved.     */
/*  DirectC Version 2.7     Release date August 30, 2010                    */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*  Module:         dpcom.h                                                 */
/*                                                                          */
/*  Description:    Contains functions prototypes needed to access the data */
/*  from external flash or other means of communication                     */
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

#ifndef INC_DPCOM_H
#define INC_DPCOM_H

extern DPULONG return_bytes;
extern DPULONG requested_bytes;
extern DPULONG image_size;
extern DPUCHAR * page_buffer_ptr;
extern uint32_t ADDR_OFFSET;
/* user attention is required.  PAGE_BUFFER_SIZE needs to be specified in bytes */
#define PAGE_BUFFER_SIZE 8192u
#define F2DSS_EMC_BASE_ADDR 0x70000000
#define MIN_VALID_BYTES_IN_PAGE 16u

#ifdef USE_PAGING
extern DPUCHAR page_global_buffer[PAGE_BUFFER_SIZE];  /* Page_global_buffer simulating the global_buf1fer that is accessible by DirectC code*/
#endif

/* 
* Data block ID definitions
*/
#define Header_ID                 0u
#define ACT_UROW_DESIGN_NAME_ID   1u
#define BsrPattern_ID             2u  
#define SILSIG_ID                 3u		
#define CHECKSUM_ID               4u
#define datastream_ID             5u
#define rlock_ID                  6u
#define FRomAddressMask_ID        7u
#define FRomStream_ID             8u

/* These defintions are the same as NVM block zoro.  They are defined to aviod confusion when pogram and verify NVM functions are called. */
#define NVM_OFFSET                5u
#define NvmParSize_ID             9u 
#define NumOfPart_ID             10u
#define NvmAddr_ID               11u
#define NvmData_ID               12u
#define NvmProtect_ID            13u


#define NvmParSize_0_ID           9u 
#define NumOfPart_0_ID           10u
#define NvmAddr_0_ID             11u
#define NvmData_0_ID             12u
#define NvmProtect_0_ID          13u
#define NvmParSize_1_ID          14u
#define NumOfPart_1_ID           15u
#define NvmAddr_1_ID             16u
#define NvmData_1_ID             17u
#define NvmProtect_1_ID          18u
#define NvmParSize_2_ID          19u
#define NumOfPart_2_ID           20u
#define NvmAddr_2_ID             21u
#define NvmData_2_ID             22u
#define NvmProtect_2_ID          23u
#define NvmParSize_3_ID          24u
#define NumOfPart_3_ID           25u
#define NvmAddr_3_ID             26u
#define NvmData_3_ID             27u
#define NvmProtect_3_ID          28u
#define UKEY_ID                  29u
#define DMK_ID                   30u
#define KDATA_ID                 31u
#define ULOCK_ID                 32u
#define NvmParSizePriv_all_ID    33u
#define NumOfPartPriv_all_ID     34u
#define NvmAddrPriv_all_ID       35u
#define NvmDataPriv_all_ID       36u
#define NvmProtectPriv_all_ID    37u

/*
* Location of special variables needed in the header section of the image file
*/
#define BTYES_PER_TABLE_RECORD    9u
#define ACTEL_HEADER_SIZE        24u
#define HEADER_SIZE_OFFSET       24u
#define IMAGE_SIZE_OFFSET        25u
#define MIN_IMAGE_SIZE           56u
#define M_DEVICE_OFFSET          30u
#define ID_OFFSET                31u

#define DEVICE_FAMILY_OFFSET     55u
#define DEVICE_NAME_OFFSET       56u
#define ID_MASK_OFFSET           57u
#define SD_TILES_OFFSET          61u
#define MAP_ROWS_OFFSET          62u
#define BSR_LENGTH_OFFSET        64u
#define SE_WAIT_OFFSET           66u
#define DUAL_KEY_SUPPORT_OFFSET  67u

#define JTAG_EXIT2_DR             0u
#define JTAG_EXIT1_DR             1u
#define JTAG_SHIFT_DR             2u 
#define JTAG_PAUSE_DR             3u
#define JTAG_SELECT_IR            4u
#define JTAG_UPDATE_DR            5u
#define JTAG_CAPTURE_DR           6u
#define JTAG_SELECT_DR            7u 
#define JTAG_EXIT2_IR             8u
#define JTAG_EXIT1_IR             9u
#define JTAG_SHIFT_IR            10u
#define JTAG_PAUSE_IR            11u
#define JTAG_RUN_TEST_IDLE       12u
#define JTAG_UPDATE_IR           13u
#define JTAG_CAPTURE_IR          14u
#define JTAG_TEST_LOGIC_RESET    15u

DPUCHAR * dp_get_data(DPUCHAR var_ID,DPULONG bit_index);
DPUCHAR * dp_get_header_data(DPULONG bit_index);
void dp_get_page_data(DPULONG image_requested_address);
void dp_get_data_block_address(DPUCHAR requested_var_ID);
DPUCHAR * dp_get_data_block_element_address(DPULONG bit_index);
DPULONG dp_get_bytes(DPUCHAR var_ID,DPULONG byte_index,DPUCHAR requested_bytes);
DPULONG dp_get_header_bytes(DPULONG byte_index,DPUCHAR requested_bytes);
void dp_get_and_DRSCAN_in(unsigned char Variable_ID,unsigned int total_bits_to_shift, unsigned long start_bit_index);
void dp_get_and_DRSCAN_in_out(unsigned char Variable_ID,unsigned int total_bits_to_shift, unsigned long start_bit_index, unsigned char *tdo_data);
#endif /* INC_DPCOM_H */


