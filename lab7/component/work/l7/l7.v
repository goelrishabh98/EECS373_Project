//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Sun Dec 01 15:28:49 2019
// Version: v11.9 11.9.0.4
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// l7
module l7(
    // Inputs
    ADCDirectInput_5,
    MSS_RESET_N,
    UART_0_RXD,
    VAREF1,
    // Outputs
    SDD_1,
    UART_0_TXD
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  ADCDirectInput_5;
input  MSS_RESET_N;
input  UART_0_RXD;
input  VAREF1;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output SDD_1;
output UART_0_TXD;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   ADCDirectInput_5;
wire   MSS_RESET_N;
wire   SDD_1_net_0;
wire   UART_0_RXD;
wire   UART_0_TXD_net_0;
wire   VAREF1;
wire   SDD_1_net_1;
wire   UART_0_TXD_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign SDD_1_net_1      = SDD_1_net_0;
assign SDD_1            = SDD_1_net_1;
assign UART_0_TXD_net_1 = UART_0_TXD_net_0;
assign UART_0_TXD       = UART_0_TXD_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------lab7
lab7 lab7_0(
        // Inputs
        .MSS_RESET_N      ( MSS_RESET_N ),
        .ADCDirectInput_5 ( ADCDirectInput_5 ),
        .VAREF1           ( VAREF1 ),
        .UART_0_RXD       ( UART_0_RXD ),
        // Outputs
        .SDD_1            ( SDD_1_net_0 ),
        .UART_0_TXD       ( UART_0_TXD_net_0 ) 
        );


endmodule
