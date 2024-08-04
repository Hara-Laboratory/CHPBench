//top with reset temp
#include <ap_int.h>
#include "TI_Simon_Core.hpp"
#include <iostream>
#include <cstdint>




 ap_uint<128> TI_Simon_TopModule(ap_uint<768> Din) {

	 //output
	 ap_uint<128> Dout;

    ap_uint<256> share_a = 0, share_b = 0, share_c = 0;
    ap_uint<2> state = 0;
    ap_uint<64> cout_a = 0, cout_b = 0, cout_c = 0;
    ap_uint<7> round_counter;
    ap_uint<1> Done;
    ap_uint<1> cipher_outa, cipher_outb,cipher_outc;
    int cycle =0;
    share_a = 0;
	share_b = 0;
	share_c = 0;
	state = 0;
    // TI_Simon_Core submodule
    TI_Simon_Core my_simon_core;
    my_simon_core.reset();
    ap_uint<14> count=0;


    share_a = Din.range(767, 512);
	share_b = Din.range(511, 256);
	share_c = Din.range(255, 0);
	state = 2;
	count = 1;

		TI_Simon_TopModule_label3:while(!Done)
    	{

			cycle++;
//		    std::cout << "cycle: " << cycle << std::endl;

			if (count==128 && state == 2) state = 1;
			else if (count ==256 && state==1) state=0;
			else if (count ==261) state = 3;
			if (Done) state = 0;
    	    my_simon_core.data_rdy=state;

    	    // Setting inputs to my_simon_core
    	    share_a.range(254,0) = share_a.range(255, 1);
			share_a.bit(255)=0;
			share_b.range(254,0) = share_b.range(255, 1);
			share_b.bit(255)=0;
			share_c.range(254,0) = share_c.range(255, 1);
			share_c.bit(255)=0;
    	    my_simon_core.data_ina = share_a.bit(0);
			my_simon_core.data_inb = share_b.bit(0);
			my_simon_core.data_inc = share_c.bit(0);

    	    my_simon_core.tick();
    	    if(count<267)count++;
    	    if(round_counter>64) {
    	 	cipher_outa = my_simon_core.cipher_outa;
    	    cipher_outb = my_simon_core.cipher_outb;
    	    cipher_outc = my_simon_core.cipher_outc;
    	    }
    	    round_counter = my_simon_core.round_counter;
    	    Done = my_simon_core.Done;

    	    cout_a.range(62,0)=cout_a.range(63,1);
			cout_a.bit(63) = cipher_outa;
    	    cout_b.range(62,0)=cout_b.range(63,1);
			cout_b.bit(63) = cipher_outb;
    	    cout_c.range(62,0)=cout_c.range(63,1);
			cout_c.bit(63) = cipher_outc;

    	    if(state==3)count=0;


    	    //debug
//    	    if(cycle==125){
//    	        std::cout << "128 passed"<< std::endl;}
//    	    if(cycle==253){
//    	        	        std::cout << "256 passed"<< std::endl;}
//    	    if(cycle==4490){
//    	        	        std::cout << "4490 passed"<< std::endl;}
//    	    if(cycle==4600){
//    	        	        std::cout << "4600 passed"<< std::endl;}

    	}



    Dout = cout_a ^ cout_b ^ cout_c;
    return Dout;
}
