/* ************************************************************************ */
/*                                                                          */
/* (c) Copyright 2008-2016 Microsemi Corporation.  All rights reserved.     */
/*  Version 1.0.0        Release date March 30, 2010                        */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*  Module:         urow_iap.c                                              */
/*                                                                          */
/*  Description:    Contains the function prototypes.                       */
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
#include "dpuser.h"
#include "dpcom.h"
#include "dpalg.h"
#include "dpcore.h"
#include "dpsecurity.h"
#include "dpdef.h"
#include "dputil.h"
#include "urow_iap.h"
#define NVM0_BUSY                       0x00000001uL

#define F2DSS_ENVM_BASE_UROW_ADDR       (uint32_t)0x60081E70u
#define F2DSS_ENVM_BASE_UROW_CRC_ADDR   (uint32_t)0x60081E6Eu
#define F2DSS_ENVM_UROW_ADDR_OFFSET     0x81E70u
#define F2DSS_ENVM_UROW_CRC_ADDR_OFFSET 0x81E6Eu

DPUCHAR actual_iap_urow[UROW_BYTE_LENGTH_AND_CRC];
DPUCHAR expected_iap_urow[UROW_BYTE_LENGTH_AND_CRC];
DPUINT expected_iap_urow_crc;
DPUINT actual_iap_urow_crc;
DPUINT tmp_iap_urow_crc;


/* Data structure of data stored in eNVM by IAP programming algorithm. */
typedef struct
{
    __IO uint8_t urow[UROW_BYTE_LENGTH];
} IAP_DATA_ENVM_TypeDef;

IAP_DATA_ENVM_TypeDef * g_iap_data = (IAP_DATA_ENVM_TypeDef *)F2DSS_ENVM_BASE_UROW_ADDR;
IAP_DATA_ENVM_TypeDef * g_iap_crc = (IAP_DATA_ENVM_TypeDef *)F2DSS_ENVM_BASE_UROW_CRC_ADDR;

void init_urow_nvm(void)
{
    NVIC_ClearPendingIRQ( ENVM0_IRQn );
    NVIC_EnableIRQ(ENVM0_IRQn );
    ENVM_REGS->ENABLE = 0x00000008; //Erase Error
    SYSREG->ENVM_CR = 0x92;  //PIPELINE(bit 6),SIXCYCLE(bit7)
    
    return;
}

void check_envm_status(void)
{
    uint32_t status;
    do {
        status = ENVM_REGS->STATUS;
    } while ((status & NVM0_BUSY));
}

void do_program_urow_nvm(void)
{
    /* writing data into envm */
    for (ADDR_OFFSET = 0;ADDR_OFFSET < UROW_BYTE_LENGTH; ADDR_OFFSET++)
    {
        check_envm_status();
        g_iap_data->urow[ADDR_OFFSET] = expected_iap_urow[ADDR_OFFSET];
    }
    
    /* Issue program command */ 
    check_envm_status();
    ADDR_OFFSET = 0;
    ENVM_REGS->CONTROL = (uint32_t) ( (0x10000000  + F2DSS_ENVM_UROW_ADDR_OFFSET ));
    check_envm_status();
    
    
    return;
}

void do_program_urow_crc_nvm(void)
{
    /* writing data into envm */
    for (ADDR_OFFSET = 0u; ADDR_OFFSET < 2u; ADDR_OFFSET++)
    {
        check_envm_status();
        g_iap_crc->urow[ADDR_OFFSET] = tmp_iap_urow_crc >> ADDR_OFFSET*8u;
    }
    
    /* Issue program command */ 
    check_envm_status();
    ADDR_OFFSET = 0;
    ENVM_REGS->CONTROL = (uint32_t) ( (0x10000000  + F2DSS_ENVM_UROW_CRC_ADDR_OFFSET ));
    check_envm_status();
    
    
    return;
}


void do_read_urow_nvm(void)
{
    for (ADDR_OFFSET = 0u; ADDR_OFFSET < UROW_BYTE_LENGTH; ADDR_OFFSET++)
    {
        actual_iap_urow[ADDR_OFFSET] = g_iap_data->urow[ADDR_OFFSET];       
    }
    return;
}

void do_read_urow_crc_nvm(void)
{
    actual_iap_urow_crc = 0u;
    for (ADDR_OFFSET = 0u; ADDR_OFFSET < 2u; ADDR_OFFSET++)
    {
        actual_iap_urow_crc |= (g_iap_crc->urow[ADDR_OFFSET]) << (ADDR_OFFSET*8);
    }
    return;
}


void dp_compute_urow_crc(DPUCHAR value)
{
    DPUINT idx, tmp;
    
    for (idx = 0u; idx < 8u; idx++)
    {
        tmp = (value ^ tmp_iap_urow_crc) & 0x01u;
        tmp_iap_urow_crc >>= 1u;
        if (tmp)
        {
            tmp_iap_urow_crc ^= 0x8408u;
        }
        value >>= 1u;
    }
    return;
}

void read_urow_nvm(void)
{
    DPUCHAR index;
    init_urow_nvm();
    do_read_urow_nvm();
    do_read_urow_crc_nvm();
    
    tmp_iap_urow_crc = 0u;
    for (index = 0u;index < UROW_BYTE_LENGTH; index++)
    {
        dp_compute_urow_crc(actual_iap_urow[index]);
    }
    
    expected_iap_urow_crc = tmp_iap_urow_crc;
    if (actual_iap_urow_crc == expected_iap_urow_crc)
    {
        cycle_count =  ((DPUINT)actual_iap_urow[12] >> 6U) | ((DPUINT)actual_iap_urow[13] << 2U);
        #ifdef ENABLE_DEBUG
        dp_display_text("\n\rIAP Urow: ");
        dp_display_array(actual_iap_urow,UROW_BYTE_LENGTH,HEX);
        #endif
    }
    else 
    {
        cycle_count = 0u;
    }
    
    return;
}


void program_urow_nvm(void)
{
    DPUCHAR index;
    
    read_urow_nvm();
    
    #ifdef ENABLE_DEBUG
    dp_display_text("\r\nProgramming IAP UROW...");
    #endif
    
    for(index = 0u; index < UROW_BYTE_LENGTH_AND_CRC;index++)
    {
        expected_iap_urow[index] = 0u;
    }
    
    if (((device_security_flags & IS_ERASE_ONLY) == 0U) && (global_buf1[0] & CORE_ERASE_BITS_BYTE0) )
    {
        #ifdef CORE_SUPPORT
        if (cycle_count < 1023U)
        {
            cycle_count++;
        }
        else
        {
        }
        #endif
    }

    
    if ((device_security_flags & PERM_LOCK_BIT) && (device_security_flags & ULAWE))
    {
        device_security_flags |= IS_RESTORE_DESIGN;
    }
    if (((device_security_flags & IS_ERASE_ONLY) == 0U) || 
    (device_security_flags & IS_RESTORE_DESIGN))
    {
        /* Constucting the UROW data */
        if ((device_security_flags & IS_RESTORE_DESIGN) == 0U)
        {
            for (index=0U; index < 2U; index++)
            {
                expected_iap_urow[index+14U] = (DPUCHAR) dp_get_bytes(CHECKSUM_ID,index,1U);
            }
            for (index=0U; index < 9U; index++)
            {
                expected_iap_urow[index + 4U] = (DPUCHAR) dp_get_bytes(ACT_UROW_DESIGN_NAME_ID,index,1U);
            }
        }
    }

    if (((device_security_flags & IS_ERASE_ONLY)) && ((device_security_flags & IS_RESTORE_DESIGN) == 0U))
    {
        expected_iap_urow[12] |= ((DPUCHAR) (cycle_count << 6));
        expected_iap_urow[13] = (DPUCHAR) (cycle_count >> 2);
    }
    else 
    {
        /* Constucting the UROW data */
        if ((device_security_flags & IS_RESTORE_DESIGN) == 0U)
        {
			for (index=0U; index < 2U; index++)
            {
                expected_iap_urow[index+14U] = (DPUCHAR) dp_get_bytes(CHECKSUM_ID,index,1U);
            }
            for (index=0U; index < 9U; index++)
            {
                expected_iap_urow[index + 4U] = (DPUCHAR) dp_get_bytes(ACT_UROW_DESIGN_NAME_ID,index,1U);
            }

            
            expected_iap_urow[12] |= ((DPUCHAR) (cycle_count << 6));
            expected_iap_urow[13] = (DPUCHAR) (cycle_count >> 2);
            expected_iap_urow[3] |= GPIO_PROGRAMMING_METHOD << 5;
            expected_iap_urow[3] |= (ALGO_VERSION & 0xfu) << 1u;
            if (ALGO_VERSION & 0x40u)
            {
                expected_iap_urow[0] |= 0x20u;
            }
            else
            {
                expected_iap_urow[0] |= 0x1u;
            }
            expected_iap_urow[2] |= ((ALGO_VERSION >> 4u) & 1u) << 7u;
            expected_iap_urow[3] |= ((ALGO_VERSION >> 5u) & 1u);
            expected_iap_urow[0] |= DC_PROGRAMMING_SW << 6u;
            expected_iap_urow[1] |= (DC_PROGRAMMING_SW >> 2u) & 0x3u;
            expected_iap_urow[1] |= DC_SOFTWARE_VERSION << 2u;
            expected_iap_urow[2] |= (DC_SOFTWARE_VERSION >> 6u) & 0x1u;
        }        
    }
    
    tmp_iap_urow_crc = 0;
    for (index = 0;index < UROW_BYTE_LENGTH; index++)
    {
        dp_compute_urow_crc(expected_iap_urow[index]);
    }
    expected_iap_urow_crc = tmp_iap_urow_crc;
    
    do_program_urow_nvm();
    do_program_urow_crc_nvm();
    
    /* readback and verify UROW */
    do_read_urow_nvm();
    do_read_urow_crc_nvm();
    
    for ( index = 0U; index < UROW_BYTE_LENGTH; index++ )
    {
        if (actual_iap_urow[index] != expected_iap_urow[index])
        {
            error_code = DPE_PROGRAM_UROW_ERROR;
            break;
        }
    }
    if (expected_iap_urow_crc != actual_iap_urow_crc)
    {
        error_code = DPE_PROGRAM_UROW_ERROR;
    }
    
    return;
}


#ifdef ENABLE_DEBUG
void dp_display_urow_nvm(void)
{
    DPUCHAR algo_version;
    DPUCHAR programmer;
    DPUCHAR programming_method;
    DPUCHAR software_version;
    
    algo_version = (actual_iap_urow[3] >> 1) & 0xfu;
    if ((actual_iap_urow[0] & 0x1u) != (actual_iap_urow[0] & 0x20u) >> 5u)
    {
        algo_version |= ((actual_iap_urow[2] >> 7u ) & 0x1) << 4u;
        algo_version |= (actual_iap_urow[3] & 0x1u) << 5u;
        algo_version |= ((actual_iap_urow[0] >> 5u) & 0x1u) << 6u;
    }
    programming_method = (actual_iap_urow[3] >> 5u) & 0x7u;
    programmer = ((actual_iap_urow[0] >> 6u) & 0x3u) | ((actual_iap_urow[1] & 0x3u) << 0x2u);
    software_version = (actual_iap_urow[1] >> 2u) | (actual_iap_urow[2] & 0x1 << 6u);
    
    dp_display_text("\r\nUser information: ");
    dp_display_text("\r\nCYCLE COUNT: ");
    dp_display_value(cycle_count,DEC);
    dp_display_text("\r\nCHECKSUM = ");
    dp_display_array(&actual_iap_urow[14],2u, HEX);
    dp_display_text("\r\nDesign Name = ");
    dp_display_array(&actual_iap_urow[4],9u, HEX);
    
    dp_display_text("\r\nProgramming Method: ");
    switch(programming_method)
    {
        case IEEE1532_PM:
        dp_display_text("IEEE1532");
        break;
        case STAPL_PM:
        dp_display_text("STAPL");
        break;
        case DIRECTC_PM:
        dp_display_text("DIRECTC");
        break;
        case PDB_PM:
        dp_display_text("PDB");
        break;
        case SVF_PM:
        dp_display_text("SVF");
        break;
        case IAP_PM:
        dp_display_text("IAP");
        break;
        default:
        dp_display_text("Unknown");
        break;
    };
    dp_display_text("\r\nAlgorithm Version: = ");
    dp_display_value(algo_version, DEC);
    dp_display_text("\r\nProgrammer: = ");
    dp_display_value(algo_version, DEC);
    
    dp_display_text("\r\nProgrammer: ");
    switch(programmer)
    {
        case FP:
        dp_display_text("Flash Pro");
        break;
        case FPLITE:
        dp_display_text("Flash Pro Lite");
        break;
        case FP3:
        dp_display_text("FP3");
        break;
        case SCULPTW:
        dp_display_text("Sculptor");
        break;
        case BPW:
        dp_display_text("BP Programmer");
        break;
        case DIRECTCP:
        dp_display_text("DirectC");
        break;
        case STP:
        dp_display_text("STAPL");
        break;
        case FP4:
        dp_display_text("FP4");
        break;
        default:
        dp_display_text("Unknown");
        break;
    };
    
    dp_display_text("\r\nSoftware Version = ");
    dp_display_value(software_version, DEC);
    
    dp_display_text("\r\n==================================================");
    return;
}
#endif
