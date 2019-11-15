module stepper_control(

/*** APB3 BUS INTERFACE ***/
input PCLK, 				// clock
input PRESERN, 				// system reset
input PSEL, 				// peripheral select
input PENABLE, 				// distinguishes access phase
output wire PREADY, 		// peripheral ready signal
output wire PSLVERR,		// error signal
input PWRITE,				// distinguishes read and write cycles
input [31:0] PADDR,			// I/O address
input wire [31:0] PWDATA,	// data from processor to I/O device (32 bits)
output reg [31:0] PRDATA,	// data to processor from I/O device (32-bits)

/*** I/O PORTS DECLARATION ***/	
output reg step1,			// output to step pin
output reg dir1,              // output to dir pin
output reg step2,
output reg dir2
); 

assign PSLVERR = 0;
assign PREADY = 1;
reg [7:0] count1, count2;
wire stepper_write = PSEL & PWRITE;   //enable LEDs write at offset #4
reg count_bool1, count_bool2;
//////////////////////////////////
// end of APB3 interface header //
//////////////////////////////////

//As the only thing we read is the switch, we can constantly drive it!		


always @(posedge PCLK) 		// register control for APB3 writes
begin
	if(!PRESERN)
		dir1 <= 0;  // LED should start turned "off"
												// recall it is active low. 
	else if(stepper_write)
		dir1 <= PWDATA[0];
end

always @(posedge PCLK)
begin
   if(!PRESERN)
        step1 <= 0;
   else if(count_bool1 & count1 > 50 & count1 < 200)
        step1 <= 1;
   else
        step1 <= 0;
end

always @(posedge PCLK) 		// register control for APB3 writes
begin
	if(!PRESERN)
		count_bool1 <= 0;  // LED should start turned "off"
												// recall it is active low. 
	else if(stepper_write)
		count_bool1 <= 1;
    else if(count1 > 200)
        count_bool1 <= 0;
end


always @(posedge PCLK)
begin
   if(!PRESERN)
        count1 <= 0;
    else if(count_bool1 & count1 < 201)
        count1 <= count1 +1;
    else
        count1 <= 0;
end

always @(posedge PCLK) 		// register control for APB3 writes
begin
	if(!PRESERN)
		dir2 <= 0;  // LED should start turned "off"
												// recall it is active low. 
	else if(stepper_write)
		dir2 <= PWDATA[1];
end

always @(posedge PCLK)
begin
   if(!PRESERN)
        step2 <= 0;
   else if(count_bool2 & count2 > 50 & count2 < 200)
        step2 <= 1;
   else
        step2 <= 0;
end

always @(posedge PCLK) 		// register control for APB3 writes
begin
	if(!PRESERN)
		count_bool2 <= 0;  // LED should start turned "off"
												// recall it is active low. 
	else if(stepper_write)
		count_bool2 <= 1;
    else if(count2 > 200)
        count_bool2 <= 0;
end


always @(posedge PCLK)
begin
   if(!PRESERN)
        count2 <= 0;
    else if(count_bool2 & count2 < 201)
        count2 <= count2 +1;
    else
        count2 <= 0;
end

endmodule