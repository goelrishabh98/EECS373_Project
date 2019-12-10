//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Mon Dec 09 21:42:35 2019
// Version: v11.9 11.9.0.4
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// TouchScreenFinal
module TouchScreenFinal(
    // Inputs
    MSS_RESET_N,
    SPI_1_DI,
    UART_0_RXD,
    UART_1_RXD,
    // Outputs
    GPIO_0_OUT,
    SPI_1_DO,
    UART_0_TXD,
    UART_1_TXD,
    // Inouts
    GPIO_5_BI,
    GPIO_6_BI,
    GPIO_7_BI,
    GPIO_8_BI,
    I2C_1_SCL,
    I2C_1_SDA,
    SPI_1_CLK,
    SPI_1_SS
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  MSS_RESET_N;
input  SPI_1_DI;
input  UART_0_RXD;
input  UART_1_RXD;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output GPIO_0_OUT;
output SPI_1_DO;
output UART_0_TXD;
output UART_1_TXD;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  GPIO_5_BI;
inout  GPIO_6_BI;
inout  GPIO_7_BI;
inout  GPIO_8_BI;
inout  I2C_1_SCL;
inout  I2C_1_SDA;
inout  SPI_1_CLK;
inout  SPI_1_SS;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire          GPIO_0_OUT_net_0;
wire          GPIO_5_BI;
wire          GPIO_6_BI;
wire          GPIO_7_BI;
wire          GPIO_8_BI;
wire          I2C_1_SCL;
wire          I2C_1_SDA;
wire          MSS_ADLIB_INST_EMCCLK;
wire          MSS_ADLIB_INST_FCLK;
wire          MSS_ADLIB_INST_MACCLK;
wire          MSS_ADLIB_INST_MACCLKCCC;
wire          MSS_ADLIB_INST_PLLLOCK;
wire   [0:0]  MSS_GPIO_0_GPIO_0_OUT_D;
wire   [5:5]  MSS_GPIO_0_GPIO_5_BI_D;
wire   [5:5]  MSS_GPIO_0_GPIO_5_BI_E;
wire          MSS_GPIO_0_GPIO_5_BI_Y;
wire   [6:6]  MSS_GPIO_0_GPIO_6_BI_D;
wire   [6:6]  MSS_GPIO_0_GPIO_6_BI_E;
wire          MSS_GPIO_0_GPIO_6_BI_Y;
wire   [7:7]  MSS_GPIO_0_GPIO_7_BI_D;
wire   [7:7]  MSS_GPIO_0_GPIO_7_BI_E;
wire          MSS_GPIO_0_GPIO_7_BI_Y;
wire   [8:8]  MSS_GPIO_0_GPIO_8_BI_D;
wire   [8:8]  MSS_GPIO_0_GPIO_8_BI_E;
wire          MSS_GPIO_0_GPIO_8_BI_Y;
wire          MSS_I2C_1_SCL_E;
wire          MSS_I2C_1_SCL_Y;
wire          MSS_I2C_1_SDA_E;
wire          MSS_I2C_1_SDA_Y;
wire          MSS_RESET_0_MSS_RESET_N_Y;
wire          MSS_RESET_N;
wire          MSS_SPI_1_CLK_D;
wire          MSS_SPI_1_CLK_Y;
wire          MSS_SPI_1_DI_Y;
wire          MSS_SPI_1_DO_D;
wire          MSS_SPI_1_DO_E;
wire   [0:0]  MSS_SPI_1_SS_D;
wire          MSS_SPI_1_SS_E;
wire          MSS_SPI_1_SS_Y;
wire          MSS_UART_0_RXD_Y;
wire          MSS_UART_0_TXD_D;
wire          MSS_UART_1_RXD_Y;
wire          MSS_UART_1_TXD_D;
wire          SPI_1_CLK;
wire          SPI_1_DI;
wire          SPI_1_DO_net_0;
wire          SPI_1_SS;
wire          UART_0_RXD;
wire          UART_0_TXD_net_0;
wire          UART_1_RXD;
wire          UART_1_TXD_net_0;
wire          UART_0_TXD_net_1;
wire          UART_1_TXD_net_1;
wire          SPI_1_DO_net_1;
wire          GPIO_0_OUT_net_1;
wire   [31:0] GPI_net_0;
wire   [31:0] GPO_net_0;
wire   [31:0] GPOE_net_0;
wire   [7:0]  SPI1SSO_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          GND_net;
wire          VCC_net;
wire   [1:0]  DMAREADY_const_net_0;
wire   [1:0]  MACF2MRXD_const_net_0;
wire   [1:0]  MACRXD_const_net_0;
wire   [15:0] EMCRDB_const_net_0;
wire   [31:0] MSSPRDATA_const_net_0;
wire   [31:0] FABPADDR_const_net_0;
wire   [31:0] FABPWDATA_const_net_0;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign GND_net               = 1'b0;
assign VCC_net               = 1'b1;
assign DMAREADY_const_net_0  = 2'h0;
assign MACF2MRXD_const_net_0 = 2'h0;
assign MACRXD_const_net_0    = 2'h0;
assign EMCRDB_const_net_0    = 16'h0000;
assign MSSPRDATA_const_net_0 = 32'h00000000;
assign FABPADDR_const_net_0  = 32'h00000000;
assign FABPWDATA_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_0_TXD_net_1 = UART_0_TXD_net_0;
assign UART_0_TXD       = UART_0_TXD_net_1;
assign UART_1_TXD_net_1 = UART_1_TXD_net_0;
assign UART_1_TXD       = UART_1_TXD_net_1;
assign SPI_1_DO_net_1   = SPI_1_DO_net_0;
assign SPI_1_DO         = SPI_1_DO_net_1;
assign GPIO_0_OUT_net_1 = GPIO_0_OUT_net_0;
assign GPIO_0_OUT       = GPIO_0_OUT_net_1;
//--------------------------------------------------------------------
// Slices assignments
//--------------------------------------------------------------------
assign MSS_GPIO_0_GPIO_0_OUT_D[0] = GPO_net_0[0:0];
assign MSS_GPIO_0_GPIO_5_BI_D[5]  = GPO_net_0[5:5];
assign MSS_GPIO_0_GPIO_5_BI_E[5]  = GPOE_net_0[5:5];
assign MSS_GPIO_0_GPIO_6_BI_D[6]  = GPO_net_0[6:6];
assign MSS_GPIO_0_GPIO_6_BI_E[6]  = GPOE_net_0[6:6];
assign MSS_GPIO_0_GPIO_7_BI_D[7]  = GPO_net_0[7:7];
assign MSS_GPIO_0_GPIO_7_BI_E[7]  = GPOE_net_0[7:7];
assign MSS_GPIO_0_GPIO_8_BI_D[8]  = GPO_net_0[8:8];
assign MSS_GPIO_0_GPIO_8_BI_E[8]  = GPOE_net_0[8:8];
assign MSS_SPI_1_SS_D[0]          = SPI1SSO_net_0[0:0];
//--------------------------------------------------------------------
// Concatenation assignments
//--------------------------------------------------------------------
assign GPI_net_0 = { 23'h000000 , MSS_GPIO_0_GPIO_8_BI_Y , MSS_GPIO_0_GPIO_7_BI_Y , MSS_GPIO_0_GPIO_6_BI_Y , MSS_GPIO_0_GPIO_5_BI_Y , 5'h00 };
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------MSS_APB
MSS_APB #( 
        .ACT_CONFIG ( 0 ),
        .ACT_DIE    ( "IP4X3M1" ),
        .ACT_FCLK   ( 100000000 ),
        .ACT_PKG    ( "fg484" ) )
MSS_ADLIB_INST(
        // Inputs
        .MSSPRDATA      ( MSSPRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .MSSPREADY      ( VCC_net ), // tied to 1'b1 from definition
        .MSSPSLVERR     ( GND_net ), // tied to 1'b0 from definition
        .FABPADDR       ( FABPADDR_const_net_0 ), // tied to 32'h00000000 from definition
        .FABPWDATA      ( FABPWDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .FABPWRITE      ( GND_net ), // tied to 1'b0 from definition
        .FABPSEL        ( GND_net ), // tied to 1'b0 from definition
        .FABPENABLE     ( GND_net ), // tied to 1'b0 from definition
        .SYNCCLKFDBK    ( GND_net ), // tied to 1'b0 from definition
        .CALIBIN        ( GND_net ), // tied to 1'b0 from definition
        .FABINT         ( GND_net ), // tied to 1'b0 from definition
        .F2MRESETn      ( VCC_net ), // tied to 1'b1 from definition
        .DMAREADY       ( DMAREADY_const_net_0 ), // tied to 2'h0 from definition
        .RXEV           ( GND_net ), // tied to 1'b0 from definition
        .VRON           ( GND_net ), // tied to 1'b0 from definition
        .GPI            ( GPI_net_0 ),
        .UART0CTSn      ( GND_net ), // tied to 1'b0 from definition
        .UART0DSRn      ( GND_net ), // tied to 1'b0 from definition
        .UART0RIn       ( GND_net ), // tied to 1'b0 from definition
        .UART0DCDn      ( GND_net ), // tied to 1'b0 from definition
        .UART1CTSn      ( GND_net ), // tied to 1'b0 from definition
        .UART1DSRn      ( GND_net ), // tied to 1'b0 from definition
        .UART1RIn       ( GND_net ), // tied to 1'b0 from definition
        .UART1DCDn      ( GND_net ), // tied to 1'b0 from definition
        .I2C0SMBUSNI    ( GND_net ), // tied to 1'b0 from definition
        .I2C0SMBALERTNI ( GND_net ), // tied to 1'b0 from definition
        .I2C0BCLK       ( GND_net ), // tied to 1'b0 from definition
        .I2C1SMBUSNI    ( GND_net ), // tied to 1'b0 from definition
        .I2C1SMBALERTNI ( GND_net ), // tied to 1'b0 from definition
        .I2C1BCLK       ( GND_net ), // tied to 1'b0 from definition
        .MACF2MRXD      ( MACF2MRXD_const_net_0 ), // tied to 2'h0 from definition
        .MACF2MCRSDV    ( GND_net ), // tied to 1'b0 from definition
        .MACF2MRXER     ( GND_net ), // tied to 1'b0 from definition
        .MACF2MMDI      ( GND_net ), // tied to 1'b0 from definition
        .FABSDD0D       ( GND_net ), // tied to 1'b0 from definition
        .FABSDD1D       ( GND_net ), // tied to 1'b0 from definition
        .FABSDD2D       ( GND_net ), // tied to 1'b0 from definition
        .FABSDD0CLK     ( GND_net ), // tied to 1'b0 from definition
        .FABSDD1CLK     ( GND_net ), // tied to 1'b0 from definition
        .FABSDD2CLK     ( GND_net ), // tied to 1'b0 from definition
        .FABACETRIG     ( GND_net ), // tied to 1'b0 from definition
        .LVTTL0EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL1EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL2EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL3EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL4EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL5EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL6EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL7EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL8EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL9EN       ( GND_net ), // tied to 1'b0 from definition
        .LVTTL10EN      ( GND_net ), // tied to 1'b0 from definition
        .LVTTL11EN      ( GND_net ), // tied to 1'b0 from definition
        .FCLK           ( MSS_ADLIB_INST_FCLK ),
        .MACCLKCCC      ( MSS_ADLIB_INST_MACCLKCCC ),
        .RCOSC          ( GND_net ), // tied to 1'b0 from definition
        .MACCLK         ( MSS_ADLIB_INST_MACCLK ),
        .PLLLOCK        ( MSS_ADLIB_INST_PLLLOCK ),
        .MSSRESETn      ( MSS_RESET_0_MSS_RESET_N_Y ),
        .SPI0DI         ( GND_net ), // tied to 1'b0 from definition
        .SPI0CLKI       ( GND_net ), // tied to 1'b0 from definition
        .SPI0SSI        ( GND_net ), // tied to 1'b0 from definition
        .UART0RXD       ( MSS_UART_0_RXD_Y ),
        .I2C0SDAI       ( GND_net ), // tied to 1'b0 from definition
        .I2C0SCLI       ( GND_net ), // tied to 1'b0 from definition
        .SPI1DI         ( MSS_SPI_1_DI_Y ),
        .SPI1CLKI       ( MSS_SPI_1_CLK_Y ),
        .SPI1SSI        ( MSS_SPI_1_SS_Y ),
        .UART1RXD       ( MSS_UART_1_RXD_Y ),
        .I2C1SDAI       ( MSS_I2C_1_SDA_Y ),
        .I2C1SCLI       ( MSS_I2C_1_SCL_Y ),
        .MACRXD         ( MACRXD_const_net_0 ), // tied to 2'h0 from definition
        .MACCRSDV       ( GND_net ), // tied to 1'b0 from definition
        .MACRXER        ( GND_net ), // tied to 1'b0 from definition
        .MACMDI         ( GND_net ), // tied to 1'b0 from definition
        .EMCCLKRTN      ( MSS_ADLIB_INST_EMCCLK ),
        .EMCRDB         ( EMCRDB_const_net_0 ), // tied to 16'h0000 from definition
        .ADC0           ( GND_net ), // tied to 1'b0 from definition
        .ADC1           ( GND_net ), // tied to 1'b0 from definition
        .ADC2           ( GND_net ), // tied to 1'b0 from definition
        .ADC3           ( GND_net ), // tied to 1'b0 from definition
        .ADC4           ( GND_net ), // tied to 1'b0 from definition
        .ADC5           ( GND_net ), // tied to 1'b0 from definition
        .ADC6           ( GND_net ), // tied to 1'b0 from definition
        .ADC7           ( GND_net ), // tied to 1'b0 from definition
        .ADC8           ( GND_net ), // tied to 1'b0 from definition
        .ADC9           ( GND_net ), // tied to 1'b0 from definition
        .ADC10          ( GND_net ), // tied to 1'b0 from definition
        .ADC11          ( GND_net ), // tied to 1'b0 from definition
        .ABPS0          ( GND_net ), // tied to 1'b0 from definition
        .ABPS1          ( GND_net ), // tied to 1'b0 from definition
        .ABPS2          ( GND_net ), // tied to 1'b0 from definition
        .ABPS3          ( GND_net ), // tied to 1'b0 from definition
        .ABPS4          ( GND_net ), // tied to 1'b0 from definition
        .ABPS5          ( GND_net ), // tied to 1'b0 from definition
        .ABPS6          ( GND_net ), // tied to 1'b0 from definition
        .ABPS7          ( GND_net ), // tied to 1'b0 from definition
        .ABPS8          ( GND_net ), // tied to 1'b0 from definition
        .ABPS9          ( GND_net ), // tied to 1'b0 from definition
        .ABPS10         ( GND_net ), // tied to 1'b0 from definition
        .ABPS11         ( GND_net ), // tied to 1'b0 from definition
        .TM0            ( GND_net ), // tied to 1'b0 from definition
        .TM1            ( GND_net ), // tied to 1'b0 from definition
        .TM2            ( GND_net ), // tied to 1'b0 from definition
        .TM3            ( GND_net ), // tied to 1'b0 from definition
        .TM4            ( GND_net ), // tied to 1'b0 from definition
        .TM5            ( GND_net ), // tied to 1'b0 from definition
        .CM0            ( GND_net ), // tied to 1'b0 from definition
        .CM1            ( GND_net ), // tied to 1'b0 from definition
        .CM2            ( GND_net ), // tied to 1'b0 from definition
        .CM3            ( GND_net ), // tied to 1'b0 from definition
        .CM4            ( GND_net ), // tied to 1'b0 from definition
        .CM5            ( GND_net ), // tied to 1'b0 from definition
        .GNDTM0         ( GND_net ), // tied to 1'b0 from definition
        .GNDTM1         ( GND_net ), // tied to 1'b0 from definition
        .GNDTM2         ( GND_net ), // tied to 1'b0 from definition
        .VAREF0         ( GND_net ), // tied to 1'b0 from definition
        .VAREF1         ( GND_net ), // tied to 1'b0 from definition
        .VAREF2         ( GND_net ), // tied to 1'b0 from definition
        .GNDVAREF       ( GND_net ), // tied to 1'b0 from definition
        .PUn            ( GND_net ), // tied to 1'b0 from definition
        // Outputs
        .MSSPADDR       (  ),
        .MSSPWDATA      (  ),
        .MSSPWRITE      (  ),
        .MSSPSEL        (  ),
        .MSSPENABLE     (  ),
        .FABPRDATA      (  ),
        .FABPREADY      (  ),
        .FABPSLVERR     (  ),
        .CALIBOUT       (  ),
        .MSSINT         (  ),
        .WDINT          (  ),
        .M2FRESETn      (  ),
        .DEEPSLEEP      (  ),
        .SLEEP          (  ),
        .TXEV           (  ),
        .GPO            ( GPO_net_0 ),
        .UART0RTSn      (  ),
        .UART0DTRn      (  ),
        .UART1RTSn      (  ),
        .UART1DTRn      (  ),
        .I2C0SMBUSNO    (  ),
        .I2C0SMBALERTNO (  ),
        .I2C1SMBUSNO    (  ),
        .I2C1SMBALERTNO (  ),
        .MACM2FTXD      (  ),
        .MACM2FTXEN     (  ),
        .MACM2FMDO      (  ),
        .MACM2FMDEN     (  ),
        .MACM2FMDC      (  ),
        .ACEFLAGS       (  ),
        .CMP0           (  ),
        .CMP1           (  ),
        .CMP2           (  ),
        .CMP3           (  ),
        .CMP4           (  ),
        .CMP5           (  ),
        .CMP6           (  ),
        .CMP7           (  ),
        .CMP8           (  ),
        .CMP9           (  ),
        .CMP10          (  ),
        .CMP11          (  ),
        .LVTTL0         (  ),
        .LVTTL1         (  ),
        .LVTTL2         (  ),
        .LVTTL3         (  ),
        .LVTTL4         (  ),
        .LVTTL5         (  ),
        .LVTTL6         (  ),
        .LVTTL7         (  ),
        .LVTTL8         (  ),
        .LVTTL9         (  ),
        .LVTTL10        (  ),
        .LVTTL11        (  ),
        .PUFABn         (  ),
        .VCC15GOOD      (  ),
        .VCC33GOOD      (  ),
        .GPOE           ( GPOE_net_0 ),
        .SPI0DO         (  ),
        .SPI0DOE        (  ),
        .SPI0CLKO       (  ),
        .SPI0MODE       (  ),
        .SPI0SSO        (  ),
        .UART0TXD       ( MSS_UART_0_TXD_D ),
        .I2C0SDAO       (  ),
        .I2C0SCLO       (  ),
        .SPI1DO         ( MSS_SPI_1_DO_D ),
        .SPI1DOE        ( MSS_SPI_1_DO_E ),
        .SPI1CLKO       ( MSS_SPI_1_CLK_D ),
        .SPI1MODE       ( MSS_SPI_1_SS_E ),
        .SPI1SSO        ( SPI1SSO_net_0 ),
        .UART1TXD       ( MSS_UART_1_TXD_D ),
        .I2C1SDAO       ( MSS_I2C_1_SDA_E ),
        .I2C1SCLO       ( MSS_I2C_1_SCL_E ),
        .MACTXD         (  ),
        .MACTXEN        (  ),
        .MACMDO         (  ),
        .MACMDEN        (  ),
        .MACMDC         (  ),
        .EMCCLK         ( MSS_ADLIB_INST_EMCCLK ),
        .EMCAB          (  ),
        .EMCWDB         (  ),
        .EMCRWn         (  ),
        .EMCCS0n        (  ),
        .EMCCS1n        (  ),
        .EMCOEN0n       (  ),
        .EMCOEN1n       (  ),
        .EMCBYTEN       (  ),
        .EMCDBOE        (  ),
        .SDD0           (  ),
        .SDD1           (  ),
        .SDD2           (  ),
        .VAREFOUT       (  ) 
        );

//--------TouchScreenFinal_tmp_MSS_CCC_0_MSS_CCC   -   Actel:SmartFusionMSS:MSS_CCC:2.0.106
TouchScreenFinal_tmp_MSS_CCC_0_MSS_CCC MSS_CCC_0(
        // Inputs
        .CLKA           ( GND_net ), // tied to 1'b0 from definition
        .CLKA_PAD       ( GND_net ), // tied to 1'b0 from definition
        .CLKA_PADP      ( GND_net ), // tied to 1'b0 from definition
        .CLKA_PADN      ( GND_net ), // tied to 1'b0 from definition
        .CLKB           ( GND_net ), // tied to 1'b0 from definition
        .CLKB_PAD       ( GND_net ), // tied to 1'b0 from definition
        .CLKB_PADP      ( GND_net ), // tied to 1'b0 from definition
        .CLKB_PADN      ( GND_net ), // tied to 1'b0 from definition
        .CLKC           ( GND_net ), // tied to 1'b0 from definition
        .CLKC_PAD       ( GND_net ), // tied to 1'b0 from definition
        .CLKC_PADP      ( GND_net ), // tied to 1'b0 from definition
        .CLKC_PADN      ( GND_net ), // tied to 1'b0 from definition
        .MAINXIN        ( GND_net ), // tied to 1'b0 from definition
        .LPXIN          ( GND_net ), // tied to 1'b0 from definition
        .MAC_CLK        ( GND_net ), // tied to 1'b0 from definition
        // Outputs
        .GLA            (  ),
        .GLB            (  ),
        .GLC            (  ),
        .FAB_CLK        (  ),
        .YB             (  ),
        .YC             (  ),
        .FAB_LOCK       (  ),
        .RCOSC_CLKOUT   (  ),
        .MAINXIN_CLKOUT (  ),
        .LPXIN_CLKOUT   (  ),
        .GLA0           ( MSS_ADLIB_INST_FCLK ),
        .MSS_LOCK       ( MSS_ADLIB_INST_PLLLOCK ),
        .MAC_CLK_CCC    ( MSS_ADLIB_INST_MACCLKCCC ),
        .MAC_CLK_IO     ( MSS_ADLIB_INST_MACCLK ) 
        );

//--------OUTBUF_MSS
OUTBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "V1" ) )
MSS_GPIO_0_GPIO_0_OUT(
        // Inputs
        .D   ( MSS_GPIO_0_GPIO_0_OUT_D ),
        // Outputs
        .PAD ( GPIO_0_OUT_net_0 ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "U2" ) )
MSS_GPIO_0_GPIO_5_BI(
        // Inputs
        .D   ( MSS_GPIO_0_GPIO_5_BI_D ),
        .E   ( MSS_GPIO_0_GPIO_5_BI_E ),
        // Outputs
        .Y   ( MSS_GPIO_0_GPIO_5_BI_Y ),
        // Inouts
        .PAD ( GPIO_5_BI ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "V2" ) )
MSS_GPIO_0_GPIO_6_BI(
        // Inputs
        .D   ( MSS_GPIO_0_GPIO_6_BI_D ),
        .E   ( MSS_GPIO_0_GPIO_6_BI_E ),
        // Outputs
        .Y   ( MSS_GPIO_0_GPIO_6_BI_Y ),
        // Inouts
        .PAD ( GPIO_6_BI ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "W2" ) )
MSS_GPIO_0_GPIO_7_BI(
        // Inputs
        .D   ( MSS_GPIO_0_GPIO_7_BI_D ),
        .E   ( MSS_GPIO_0_GPIO_7_BI_E ),
        // Outputs
        .Y   ( MSS_GPIO_0_GPIO_7_BI_Y ),
        // Inouts
        .PAD ( GPIO_7_BI ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "T3" ) )
MSS_GPIO_0_GPIO_8_BI(
        // Inputs
        .D   ( MSS_GPIO_0_GPIO_8_BI_D ),
        .E   ( MSS_GPIO_0_GPIO_8_BI_E ),
        // Outputs
        .Y   ( MSS_GPIO_0_GPIO_8_BI_Y ),
        // Inouts
        .PAD ( GPIO_8_BI ) 
        );

//--------BIBUF_OPEND_MSS
BIBUF_OPEND_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "U20" ) )
MSS_I2C_1_SCL(
        // Inputs
        .E   ( MSS_I2C_1_SCL_E ),
        // Outputs
        .Y   ( MSS_I2C_1_SCL_Y ),
        // Inouts
        .PAD ( I2C_1_SCL ) 
        );

//--------BIBUF_OPEND_MSS
BIBUF_OPEND_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "V22" ) )
MSS_I2C_1_SDA(
        // Inputs
        .E   ( MSS_I2C_1_SDA_E ),
        // Outputs
        .Y   ( MSS_I2C_1_SDA_Y ),
        // Inouts
        .PAD ( I2C_1_SDA ) 
        );

//--------INBUF_MSS
INBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "R1" ) )
MSS_RESET_0_MSS_RESET_N(
        // Inputs
        .PAD ( MSS_RESET_N ),
        // Outputs
        .Y   ( MSS_RESET_0_MSS_RESET_N_Y ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "AA22" ) )
MSS_SPI_1_CLK(
        // Inputs
        .D   ( MSS_SPI_1_CLK_D ),
        .E   ( MSS_SPI_1_SS_E ),
        // Outputs
        .Y   ( MSS_SPI_1_CLK_Y ),
        // Inouts
        .PAD ( SPI_1_CLK ) 
        );

//--------INBUF_MSS
INBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "V19" ) )
MSS_SPI_1_DI(
        // Inputs
        .PAD ( SPI_1_DI ),
        // Outputs
        .Y   ( MSS_SPI_1_DI_Y ) 
        );

//--------TRIBUFF_MSS
TRIBUFF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "T17" ) )
MSS_SPI_1_DO(
        // Inputs
        .D   ( MSS_SPI_1_DO_D ),
        .E   ( MSS_SPI_1_DO_E ),
        // Outputs
        .PAD ( SPI_1_DO_net_0 ) 
        );

//--------BIBUF_MSS
BIBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "W21" ) )
MSS_SPI_1_SS(
        // Inputs
        .D   ( MSS_SPI_1_SS_D ),
        .E   ( MSS_SPI_1_SS_E ),
        // Outputs
        .Y   ( MSS_SPI_1_SS_Y ),
        // Inouts
        .PAD ( SPI_1_SS ) 
        );

//--------INBUF_MSS
INBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "U18" ) )
MSS_UART_0_RXD(
        // Inputs
        .PAD ( UART_0_RXD ),
        // Outputs
        .Y   ( MSS_UART_0_RXD_Y ) 
        );

//--------OUTBUF_MSS
OUTBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "Y22" ) )
MSS_UART_0_TXD(
        // Inputs
        .D   ( MSS_UART_0_TXD_D ),
        // Outputs
        .PAD ( UART_0_TXD_net_0 ) 
        );

//--------INBUF_MSS
INBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "W22" ) )
MSS_UART_1_RXD(
        // Inputs
        .PAD ( UART_1_RXD ),
        // Outputs
        .Y   ( MSS_UART_1_RXD_Y ) 
        );

//--------OUTBUF_MSS
OUTBUF_MSS #( 
        .ACT_CONFIG ( 2 ),
        .ACT_PIN    ( "V20" ) )
MSS_UART_1_TXD(
        // Inputs
        .D   ( MSS_UART_1_TXD_D ),
        // Outputs
        .PAD ( UART_1_TXD_net_0 ) 
        );


endmodule
