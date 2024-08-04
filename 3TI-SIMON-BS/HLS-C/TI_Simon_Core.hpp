#ifndef TI_SIMON_CORE_HPP
#define TI_SIMON_CORE_HPP

#include <ap_int.h>
#include "datapath.hpp"
//#include "key_schedule1.hpp"
//#include "key_schedule2.hpp"



class Key_Schedule3 {
public:
	ap_uint<1> temp1,temp2;
    // Inputs and outputs
    ap_uint<1> clk;
    ap_uint<1> data_in;
    ap_uint<1> flag;
    ap_uint<1> s2;
    ap_uint<2> s1, s3;
    ap_uint<1> shifter_enable1, shifter_enable2;
    ap_uint<1> lut_ff_enable, fifo_ff_enable;

    // Outputs
    ap_uint<1> key_out;

    // Internal variables
    ap_uint<60> shifter1;
    ap_uint<64> shifter2;
    ap_uint<1> shift_in1, shift_in2;
    ap_uint<1> shift_out1, shift_out2;
    ap_uint<1> lut_out;
    ap_uint<1> lut_in3;
    ap_uint<1> fifo_ff0, fifo_ff1, fifo_ff2, fifo_ff3;
    ap_uint<1> lut_ff0, lut_ff1, lut_ff2, lut_ff3;

    void tick_k3();
};

class Key_Schedule2 {
public:
	ap_uint<1> temp1,temp2;
    // Inputs and outputs
    ap_uint<1> clk;
    ap_uint<1> data_in;
    ap_uint<7> bit_counter;
    ap_uint<1> flag;
    ap_uint<1> s2;
    ap_uint<2> s1, s3;
    ap_uint<1> shifter_enable1, shifter_enable2;
    ap_uint<1> lut_ff_enable, fifo_ff_enable;

    // Outputs
    ap_uint<1> key_out;

    // Internal variables
    ap_uint<60> shifter1;
    ap_uint<64> shifter2;
    ap_uint<1> shift_in1, shift_in2;
    ap_uint<1> shift_out1, shift_out2;
    ap_uint<1> lut_out;
    ap_uint<1> lut_in3;
    ap_uint<1> c;
    ap_uint<1> fifo_ff0, fifo_ff1, fifo_ff2, fifo_ff3;
    ap_uint<1> lut_ff0, lut_ff1, lut_ff2, lut_ff3;

    void tick_k2();
};

class Key_Schedule1 {
public:
	ap_uint<1> temp1,temp2;
    // Inputs
    ap_uint<1> clk;
    ap_uint<1> data_in;
    ap_uint<2> data_rdy;
    ap_uint<7> bit_counter;
    ap_uint<7> round_counter=0;
    ap_uint<1> flag,round_counter_out;

    // Outputs
    ap_uint<1> key_out;
    ap_uint<1> s2;
    ap_uint<2> s1, s3;
    ap_uint<1> shifter_enable1, shifter_enable2;
    ap_uint<1> lut_ff_enable, fifo_ff_enable;


    ap_uint<68> Z;

    // Internal variables
    ap_uint<60> shifter1;
    ap_uint<64> shifter2;
    ap_uint<1> shift_in1, shift_in2;
    ap_uint<1> shift_out1, shift_out2;
    ap_uint<1> lut_out;
    ap_uint<1> lut_in3;
    ap_uint<1> z_value;
    ap_uint<1> fifo_ff0, fifo_ff1, fifo_ff2, fifo_ff3;
    ap_uint<1> lut_ff0, lut_ff1, lut_ff2, lut_ff3;


    void tick_k1();
};


class TI_Simon_Core {
public:
    ap_uint<1> data_ina, data_inb, data_inc;
    ap_uint<2> data_rdy;
    ap_uint<1> cipher_outa, cipher_outb, cipher_outc;
    ap_uint<7> round_counter, bit_counter;//also output
    ap_uint<1> Done, Trig;

    void reset();

    void tick();

private:
    ap_uint<1> flag;

    datapath dp;
    Key_Schedule1 k1;
    Key_Schedule2 k2;
    Key_Schedule3 k3;

};

#endif // TI_SIMON_CORE_HPP
