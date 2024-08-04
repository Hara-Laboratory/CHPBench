#include "KS1.hpp"

#include <ap_int.h>
#include <stdio.h>
#include <iostream>

ap_uint<64> top(ap_uint<256> Din){
	p_keysch10 KS1;
	int state=2;
	int count=1;


	top_label0:while(count<=128){

		Din.range(254,0)=Din.range(255,1);
		KS1.data_in=Din.bit(count);
		KS1.data_rdy=state;
		KS1.counter=0;
		KS1.update();
		count++;

	}

	return KS1.key_out;

}
