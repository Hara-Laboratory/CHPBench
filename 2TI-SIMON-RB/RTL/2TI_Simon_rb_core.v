`timescale 1ns / 1ps

module simon2share(clk, data_ina, data_inb, data_rdy, cipher_out, Done, Trig);

input clk;
input data_ina, data_inb;
input [1:0] data_rdy;
output [127:0] cipher_out;
output reg Done, Trig;

reg [7:0] counter;
wire [63:0] keya, keyb;

always@(posedge clk)
begin
	if(data_rdy==0) begin
		counter <= 0;
	end
	else if(data_rdy ==3) begin			
		counter <= counter + 1;
	end
end

always @(posedge clk) begin
	if (counter == 1) //So it means first 1 rounds
		Trig <= 1;
	else
		Trig <= 0;
	if(data_rdy == 3 && (counter == 134))
		Done <= 1;			
	else
		Done <= 0;
end

p_datapath mydatapath(.clk(clk), .counter(counter), 
							 .data_ina(data_ina), .data_inb(data_inb),
							 .data_rdy(data_rdy), 
							 .key_ina(keya), .key_inb(keyb), 
							 .cipher_out(cipher_out));
					 
p_keysch10 mykeysch_a(.clk(clk), .counter(counter), 
							 .data_in(data_ina), .data_rdy(data_rdy), .key_out(keya));
							 
p_keysch11 mykeysch_b(.clk(clk), .counter(counter), 
							 .data_in(data_inb), .data_rdy(data_rdy), .key_out(keyb));						 
endmodule


