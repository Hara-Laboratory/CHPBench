`timescale 1ns / 1ps

module TopModule_tb;

// Inputs
reg [767:0] Din;
reg Drdy;
reg EN;
reg CLK;
reg RSTn;
reg [14:0] round;
reg [15:0] count;
// Outputs
wire [127:0] Dout;
wire Dvld;
wire BSY;
wire Trig;


// Instantiate the Unit Under Test (UUT)
sasebo_simon uut (
	.Din(Din), 
	.Dout(Dout), 
	.Drdy(Drdy), 
	.Dvld(Dvld), 
	.EN(EN), 
	.BSY(BSY), 
	.CLK(CLK), 
	.RSTn(RSTn), 
	.Trig(Trig)
);
always @(posedge CLK)
begin
round<=round+1;
end

always #5 CLK = ~CLK;
always @(posedge CLK)
begin
count<=count+1;
end
initial begin
	// Initialize Inputs
	count<=0;
	round<=0;
	Din = 0;
	Drdy = 0;
	EN = 0;
	CLK = 0;
	RSTn = 1;

	// Wait 100 ns for global reset to finish
	#20;
  RSTn = 0;
	#40;
	RSTn = 1;
	EN = 1;
	#20;
	Din = 768'h63736564207372656c6c6576617274200f0e0d0c0b0a0908070605040302010063736564207372656c6c6576617274200f0e0d0c0b0a0908070605040302010063736564207372656c6c6576617274200f0e0d0c0b0a09080706050403020100;
	#10;
	Drdy = 1;
	#10;
	Drdy = 0;
	
	// Add stimulus here

end
  
endmodule

