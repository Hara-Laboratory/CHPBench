#include "TI_Simon_Core.hpp"
#include <ap_int.h>
//key_schedule1.cpp

const ap_uint<34> upper_bits = 0x2BDC0D262;
   const ap_uint<32> lower_bits = 0x847E5B3A;
   ap_uint<66> Z = (upper_bits, lower_bits);
void Key_Schedule1::tick_k1() {

	temp1=0;
	temp2=0;
	round_counter_out=round_counter.bit(0);
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

       if (data_rdy == 2) {
               s3 = 1;
           } else if (data_rdy == 3 && (round_counter < 1 || bit_counter > 3 )) {
               s3 = 2;
           } else if (data_rdy == 3 && bit_counter < 4 && round_counter > 0) {
               s3 = 3;
           } else {
               s3 = 0;
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

       if ((flag && bit_counter == 0) && round_counter != 0) {
               s2 = 1;
           } else {
               s2 = 0;
           }

       if (data_rdy == 2) {
               s1 = 1;
           } else if (data_rdy == 3 && bit_counter < 4 && round_counter == 0) {
               s1 = 0;
           } else if (data_rdy == 3 &&  bit_counter < 4 && round_counter > 0) {
               s1 = 3;
           } else {
               s1 = 2;
           }
       if(data_rdy==3 && (flag && bit_counter<4))
       			lut_ff_enable = 1;
       		else
       			lut_ff_enable = 0;

       if (data_rdy == 2 || data_rdy==3) {
               fifo_ff_enable = 1;
               shifter_enable1 = 1;
               shifter_enable2 = 1;
           } else {
               fifo_ff_enable = 0;
               shifter_enable1 = 0;
               shifter_enable2 = 0;
           }

       if (data_rdy==3 && bit_counter == 0) round_counter++;

	   if (bit_counter == 0) {
		   z_value = Z.bit(round_counter);
	   } else {
		   z_value = 0;
	   }

	   lut_out = shift_out2 ^ lut_in3 ^ shift_out1 ^ z_value;
	   key_out = shift_out2;
}
