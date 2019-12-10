//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Mon Dec 09 21:43:58 2019
// Version: v11.9 11.9.0.4
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// touch
module touch(
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
wire   GPIO_0_OUT_net_0;
wire   GPIO_5_BI;
wire   GPIO_6_BI;
wire   GPIO_7_BI;
wire   GPIO_8_BI;
wire   I2C_1_SCL;
wire   I2C_1_SDA;
wire   MSS_RESET_N;
wire   SPI_1_CLK;
wire   SPI_1_DI;
wire   SPI_1_DO_net_0;
wire   SPI_1_SS;
wire   UART_0_RXD;
wire   UART_0_TXD_0;
wire   UART_1_RXD;
wire   UART_1_TXD_net_0;
wire   UART_1_TXD_net_1;
wire   SPI_1_DO_net_1;
wire   GPIO_0_OUT_net_1;
wire   UART_0_TXD_0_net_0;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_1_TXD_net_1   = UART_1_TXD_net_0;
assign UART_1_TXD         = UART_1_TXD_net_1;
assign SPI_1_DO_net_1     = SPI_1_DO_net_0;
assign SPI_1_DO           = SPI_1_DO_net_1;
assign GPIO_0_OUT_net_1   = GPIO_0_OUT_net_0;
assign GPIO_0_OUT         = GPIO_0_OUT_net_1;
assign UART_0_TXD_0_net_0 = UART_0_TXD_0;
assign UART_0_TXD         = UART_0_TXD_0_net_0;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------TouchScreenFinal
TouchScreenFinal TouchScreenFinal_0(
        // Inputs
        .UART_1_RXD  ( UART_1_RXD ),
        .MSS_RESET_N ( MSS_RESET_N ),
        .SPI_1_DI    ( SPI_1_DI ),
        .UART_0_RXD  ( UART_0_RXD ),
        // Outputs
        .UART_1_TXD  ( UART_1_TXD_net_0 ),
        .GPIO_0_OUT  ( GPIO_0_OUT_net_0 ),
        .SPI_1_DO    ( SPI_1_DO_net_0 ),
        .UART_0_TXD  ( UART_0_TXD_0 ),
        // Inouts
        .GPIO_8_BI   ( GPIO_8_BI ),
        .GPIO_7_BI   ( GPIO_7_BI ),
        .GPIO_6_BI   ( GPIO_6_BI ),
        .GPIO_5_BI   ( GPIO_5_BI ),
        .I2C_1_SCL   ( I2C_1_SCL ),
        .I2C_1_SDA   ( I2C_1_SDA ),
        .SPI_1_CLK   ( SPI_1_CLK ),
        .SPI_1_SS    ( SPI_1_SS ) 
        );


endmodule
