//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Sat Nov 23 20:43:09 2019
// Version: v11.9 11.9.0.4
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// mss
module mss(
    // Inputs
    ADCDirectInput_0,
    ADCDirectInput_1,
    MSS_RESET_N,
    SPI_0_DI,
    UART_0_RXD,
    VAREF0,
    // Outputs
    SPI_0_DO,
    UART_0_TXD,
    // Inouts
    GPIO_0_BI,
    GPIO_1_BI,
    GPIO_2_BI,
    GPIO_3_BI,
    SPI_0_CLK,
    SPI_0_SS
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  ADCDirectInput_0;
input  ADCDirectInput_1;
input  MSS_RESET_N;
input  SPI_0_DI;
input  UART_0_RXD;
input  VAREF0;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output SPI_0_DO;
output UART_0_TXD;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  GPIO_0_BI;
inout  GPIO_1_BI;
inout  GPIO_2_BI;
inout  GPIO_3_BI;
inout  SPI_0_CLK;
inout  SPI_0_SS;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   ADCDirectInput_0;
wire   ADCDirectInput_1;
wire   GPIO_0_BI;
wire   GPIO_1_BI;
wire   GPIO_2_BI;
wire   GPIO_3_BI;
wire   MSS_RESET_N;
wire   SPI_0_CLK;
wire   SPI_0_DI;
wire   SPI_0_DO_net_0;
wire   SPI_0_SS;
wire   UART_0_RXD;
wire   UART_0_TXD_net_0;
wire   VAREF0;
wire   UART_0_TXD_net_1;
wire   SPI_0_DO_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_0_TXD_net_1 = UART_0_TXD_net_0;
assign UART_0_TXD       = UART_0_TXD_net_1;
assign SPI_0_DO_net_1   = SPI_0_DO_net_0;
assign SPI_0_DO         = SPI_0_DO_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------TouchScreenController
TouchScreenController TouchScreenController_0(
        // Inputs
        .UART_0_RXD       ( UART_0_RXD ),
        .SPI_0_DI         ( SPI_0_DI ),
        .MSS_RESET_N      ( MSS_RESET_N ),
        .ADCDirectInput_0 ( ADCDirectInput_0 ),
        .ADCDirectInput_1 ( ADCDirectInput_1 ),
        .VAREF0           ( VAREF0 ),
        // Outputs
        .UART_0_TXD       ( UART_0_TXD_net_0 ),
        .SPI_0_DO         ( SPI_0_DO_net_0 ),
        // Inouts
        .SPI_0_CLK        ( SPI_0_CLK ),
        .SPI_0_SS         ( SPI_0_SS ),
        .GPIO_3_BI        ( GPIO_3_BI ),
        .GPIO_2_BI        ( GPIO_2_BI ),
        .GPIO_1_BI        ( GPIO_1_BI ),
        .GPIO_0_BI        ( GPIO_0_BI ) 
        );


endmodule
