//top with reset temp
#include <ap_int.h>
#include "E:\vitis_library\TI_Simon_Core.hpp"
//#include "datapath.hpp"
//#include "key_schedule1.hpp"
//#include "key_schedule2.hpp"




 ap_uint<128> TI_Simon_TopModule(ap_uint<768> Din) {

	 //output
	 ap_uint<128> Dout;

    ap_uint<256> share_a = 0, share_b = 0, share_c = 0;
    ap_uint<2> state = 0;
    ap_uint<64> cout_La = 0, cout_Lb = 0, cout_Ra = 0, cout_Rb = 0;
    ap_uint<7> round_counter;
    ap_uint<1> Done;
    ap_uint<1> cipher_outa, cipher_outb;

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

		TI_Simon_TopModule_label3:while(Done!=1)
    	{




			if (count == 128 && state == 2) state = 1;
			else if (count == 256 && state == 1) state = 3;
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
			my_simon_core.data_inb = share_b.bit(0) ^ share_c.bit(0);

    	    my_simon_core.tick();
    	    if(count<257)count++;
    	 	cipher_outa = my_simon_core.cipher_outa;
    	    cipher_outb = my_simon_core.cipher_outb;
    	    round_counter = my_simon_core.round_counter;
    	    Done = my_simon_core.Done;
    	    if (round_counter ==  66) {
    	    	cout_Ra.range(62,0)=cout_Ra.range(63,1);
				cout_Ra.bit(63) = cipher_outa;
    	    	cout_Rb.range(62,0)=cout_Rb.range(63,1);
				cout_Rb.bit(63) = cipher_outb;
    	    }
    	    	else if (round_counter ==  67) {
    	    		cout_La.range(62,0)=cout_La.range(63,1);
    	    		cout_La.bit(63) = cipher_outa;
    	    		cout_Lb.range(62,0)=cout_Lb.range(63,1);
    	    		cout_Lb.bit(63) = cipher_outb;
    	    }



    	}



    Dout = (cout_La, cout_Ra) ^ (cout_Lb, cout_Rb);
    return Dout;
}
