#include "E:\vitis_library\TI_Simon_Core.hpp"
#include <ap_int.h>

//ti_simon_core.cpp
void TI_Simon_Core::reset() {
	simon_key_exp_1.fifo_ff2=0;
	simon_key_exp_1.fifo_ff1=0;
	simon_key_exp_1.fifo_ff3=0;
	simon_key_exp_1.fifo_ff0=0;
    bit_counter = 0;
    round_counter = 0;
    flag = 0;
    Done = 0;
    Trig = 0;
    simon_datapath.reset();

}

void TI_Simon_Core::tick() {
	update_counters();
	    update_done_trig();

	//connecting datapath
	simon_datapath.data_ina=data_ina;
	simon_datapath.data_inb=data_inb;
	simon_datapath.key_ina=simon_key_exp_1.key_out;
	simon_datapath.key_inb=simon_key_exp_2.key_out;
	simon_datapath.data_rdy=data_rdy;
	simon_datapath.flag=flag;
	simon_datapath.bit_counter=bit_counter;
	simon_datapath.round_counter_0=round_counter.bit(0);
	//output
	cipher_outa=simon_datapath.cipher_outa;
	cipher_outb=simon_datapath.cipher_outb;

	//connecting key_schedule_1
	simon_key_exp_1.data_in=data_ina;
	simon_key_exp_1.data_rdy=data_rdy;
	simon_key_exp_1.bit_counter=bit_counter;
	simon_key_exp_1.round_counter=round_counter;
	simon_key_exp_1.flag=flag;
	//output





	//connecting key_schedule_2
	simon_key_exp_2.s2=simon_key_exp_1.s2;
	simon_key_exp_2.s1=simon_key_exp_1.s1;
	simon_key_exp_2.s3=simon_key_exp_1.s3;
	simon_key_exp_2.data_in=data_inb;
	simon_key_exp_2.bit_counter=bit_counter;
	simon_key_exp_2.shifter_enable1=simon_key_exp_1.shifter_enable1;
	simon_key_exp_2.shifter_enable2=simon_key_exp_1.shifter_enable2;
	simon_key_exp_2.lut_ff_enable=simon_key_exp_1.lut_ff_enable;
	simon_key_exp_2.fifo_ff_enable=simon_key_exp_1.fifo_ff_enable;




    simon_datapath.tick_dp();
    simon_key_exp_1.tick_k1();
    simon_key_exp_2.tick_k2();

}

void TI_Simon_Core::update_counters() {


    if (data_rdy == 0) {
        flag = 0;
    } else if (data_rdy == 3) {
        if (bit_counter == 63) {
            flag = ~flag;
        } else {
            flag = 1;
        }
    }

    if (data_rdy == 0) {
            bit_counter = 0;
        } else if (flag) {
                bit_counter++;
        }

    if (data_rdy == 0) {
        round_counter = 0;
    } else if (data_rdy == 3 && bit_counter == 0) {
        round_counter = round_counter + 1;
    }
}

void TI_Simon_Core::update_done_trig() {
    if (round_counter == 0 && bit_counter == 1) {
            Trig = 1;
    } else {
        Trig = 0;
    }

    if (data_rdy == 3 && round_counter == 67 && bit_counter == 62) {
        Done = 1;
    } else {
        Done = 0;
    }
}



