#ifndef DATAPATH_HPP
#define DATAPATH_HPP

#include <ap_int.h>

class datapath {
public:
// Module Interface Variables
ap_uint<1> data_ina, data_inb, data_inc;
ap_uint<1> key_ina, key_inb, key_inc;
ap_uint<2> data_rdy;
ap_uint<1> round_counter;
ap_uint<7> round_num;
ap_uint<1> couta=0, coutb=0, coutc=0;
ap_uint<7> bit_counter=0;

// Internal Registers and Wires
ap_uint<56> shifter1a, shifter1b, shifter1c;
ap_uint<64> shifter2a, shifter2b, shifter2c;
ap_uint<1> shift_in1a, shift_in1b, shift_in1c;
ap_uint<1> shift_in2a, shift_in2b, shift_in2c;
ap_uint<1> shift_out1a, shift_out1b, shift_out1c;
ap_uint<1> shift_out2a, shift_out2b, shift_out2c;
ap_uint<1> shifter_enable1a, shifter_enable1b, shifter_enable1c;
ap_uint<1> shifter_enable2a, shifter_enable2b, shifter_enable2c;

ap_uint<1> fifo_ff63a, fifo_ff62a, fifo_ff61a, fifo_ff60a, fifo_ff59a, fifo_ff58a, fifo_ff57a, fifo_ff56a;
ap_uint<1> lut_ff63a, lut_ff62a, lut_ff61a, lut_ff60a, lut_ff59a, lut_ff58a, lut_ff57a, lut_ff56a;

ap_uint<1> fifo_ff63b, fifo_ff62b, fifo_ff61b, fifo_ff60b, fifo_ff59b, fifo_ff58b, fifo_ff57b, fifo_ff56b;
ap_uint<1> lut_ff63b, lut_ff62b, lut_ff61b, lut_ff60b, lut_ff59b, lut_ff58b, lut_ff57b, lut_ff56b;

ap_uint<1> fifo_ff63c, fifo_ff62c, fifo_ff61c, fifo_ff60c, fifo_ff59c, fifo_ff58c, fifo_ff57c, fifo_ff56c;
ap_uint<1> lut_ff63c, lut_ff62c, lut_ff61c, lut_ff60c, lut_ff59c, lut_ff58c, lut_ff57c, lut_ff56c;

ap_uint<1> lut_ff_inputa, fifo_ff_inputa;
ap_uint<1> lut_rol1a, lut_rol2a, lut_rol8a;

ap_uint<1> lut_ff_inputb, fifo_ff_inputb;
ap_uint<1> lut_rol1b, lut_rol2b, lut_rol8b;

ap_uint<1> lut_ff_inputc, fifo_ff_inputc;
ap_uint<1> lut_rol1c, lut_rol2c, lut_rol8c;

ap_uint<1> s1, s4, s5, s6, s7;
ap_uint<2> s3;

// LUT Outputs
ap_uint<1> lut_outa, lut_outb, lut_outc;

ap_uint<1> out_res_1,out_res_2,out_res_3;

void tick_dp();
};

ap_uint<1> lut_dp(ap_uint<1> in1, ap_uint<1> in2, ap_uint<1> in3, ap_uint<1> in_4, ap_uint<1> in_5, ap_uint<1> in_6_, ap_uint<1> in_7_, ap_uint<1> in_8, ap_uint<1> in_9) ;



#endif // DATAPATH_HPP
