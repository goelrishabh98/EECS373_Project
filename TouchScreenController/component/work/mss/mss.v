//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Fri Dec 06 00:55:40 2019
// Version: v11.9 11.9.0.4
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// mss
module mss(
    // Inputs
    ADCDirectInput_0,
    ADCDirectInput_1,
    MSS_RESET_N,
    SPI_1_DI,
    UART_0_RXD,
    UART_1_RXD,
    VAREF0,
    VAREF1,
    // Outputs
    GPIO_0_OUT,
    SPI_1_DO,
    UART_0_TXD,
    UART_1_TXD,
    // Inouts
    GPIO_1_BI,
    GPIO_2_BI,
    GPIO_3_BI,
    GPIO_4_BI,
    SPI_1_CLK,
    SPI_1_SS
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  ADCDirectInput_0;
input  ADCDirectInput_1;
input  MSS_RESET_N;
input  SPI_1_DI;
input  UART_0_RXD;
input  UART_1_RXD;
input  VAREF0;
input  VAREF1;
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
inout  GPIO_1_BI;
inout  GPIO_2_BI;
inout  GPIO_3_BI;
inout  GPIO_4_BI;
inout  SPI_1_CLK;
inout  SPI_1_SS;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   ADCDirectInput_0;
wire   ADCDirectInput_1;
wire   GPIO_0_OUT_net_0;
wire   GPIO_1_BI;
wire   GPIO_2_BI;
wire   GPIO_3_BI;
wire   GPIO_4_BI;
wire   MSS_RESET_N;
wire   SPI_1_CLK;
wire   SPI_1_DI;
wire   SPI_1_DO_net_0;
wire   SPI_1_SS;
wire   UART_0_RXD;
wire   UART_0_TXD_net_0;
wire   UART_1_RXD;
wire   UART_1_TXD_net_0;
wire   VAREF0;
wire   VAREF1;
wire   UART_0_TXD_net_1;
wire   SPI_1_DO_net_1;
wire   UART_1_TXD_net_1;
wire   GPIO_0_OUT_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_0_TXD_net_1 = UART_0_TXD_net_0;
assign UART_0_TXD       = UART_0_TXD_net_1;
assign SPI_1_DO_net_1   = SPI_1_DO_net_0;
assign SPI_1_DO         = SPI_1_DO_net_1;
assign UART_1_TXD_net_1 = UART_1_TXD_net_0;
assign UART_1_TXD       = UART_1_TXD_net_1;
assign GPIO_0_OUT_net_1 = GPIO_0_OUT_net_0;
assign GPIO_0_OUT       = GPIO_0_OUT_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------TouchScreenController
TouchScreenController TouchScreenController_0(
        // Inputs
        .UART_0_RXD       ( UART_0_RXD ),
        .MSS_RESET_N      ( MSS_RESET_N ),
        .VAREF0           ( VAREF0 ),
        .SPI_1_DI         ( SPI_1_DI ),
        .UART_1_RXD       ( UART_1_RXD ),
        .ADCDirectInput_0 ( ADCDirectInput_0 ),
        .ADCDirectInput_1 ( ADCDirectInput_1 ),
        .VAREF1           ( VAREF1 ),
        // Outputs
        .UART_0_TXD       ( UART_0_TXD_net_0 ),
        .SPI_1_DO         ( SPI_1_DO_net_0 ),
        .UART_1_TXD       ( UART_1_TXD_net_0 ),
        .GPIO_0_OUT       ( GPIO_0_OUT_net_0 ),
        // Inouts
        .GPIO_3_BI        ( GPIO_3_BI ),
        .GPIO_2_BI        ( GPIO_2_BI ),
        .GPIO_1_BI        ( GPIO_1_BI ),
        .SPI_1_CLK        ( SPI_1_CLK ),
        .SPI_1_SS         ( SPI_1_SS ),
        .GPIO_4_BI        ( GPIO_4_BI ) 
        );


endmodule
