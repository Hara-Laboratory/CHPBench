#include "TI_Simon_Core.hpp"
#include <ap_int.h>
//key_schedule2.cpp
void Key_Schedule2::tick_k2() {
	temp1=0;
	temp2=0;
    if (shifter_enable1) {
        shifter1.range(58,0) =  shifter1.range(59, 1);
        shifter1.bit(59)=shift_in1;
    }

    shift_out1 = shifter1.bit(0);

    if (shifter_enable2) {
        shifter2.range(62,0) = shifter2.range(63, 1);
        shifter2.bit(63) = shift_in2;
    }

    shift_out2 = shifter2.bit(0);

    if (fifo_ff_enable) {

        	   temp1=fifo_ff3;
               fifo_ff3 = shift_out1;
               temp2=fifo_ff2;
               fifo_ff2 = temp1;
               temp1=fifo_ff1;
               fifo_ff1 = temp2;
               fifo_ff0 = temp1;
           }

           if (lut_ff_enable) {
        	   temp1=lut_ff3;
               lut_ff3 = lut_out;
               temp2=lut_ff2;
               lut_ff2 = temp1;
               temp1=lut_ff1;
               lut_ff1 = temp2;
               lut_ff0 = temp1;
           }

    if (s3 == 1) {
        shift_in2 = fifo_ff0;
    } else if (s3 == 2) {
        shift_in2 = fifo_ff0;
    } else if (s3 == 3) {
        shift_in2 = lut_ff0;
    } else {
        shift_in2 = 0;//1'bx
    }

    if (s2 == 0) {
        lut_in3 = fifo_ff3;
    } else {
        lut_in3 = lut_ff3;
    }

    if (s1 == 0) {
        shift_in1 = fifo_ff0;
    } else if (s1 == 1) {
        shift_in1 = data_in;
    } else if (s1 == 2) {
        shift_in1 = lut_out;
    } else if (s1 == 3) {
        shift_in1 = lut_ff0;
    } else {
        shift_in1 = 0;//1'bx
    }

    if ((flag && bit_counter == 0) || bit_counter == 1) {
        c = 0;
    } else {
        c = 1;
    }

    lut_out = shift_out2 ^ lut_in3 ^ shift_out1 ^ c;
    key_out = shift_out2;
}
