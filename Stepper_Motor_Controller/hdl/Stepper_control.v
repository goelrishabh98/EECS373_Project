///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: Stepper_control.v
// File history:
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <Description here>
//
// Targeted device: <Family::SmartFusion> <Die::A2F200M3F> <Package::484 FBGA>
// Author: <Name>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 

//`timescale <time_units> / <precision>

module Stepper_control(

/*** APB3 BUS INTERFACE ***/
input PCLK, // clock
input PRESERN, // system reset
input PSEL, // peripheral select
input PENABLE, // distinguishes access phase
output wire PREADY, // peripheral ready signal
output wire PSLVERR, // error signal
input PWRITE, // distinguishes read and write cycles
input [31:0] PADDR, // I/O address
input wire [31:0] PWDATA, // data from processor to I/O device (32 bits)
output reg [31:0] PRDATA, // data to processor from I/O device (32-bits)

/*** I/O PORTS DECLARATION ***/
output reg MS1,
output reg MS2,
output reg DIR,
output reg STEP,
input SW,
input SW2
);

assign PSLVERR = 0;
assign PREADY = 1;

wire stepper_write = PSEL & PWRITE &(PADDR); //enable LEDs write at offset #4

//////////////////////////////////
// end of APB3 interface header //
//////////////////////////////////

//As the only thing we read is the switch, we can constantly drive it!
always @(posedge PCLK) //register control for APB3 reads
begin
    PRDATA[31:1] <= 31'h00000000; //initialize the PRDATA
    PRDATA[0] <= 0; //read switch values to PRDATA
end

always @(posedge PCLK) // register control for APB3 writes
begin
    if(!PRESERN)
        LEDOUT <= 0; // LED should start turned "off"
                                          // recall it is active low.
    else if(stepper_write)
        LEDOUT <=0;
end
endmodule

