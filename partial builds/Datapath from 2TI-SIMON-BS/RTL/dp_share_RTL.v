module datapath_share(clk, data_in, key_in, shifter_enable1, shifter_enable2, cipher_out, 
		 			  lut_rol8_shifted_ext, lut_rol8_shifted_out, s1, s2, s3);

	// interfaces
	input clk;
	input data_in, key_in;
	input s1, s2;
	input [1:0] s3;
	input shifter_enable1, shifter_enable2;
	input lut_rol8_shifted_ext;
	output cipher_out;
	output reg lut_rol8_shifted_out;
	
	// shift register 
	reg [54:0] shifter1;
	reg [63:0] shifter2;
	reg shift_in1,shift_in2;
	wire shift_out1,shift_out2;
	
	// FIFO
	reg fifo_ff62,fifo_ff61,fifo_ff60,fifo_ff59,fifo_ff58,fifo_ff57,fifo_ff56, fifo_ff55;
	reg lut_ff62,lut_ff61,lut_ff60,lut_ff59,lut_ff58,lut_ff57,lut_ff56, lut_ff55;
	reg ff63;
	
	reg lut_ff_input,fifo_ff_input, ff_input;
	reg lut_rol1,lut_rol2,lut_rol8;
	reg lut_rol1_shifted;
	wire lut_out;
	// Loading data in
	always @(posedge clk)
	begin
		if(shifter_enable1)
			shifter1 <= {shift_in1, shifter1[54:1]};
	end
	
	assign shift_out1 = shifter1[0];
	
	always @(posedge clk)
	begin
		if(shifter_enable2)
			shifter2 <= {shift_in2, shifter2[63:1]};
	end
	
	assign shift_out2 = shifter2[0];
	
	always@(posedge clk)
	begin
		ff63 <= ff_input;
		if(shifter_enable1)
		begin	
			fifo_ff62 <= fifo_ff_input;
			fifo_ff61 <= fifo_ff62;
			fifo_ff60 <= fifo_ff61;
			fifo_ff59 <= fifo_ff60;
			fifo_ff58 <= fifo_ff59;
			fifo_ff57 <= fifo_ff58;
			fifo_ff56 <= fifo_ff57;
			fifo_ff55 <= fifo_ff56;
		end
	end

	always@(posedge clk)
	begin
		if(shifter_enable1)
		begin
			lut_ff62 <= lut_ff_input;
			lut_ff61 <= lut_ff62;
			lut_ff60 <= lut_ff61;
			lut_ff59 <= lut_ff60;
			lut_ff58 <= lut_ff59;
			lut_ff57 <= lut_ff58;
			lut_ff56 <= lut_ff57;
			lut_ff55 <= lut_ff56;
		end
	end
	
	always@(*)
	begin
			shift_in2 = shift_out1;
	end
	
	always@(*)
	begin
		if(s1 == 0)
			shift_in1 = lut_ff55;
		else
			shift_in1 = fifo_ff55;
	end
	
	always@(*)
	begin
		if(s3 == 0)
			ff_input = data_in;
		else if(s3 == 1) begin
			ff_input = shift_out1;
		end
		else if(s3 == 2) begin
			ff_input = lut_out;
		end
		else
			ff_input = ff_input; 
	end
	
	always@(*)
	begin
		if(s2 == 0) 
			fifo_ff_input = ff63;
		else
			fifo_ff_input = lut_out;
	end
	
	always@(*)
	begin
		if(s2 == 1)
			lut_ff_input = ff63;
		else
			lut_ff_input = lut_out;
	end
	
	always@(*)
	begin
		lut_rol1 = ff63;
		
		if(s2 == 0) 
			lut_rol1_shifted = fifo_ff62;
		else
			lut_rol1_shifted = lut_ff62;
		
		if(s2 == 0)
			lut_rol8_shifted_out = fifo_ff55;
		else
			lut_rol8_shifted_out = lut_ff55;
		
		if(s2 == 0)
			lut_rol2 = fifo_ff62;
		else
			lut_rol2 = lut_ff62;
			
		if(s2 == 0)
			lut_rol8 = fifo_ff56;
		else
			lut_rol8 = lut_ff56;
	end

	lut_datapath LUT_A_DATAPATH 
	(.clk(clk), .out(lut_out), .shift_out2(shift_out2), .key_in(key_in), .lut_rol2(lut_rol2), 
	 .lut_rol1(lut_rol1), .lut_rol8(lut_rol8), 
	 .lut_rol1_shifted(lut_rol1_shifted), .lut_rol8_ext(lut_rol8_shifted_ext));
	 
	assign cipher_out = lut_out; 
endmodule

//================================================ lut_datapath
module lut_datapath
	(clk, out, shift_out2, key_in, lut_rol2, lut_rol1, lut_rol8, lut_rol1_shifted, lut_rol8_ext);
	
	//------------------------------------------------
	input clk, shift_out2, key_in, lut_rol2, lut_rol1, lut_rol8, lut_rol1_shifted, lut_rol8_ext;
	output out;
	reg intreg;
	//------------------------------------------------
	//assign lut_outa = shift_out2a ^ key_ina ^ lut_rol2a ^ (lut_rol1a & lut_rol8a) ^ (lut_rol1a & lut_rol8b);
	always @(posedge clk)
	begin
		intreg <= shift_out2 ^ lut_rol2 ^ (lut_rol1 & lut_rol8);
	end
	assign out = key_in ^ (lut_rol1_shifted & lut_rol8_ext) ^ intreg;

endmodule //lut_datapath