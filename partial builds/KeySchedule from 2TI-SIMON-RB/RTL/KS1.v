`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/01/19 13:52:28
// Design Name: 
// Module Name: KS1
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module p_keysch10(clk, counter, data_in, data_rdy, key_out);
input clk, data_in;
input [1:0] data_rdy;
input [7:0] counter;
output [63:0] key_out;

reg [63:0] KX, KY;
reg [0:67] Z = 68'b10101111011100000011010010011000101000010001111110010110110011101011;
reg [63:0] c = 64'hfffffffffffffffc;


always@(posedge clk)
begin
	if(data_rdy == 2) begin
		{KX, KY} <= {data_in, KX, KY[63:1]};
	end
	else if(data_rdy == 3) begin
		if(counter[0] == 1'b1) begin
			KX <= c ^ Z[counter[7:1]] ^ KY ^ {KX[2:0],KX[63:3]} ^ {KX[3:0],KX[63:4]};
			KY <= KX;
		end
	end
end
assign key_out = KY ;

endmodule