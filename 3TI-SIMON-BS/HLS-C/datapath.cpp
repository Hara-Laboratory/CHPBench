
#include "datapath.hpp"

ap_uint<1> lut_dp(ap_uint<1> in1, ap_uint<1> in2, ap_uint<1> in3, ap_uint<1> in_4, ap_uint<1> in_5, ap_uint<1> in_6_, ap_uint<1> in_7_, ap_uint<1> in_8, ap_uint<1> in_9) {
    ap_uint<1> out = in1 ^ in2 ^ in3 ^ (in_4 & in_5) ^ (in_6_ & in_7_) ^ (in_8 & in_9);
    return out;
}

void datapath::tick_dp()
{
	// Shift Register1 Logic
	if (shifter_enable1a) {
	    shifter1a = (shift_in1a, shifter1a.range(55, 1));
	}
	if (shifter_enable1b) {
	    shifter1b = (shift_in1b, shifter1b.range(55, 1));
	}
	if (shifter_enable1c) {
	    shifter1c = (shift_in1c, shifter1c.range(55, 1));
	}

	// Output of Shift Register1
	shift_out1a = shifter1a.bit(0);
	shift_out1b = shifter1b.bit(0);
	shift_out1c = shifter1c.bit(0);

	// Shift Register2 FIFO 64x1 Logic
	if (shifter_enable2a) {
	    shifter2a = (shift_in2a, shifter2a.range(63, 1));
	}
	if (shifter_enable2b) {
	    shifter2b = (shift_in2b, shifter2b.range(63, 1));
	}
	if (shifter_enable2c) {
	    shifter2c = (shift_in2c, shifter2c.range(63, 1));
	}

	// Output of Shift Register2
	shift_out2a = shifter2a.bit(0);
	shift_out2b = shifter2b.bit(0);
	shift_out2c = shifter2c.bit(0);

	// FIFO 8 Flip-Flops Logic for Shift Register Up (SRU)
	if (shifter_enable1a) {
	    fifo_ff56a = fifo_ff57a;
	    fifo_ff57a = fifo_ff58a;
	    fifo_ff58a = fifo_ff59a;
	    fifo_ff59a = fifo_ff60a;
	    fifo_ff60a = fifo_ff61a;
	    fifo_ff61a = fifo_ff62a;
	    fifo_ff62a = fifo_ff63a;
	    fifo_ff63a = fifo_ff_inputa;
	}
	if (shifter_enable1b) {
		fifo_ff56b = fifo_ff57b;
		fifo_ff57b = fifo_ff58b;
		fifo_ff58b = fifo_ff59b;
		fifo_ff59b = fifo_ff60b;
		fifo_ff60b = fifo_ff61b;
		fifo_ff61b = fifo_ff62b;
		fifo_ff62b = fifo_ff63b;
		fifo_ff63b = fifo_ff_inputb;
		}
	if (shifter_enable1c) {
		fifo_ff56c = fifo_ff57c;
		fifo_ff57c = fifo_ff58c;
		fifo_ff58c = fifo_ff59c;
		fifo_ff59c = fifo_ff60c;
		fifo_ff60c = fifo_ff61c;
		fifo_ff61c = fifo_ff62c;
		fifo_ff62c = fifo_ff63c;
		fifo_ff63c = fifo_ff_inputc;
			}
	// FIFO 8 Flip-Flops Logic for Shift Register Down (SRD)
	lut_ff56a = lut_ff57a;
	lut_ff57a = lut_ff58a;
	lut_ff58a = lut_ff59a;
	lut_ff59a = lut_ff60a;
	lut_ff60a = lut_ff61a;
	lut_ff61a = lut_ff62a;
	lut_ff62a = lut_ff63a;
	lut_ff63a = lut_ff_inputa;

	lut_ff56b = lut_ff57b;
	lut_ff57b = lut_ff58b;
	lut_ff58b = lut_ff59b;
	lut_ff59b = lut_ff60b;
	lut_ff60b = lut_ff61b;
	lut_ff61b = lut_ff62b;
	lut_ff62b = lut_ff63b;
	lut_ff63b = lut_ff_inputb;

	lut_ff56c = lut_ff57c;
	lut_ff57c = lut_ff58c;
	lut_ff58c = lut_ff59c;
	lut_ff59c = lut_ff60c;
	lut_ff60c = lut_ff61c;
	lut_ff61c = lut_ff62c;
	lut_ff62c = lut_ff63c;
	lut_ff63c = lut_ff_inputc;

	// FIFO 64x1 Input MUX
	shift_in2a = shift_out1a;
	shift_in2b = shift_out1b;
	shift_in2c = shift_out1c;

	// FIFO 56x1 Input MUX
	if (s1 == 0) {
	    shift_in1a = lut_ff56a;
	    shift_in1b = lut_ff56b;
	    shift_in1c = lut_ff56c;
	} else {
	    shift_in1a = fifo_ff56a;
	    shift_in1b = fifo_ff56b;
	    shift_in1c = fifo_ff56c;
	}

	// FIFO FF Input MUX
	if (s3 == 0) {
	    fifo_ff_inputa = data_ina;
	    fifo_ff_inputb = data_inb;
	    fifo_ff_inputc = data_inc;
	} else if (s3 == 1) {
	    fifo_ff_inputa = shift_out1a;
	    fifo_ff_inputb = shift_out1b;
	    fifo_ff_inputc = shift_out1c;
	} else if (s3 == 2) {
	    fifo_ff_inputa = lut_outa;
	    fifo_ff_inputb = lut_outb;
	    fifo_ff_inputc = lut_outc;
	}

	// LUT FF Input MUX
	if (s5 == 0) {
	    lut_ff_inputa = shift_out1a;
	    lut_ff_inputb = shift_out1b;
	    lut_ff_inputc = shift_out1c;
	} else {
	    lut_ff_inputa = lut_outa;
	    lut_ff_inputb = lut_outb;
	    lut_ff_inputc = lut_outc;
	}

	// LUT Input MUX
	if (s7 == 0) {
	    lut_rol1a = fifo_ff63a;
	    lut_rol1b = fifo_ff63b;
	    lut_rol1c = fifo_ff63c;
	} else {
	    lut_rol1a = lut_ff63a;
	    lut_rol1b = lut_ff63b;
	    lut_rol1c = lut_ff63c;
	}

	if (s4 == 0) {
	    lut_rol2a = fifo_ff62a;
	    lut_rol2b = fifo_ff62b;
	    lut_rol2c = fifo_ff62c;
	} else {
	    lut_rol2a = lut_ff62a;
	    lut_rol2b = lut_ff62b;
	    lut_rol2c = lut_ff62c;
	}

	if (s6 == 0) {
	    lut_rol8a = fifo_ff56a;
	    lut_rol8b = fifo_ff56b;
	    lut_rol8c = fifo_ff56c;
	} else {
	    lut_rol8a = lut_ff56a;
	    lut_rol8b = lut_ff56b;
	    lut_rol8c = lut_ff56c;
	}

	// Selection MUX
	// For the first 8 bits of each even round OR for all the bits after the first 8 bits in odd rounds OR loading the plaintext
	if ((round_counter == 0 && bit_counter < 8) || (round_counter == 1 && bit_counter > 7) || (data_rdy == 1)) {
	    s1 = 1;
	} else {
	    s1 = 0;
	}

	// Loading plaintext
	if (data_rdy == 1) {
	    s3 = 0;
	} else if (round_counter == 0) { // Even rounds
	    s3 = 1;
	} else if (round_counter == 1) { // Odd rounds
	    s3 = 2;
	}
	// Even and odd round logic
	if (round_counter == 0) { // Even rounds
	    s6 = 0;
	} else {
	    s6 = 1;
	}

	s4 = s6;
	s7 = s6;
	s5 = ~s6;


	// SHIFTER ENABLES
	if (data_rdy == 1 || data_rdy == 3) {
	    shifter_enable1a = 1;
	    shifter_enable2a = 1;

	    shifter_enable1b = 1;
		shifter_enable2b = 1;

		shifter_enable1c = 1;
		shifter_enable2c = 1;
	} else {
	    shifter_enable1a = 0;
	    shifter_enable2a = 0;

	    shifter_enable1b = 0;
	    shifter_enable2b = 0;

	    shifter_enable1c = 0;
	    shifter_enable2c = 0;
	}

	// Bit Counter Logic
	if (data_rdy == 0) {
	    bit_counter = 0;
	} else if (data_rdy == 3) {
	    if (bit_counter == 64) {
	        bit_counter = 0;
	    } else {
	        bit_counter = bit_counter + 1;
	    }
	}

	lut_outa = lut_dp(shift_out2b,key_inb, lut_rol2b, lut_rol1b, lut_rol8b, lut_rol1b, lut_rol8c, lut_rol1c,lut_rol8b);
	lut_outb = lut_dp(shift_out2c,key_inc, lut_rol2c, lut_rol1c, lut_rol8c, lut_rol1a, lut_rol8c, lut_rol1c,lut_rol8a);
	lut_outc = lut_dp(shift_out2a,key_ina, lut_rol2a, lut_rol1a, lut_rol8a, lut_rol1a, lut_rol8b, lut_rol1b,lut_rol8a);

	if(round_num >= 66){
		out_res_1=lut_outa;
		out_res_2=lut_outb;
		out_res_3=lut_outc;
	}else{
		out_res_1=0;
		out_res_2=0;
		out_res_3=0;
	}

	couta = out_res_1;
	coutb = out_res_2;
	coutc = out_res_3;
}
