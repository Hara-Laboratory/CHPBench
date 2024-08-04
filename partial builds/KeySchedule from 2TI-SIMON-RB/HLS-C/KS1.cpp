#include "KS1.hpp"
#include <stdio.h>
#include <iostream>

void p_keysch10::update(/*ap_uint<8> counter, ap_uint<1> data_in, ap_uint<2> data_rdy*/) {
//        		ap_uint<128> temp;
				ap_uint<64> temp2;
                if (data_rdy == 2) {
//                	temp.bit(127)=data_in;
//					temp.range(126,63)=KX;
//					temp.range(62,0)=KY.range(63,1);
//					KX = temp.range(127, 64);
//					KY = temp.range(63, 0);
//
					KX = (data_in,KX.range(63,1));
					KY = (KX.bit(0),KY.range(63,61));
                }
                else if (data_rdy == 3) {
                    if (counter.bit(0) == 1) {
                    	temp2=KX;
                        KX = c ^ Z.bit(counter.range(7, 1)) ^ KY ^ (KX.range(2, 0), KX.range(63, 3)) ^ (KX.range(3, 0), KX.range(63, 4));
                        KY = temp2;
                    }
                }

            key_out=KY;
        }
