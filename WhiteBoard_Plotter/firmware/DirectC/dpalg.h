/* ************************************************************************ */
/*                                                                          */
/* (c) Copyright 2008-2016 Microsemi Corporation.  All rights reserved.     */
/*  DirectC Version 2.7     Release date August 30, 2010                    */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*  Module:         dpalg.h                                                 */
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

#ifndef INC_DPALG_H
#define INC_DPALG_H
/* global_buf_SIZE should not exceed 256 bytes */
#define BOL 0u
#define EOL 3u

#define global_buf_SIZE 16u
#define AXX015_DEVICE   1u
#define AXX030_DEVICE   2u


#define IDCODE_LENGTH   32u
#define LDVPROP_LENGTH  6u

/************************************************************/
/* Instrunction Set                                         */
/************************************************************/
/* General opcodes */
#define ISC_SAMPLE               0x01u
#define ISC_ENABLE               0x80u
#define ISC_DISABLE              0x81u
#define ISC_NOOP                 0x84u
#define DESELECT_ALL_TILES       0xC0u
/* Erase opcodes */              
#define ISC_ERASE                0x85u

/* UROW opcodes */               
#define ISC_PROGRAM_UROW         0xA7u
#define ISC_READ_UROW            0xA8u
#define ISC_PROGRAM_RLOCK        0x8Cu

#define HIGHZ                    0x07u
#define BYPASS                   0xFFu
#define IDCODE                   0x0Fu
#define USERCODE                 0x0Eu
#define LDVPROP                  0xB4u
/* Factory row opcodes */
#define FACTORY_ADDRESS_SHIFT    0xF9u
#define READ_FACTORY             0xBFu

/* UROW Data */
#define GPIO_PROGRAMMING_METHOD  0x2u
#define IAP_PROGRAMMING_METHOD   0x5u
/* This is equivalent to FP90 */
#define DIRECTC_VERSION          0x26u
#define DC_PROGRAMMING_SW        0x5u
#define ALGO_VERSION             0x14u

#define DC_SOFTWARE_VERSION      26u
#define IEEE1532_PM              0u
#define STAPL_PM                 1u
#define DIRECTC_PM               2u
#define PDB_PM                   3u
#define SVF_PM                   4u
#define IAP_PM                   5u



/* Programmer */
#define FP                       0u
#define FPLITE                   1u
#define FP3                      2u
#define SCULPTW                  3u
#define BPW                      4u
#define DIRECTCP                 5u
#define STP                      6u
#define FP4                      7u


/************************************************************/
/* Register Length                                          */
/************************************************************/
#define MAX_ERASE_POLL           262140u
#define MAX_PROGRAM_POLL         16380u
#define OPCODE_BIT_LENGTH        8u
#define FACTORY_ROW_BIT_LENGTH   128u

/* Action Names -- match actions function */
/* These codes are passed to the main entry function "dp_top" to indicate 
* which action to perform */
#define DP_NO_ACTION_FOUND                      0u
#define DP_DEVICE_INFO_ACTION_CODE              1u
#define DP_READ_IDCODE_ACTION_CODE              2u
#define DP_ERASE_ACTION_CODE                    3u
#define DP_PROGRAM_ACTION_CODE                  5u
#define DP_VERIFY_ACTION_CODE                   6u
/* Array only actions */
#define DP_ENC_DATA_AUTHENTICATION_ACTION_CODE  7u
#define DP_ERASE_ARRAY_ACTION_CODE              8u
#define DP_PROGRAM_ARRAY_ACTION_CODE            9u
#define DP_VERIFY_ARRAY_ACTION_CODE             10u
/* FROM only actions */
#define DP_ERASE_FROM_ACTION_CODE               11u
#define DP_PROGRAM_FROM_ACTION_CODE             12u
#define DP_VERIFY_FROM_ACTION_CODE              13u
/* Security only actions */
#define DP_ERASE_SECURITY_ACTION_CODE           14u
#define DP_PROGRAM_SECURITY_ACTION_CODE         15u
/* NVM only actions */
#define DP_PROGRAM_NVM_ACTION_CODE              16u
#define DP_VERIFY_NVM_ACTION_CODE               17u
#define DP_VERIFY_DEVICE_INFO_ACTION_CODE       18u
#define DP_READ_USERCODE_ACTION_CODE            19u
/* For P1 device, The following two actions are only supported with data files
* generated form V86 or later.  ENABLE_V85_DAT_SUPPORT must be disabled */
#define DP_PROGRAM_NVM_ACTIVE_ARRAY_ACTION_CODE 20u
#define DP_VERIFY_NVM_ACTIVE_ARRAY_ACTION_CODE  21u
#define DP_IS_CORE_CONFIGURED_ACTION_CODE       22u
#define DP_PROGRAM_PRIVATE_CLIENTS_ACTION_CODE  23u
#define DP_VERIFY_PRIVATE_CLIENTS_ACTION_CODE   24u
#define DP_PROGRAM_PRIVATE_CLIENTS_ACTIVE_ARRAY_ACTION_CODE  25u
#define DP_VERIFY_PRIVATE_CLIENTS_ACTIVE_ARRAY_ACTION_CODE   26u

/****************************************************************************/
/* External common global variables                                         */
/****************************************************************************/
extern DPUCHAR global_uchar; /* Global tmp should be used once and released */
extern DPULONG global_ulong;
extern DPUINT global_uint;
extern DPUCHAR global_buf1[global_buf_SIZE]; /* General purpose global_buffer */
extern DPUCHAR global_buf2[global_buf_SIZE];
extern DPUCHAR opcode;
extern DPULONG DataIndex;
extern DPUCHAR device_SD; /* Device specific number of SD tiles	*/
extern DPUINT device_rows; /* Device specific number of rows */
extern DPUCHAR device_family;
extern DPUINT dat_support_status;
extern DPUCHAR device_se_wait_cycle;
extern DPULONG device_ID;
extern DPUCHAR device_rev;
extern DPUCHAR Action_code;
extern DPULONG device_security_flags;
extern DPUINT device_bsr_bit_length;
extern DPUCHAR error_code;
extern DPUCHAR AES_mode_value;

/*
main entry function : user calls this function from their main function
*/
DPUCHAR dp_top(void);
void dp_check_action(void);
void dp_perform_action (void);
/* Action Function Definitions */
void dp_erase_action(void);
void dp_program_action(void);
void dp_verify_action(void);

void dp_check_device_ID(void);
void dp_check_device_ID_V85_DAT(void);
void dp_read_usercode_action(void);
void dp_test_reg_015_030_check(void);
void dp_frow_015_030_check(void);
void dp_initialize(void);
void dp_exit(void);
void dp_check_security_settings(void);
void dp_get_dat_dual_key_flag(void);
void dp_is_core_configured(void);

void dp_erase(void);
void dp_exe_erase(void);
void dp_poll_erase(void);
void dp_poll_device(void);
void dp_read_urow(void);
void dp_program_urow(void);
void dp_init_aes(void);
void dp_set_aes_mode(void);
void dp_vnr(void);
void dp_load_bsr(void);
void dp_read_factory_row(void);
void dp_das_check(void);

#ifdef ENABLE_DEBUG
void dp_device_info_action(void);
void dp_verify_device_info_action(void);
void dp_read_idcode_action(void);
void dp_read_silsig(void);
void dp_output_security(void);
void dp_display_urow(void);
#endif
#endif /* INC_DPALG_H */


