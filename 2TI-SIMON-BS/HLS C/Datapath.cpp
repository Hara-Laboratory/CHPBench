#include "E:\vitis_library\TI_Simon_Core.hpp"
#include <ap_int.h>

//datapath.cpp
void Lut_Datapath::tick_dpl() {
    static ap_uint<1> intreg;
            intreg = shift_out2 ^ lut_rol2 ^ (lut_rol1 & lut_rol8);

        lut_out = key_in ^ (lut_rol1_shifted & lut_rol8_ext) ^ intreg;
}

Datapath_Share::Datapath_Share() {
    reset();
}

void Datapath_Share::reset() {
    shifter1 = 0;
    shifter2 = 0;
}

void Datapath_Share::tick_dps() {
	lut_datapath.shift_out2=shift_out2;
	lut_datapath.key_in=key_in;
	lut_datapath.lut_rol1=lut_rol1;
	lut_datapath.lut_rol2=lut_rol2;
	lut_datapath.lut_rol8=lut_rol8;
	lut_datapath.lut_rol1_shifted=lut_rol1_shifted;
	lut_datapath.lut_rol8_ext=lut_rol8_shifted_ext;
    update_internal_state();
    lut_datapath.tick_dpl();
    cipher_out = lut_datapath.lut_out;
}

void Datapath_Share::update_internal_state() {
	if (shifter_enable1) {
	        shifter1.range(53,0) =  shifter1.range(54, 1);
	        shifter1.bit(54)=shift_in1;
	    }

	    shift_out1 = shifter1.bit(0);

	    if (shifter_enable2) {
	        shifter2.range(62,0) = shifter2.range(63, 1);
	        shifter2.bit(63) = shift_in2;
	    }

	    shift_out2 = shifter2.bit(0);

	    ff63=ff_input;
        if (shifter_enable1) {
        	temp1=fifo_ff62;
            fifo_ff62 = fifo_ff_input;
            temp2=fifo_ff61;
            fifo_ff61 = temp1;
            temp1=fifo_ff60;
            fifo_ff60 = temp2;
            temp2=fifo_ff59;
            fifo_ff59 = temp1;
            temp1=fifo_ff58;
            fifo_ff58 = temp2;
            temp2=fifo_ff57;
            fifo_ff57 = temp1;
            temp1=fifo_ff56;
            fifo_ff56 = temp2;
            fifo_ff55 = temp1;
        }

        if (shifter_enable1) {
        	temp1=fifo_ff62;
			lut_ff62 = lut_ff_input;
			temp2=lut_ff61;
			lut_ff61 = temp1;
			temp1=lut_ff60;
			lut_ff60 = temp2;
			temp2=lut_ff59;
			lut_ff59 = temp1;
			temp1=lut_ff58;
			lut_ff58 = temp2;
			temp2=lut_ff57;
			lut_ff57 = temp1;
			temp1=lut_ff56;
			lut_ff56 = temp2;
			lut_ff55 = temp1;
        }

        shift_in2 = shift_out1;

        if (s1 == 0) {
            shift_in1 = lut_ff55;
        } else {
            shift_in1 = fifo_ff55;
        }

        if (s3 == 0) {
            ff_input = data_in;
        } else if (s3 == 1) {
            ff_input = shift_out1;
        } else if (s3 == 2) {
            ff_input = lut_out;
        } else {
            ff_input = ff_input;
        }

        if (s2 == 0) {
            fifo_ff_input = ff63;
        } else {
            fifo_ff_input = lut_out;
        }

        if (s2 == 1) {
            lut_ff_input = ff63;
        } else {
            lut_ff_input = lut_out;
        }

        lut_rol1 = ff63;

        if (s2 == 0) {
            lut_rol1_shifted = fifo_ff62;
        } else {
            lut_rol1_shifted = lut_ff62;
        }

        if (s2 == 0) {
            lut_rol8_shifted_out = fifo_ff55;
        } else {
            lut_rol8_shifted_out = lut_ff55;
        }

        if (s2 == 0) {
            lut_rol2 = fifo_ff62;
        } else {
            lut_rol2 = lut_ff62;
        }

        if (s2 == 0) {
            lut_rol8 = fifo_ff56;
        } else {
            lut_rol8 = lut_ff56;
        }


}

Datapath_Simon2Share::Datapath_Simon2Share() {
    reset();
}

//void Datapath_Simon2Share::wire(ap_uint){
//
//}

void Datapath_Simon2Share::reset() {
    s1 = 0;
    s2 = 0;
    s3 = 0;
}

void Datapath_Simon2Share::tick_dp() {
	dp_a.data_in=data_ina;
	dp_a.key_in=key_ina;
	dp_b.data_in=data_inb;
	dp_b.key_in=key_inb;
	dp_a.lut_rol8_shifted_ext=dp_b.lut_rol8_shifted_out;
	dp_b.lut_rol8_shifted_ext=dp_a.lut_rol8_shifted_out;
	dp_a.s1=s1;
	dp_b.s1=s1;
	dp_a.s2=s2;
	dp_b.s2=s2;
	dp_a.s3=s3;
	dp_b.s3=s3;
    update_selection_mux();
    update_shifter_enables();

    dp_a.tick_dps();
    dp_b.tick_dps();

    cipher_outa = dp_a.cipher_out;
    cipher_outb = dp_b.cipher_out;
}

void Datapath_Simon2Share::update_selection_mux() {
     if ((round_counter_0 == 0 && (bit_counter < 8 || flag == 0)) || (round_counter_0 == 1 && (bit_counter > 7 && flag)) || (data_rdy == 1)) {
            s1 = 1;
        } else {
            s1 = 0;
        }

        if (round_counter_0 == 0) {
            s2 = 0;
        } else {
            s2 = 1;
        }

        if (data_rdy == 1) {
            s3 = 0;
        } else if (bit_counter == 63) {
            s3 = 2;
        } else {
            if (flag == 0) {
                s3 = 1;
            } else {
                s3 = s3;
            }
        }
}

void Datapath_Simon2Share::update_shifter_enables() {
      if (data_rdy == 1 || (data_rdy == 3 && bit_counter != 63)) {
            dp_a.shifter_enable1 = 1;
            dp_a.shifter_enable2 = 1;
            dp_b.shifter_enable1 = 1;
            dp_b.shifter_enable2 = 1;
        } else {
            dp_a.shifter_enable1 = 0;
            dp_a.shifter_enable2 = 0;
            dp_b.shifter_enable1 = 0;
            dp_b.shifter_enable2 = 0;
        }
}
