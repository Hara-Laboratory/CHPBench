#include "TI_Simon_Core.hpp"

void TI_Simon_Core::reset() {
    bit_counter = 0;
    round_counter = 0;
    flag = 0;
    Done = 0;
    Trig = 0;
}

void TI_Simon_Core::tick() {
	//update internal variables
	if(round_counter==0 && bit_counter == 1){
		Trig =1;
	}else{
		Trig =0;
	}
	if(data_rdy == 3 && round_counter == 67 && bit_counter ==62)
		Done=1;
	else
		Done=0;




	//connecting dp
	//input
	dp.data_ina=data_ina;
	dp.data_inb=data_inb;
	dp.data_inc=data_inc;
	dp.data_rdy=data_rdy;
	dp.round_counter=k1.round_counter_out;
	dp.round_num=k1.round_counter;
	dp.key_ina=k1.key_out;
	dp.key_inb=k2.key_out;
	dp.key_inc=k3.key_out;
	//output
	bit_counter=dp.bit_counter;

	//connecting k1
	k1.data_in=data_ina;
	k1.data_rdy=data_rdy;
	k1.bit_counter=dp.bit_counter;
	round_counter=k1.round_counter;

	//connecting k2
	k2.data_in=data_inb;
	k2.bit_counter=dp.bit_counter;
	k2.s2=k1.s2;
	k2.s1=k1.s1;
	k2.s3=k1.s3;
	k2.shifter_enable1=k1.shifter_enable1;
	k2.shifter_enable2=k1.shifter_enable2;
	k2.lut_ff_enable=k1.lut_ff_enable;
	k2.fifo_ff_enable-k1.fifo_ff_enable;

	//connecting k3
	k3.data_in=data_inc;
	k3.s2=k1.s2;
	k3.s1=k1.s1;
	k3.s3=k1.s3;
	k3.shifter_enable1=k1.shifter_enable1;
	k3.shifter_enable2=k1.shifter_enable2;
	k3.lut_ff_enable=k1.lut_ff_enable;
	k3.fifo_ff_enable-k1.fifo_ff_enable;





    k1.tick_k1();
    k2.tick_k2();
    k3.tick_k3();
    dp.tick_dp();

    cipher_outa=dp.couta;
	cipher_outb=dp.coutb;
	cipher_outc=dp.coutc;

}
