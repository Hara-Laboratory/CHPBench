#include <ap_int.h>
#include "C:\Users\12748\OneDrive\titech\vitis_projects\ti2_simon_rb\top.hpp"
#include <stdio.h>
#include <iostream>

    void and4(ap_uint<4> a1, ap_uint<4> a2, ap_uint<4>& andout) {
        andout = a1 & a2;
    }



    void sub1(ap_uint<64> i1, ap_uint<64> i2, ap_uint<64> i3, ap_uint<64> i4, ap_uint<64> &o1) {
        ap_uint<64> andout = 0;

//        and4(i3.range(3,0), i4.range(3,0), andout.range(3,0));
//        and4(i3.range(7,4), i4.range(7,4), andout.range(7,4));
//        and4(i3.range(11,8), i4.range(11,8), andout.range(11,8));
//        and4(i3.range(15,12), i4.range(15,12), andout.range(15,12));
//        and4(i3.range(19,16), i4.range(19,16), andout.range(19,16));
//        and4(i3.range(23,20), i4.range(23,20), andout.range(23,20));
//        and4(i3.range(27,24), i4.range(27,24), andout.range(27,24));
//        and4(i3.range(31,28), i4.range(31,28), andout.range(31,28));
//        and4(i3.range(35,32), i4.range(35,32), andout.range(35,32));
//        and4(i3.range(39,36), i4.range(39,36), andout.range(39,36));
//        and4(i3.range(43,40), i4.range(43,40), andout.range(43,40));
//        and4(i3.range(47,44), i4.range(47,44), andout.range(47,44));
//        and4(i3.range(51,48), i4.range(51,48), andout.range(51,48));
//        and4(i3.range(55,52), i4.range(55,52), andout.range(55,52));
//        and4(i3.range(59,56), i4.range(59,56), andout.range(59,56));
//        and4(i3.range(63,60), i4.range(63,60), andout.range(63,60));

            ap_uint<4> inputA, inputB, result;

            for (int i = 0; i < 64; i += 4) {
                inputA = i3.range(i+3, i);
                inputB = i4.range(i+3, i);
                and4(inputA, inputB, result);
                andout.range(i+3, i) = result;
            }

            o1 = i1 ^ i2 ^ andout;
        }

    void quick_mux_128(ap_uint<128> in1, ap_uint<128> in2, ap_uint<1> sel, ap_uint<128> &out) {
        if (sel)  out = in1;
        else      out = in2;
    }





        void p_keysch10::update(/*ap_uint<8> counter, ap_uint<1> data_in, ap_uint<2> data_rdy*/) {
        		ap_uint<128> temp;
        		ap_uint<64> temp2;
                if (data_rdy == 2) {
                	temp.bit(127)=data_in;
					temp.range(126,63)=KX;
					temp.range(62,0)=KY.range(63,1);
					KX = temp.range(127, 64);
					KY = temp.range(63, 0);
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




        void p_keysch11::update(/*ap_uint<8> counter, ap_uint<1> data_in, ap_uint<2> data_rdy*/) {
        		ap_uint<128> temp;
        		ap_uint<64> temp2;
                if (data_rdy == 2) {
                	temp.bit(127)=data_in;
                	temp.range(126,63)=KX;
                	temp.range(62,0)=KY.range(63,1);
                    KX = temp.range(127, 64);
                    KY = temp.range(63, 0);
                }
                else if (data_rdy == 3) {
                    if (counter.bit(0) == 1) {
                    	temp.range(127,125)=KX.range(2,0);
                    	temp.range(125,64) =KX.range(63,3);
                    	temp.range(63,60)=KX.range(3,0);
                    	temp.range(59,0)=KX.range(63,4);
                    	temp2=KX;
                        KX = KY ^ (temp.range(127,64)^temp.range(63,0));
                        KY = temp2;
                    }
                }

            key_out=KY;
        }





        void data_share2::update(/*ap_uint<2> data_rdy, ap_uint<1> counter, ap_uint<1> data_in, ap_uint<64> key_in, ap_uint<64> Y_in*/) {
             XL1_1 = (X.range(62,0), X[63]);
             XL2_1 = (X.range(61,0), X.range(63,62));
             XL8_1 = (X.range(55,0), X.range(63,56));

             YL1_1 = (Y.range(62,0), Y[63]);
             YL8_2 = (Y_in.range(55,0), Y_in.range(63,56));

            ap_uint<64> sout1, sout2;


            sub1(Y, XL2_1, XL8_1, XL1_1,sout1);
            sub1(X, key_in, YL1_1, YL8_2,sout2);


                if (data_rdy == 1) {
                    ap_uint<128> temp = (data_in, X, Y.range(63,1));
                    X = temp.range(63, 0);
                    Y = temp.range(127, 64);
                }
                else if (data_rdy == 3) {
                    if (counter == 0) {
                    	temp=X;
                        X = sout1;
                        Y = temp;
                    }
                    else {
                        X = sout2;
                    }
                }


            X_out = X;
            Y_out = Y;
        }



		void datapath::update(/*ap_uint<1> data_ina, ap_uint<1> data_inb,ap_uint<2> data_rdy,ap_uint<8> counter,ap_uint<64> key_ina,ap_uint<64> key_inb*/){
			//share_a input
			share_a.data_rdy=data_rdy;
			share_a.counter=counter.bit(0);
			share_a.data_in=data_ina;
			share_a.key_in=key_ina;
			share_a.Y_in=share_b.Y_out;
			//share_b input
			share_b.data_rdy=data_rdy;
			share_b.counter=counter.bit(0);
			share_b.data_in=data_inb;
			share_b.key_in=key_inb;
			share_b.Y_in=share_a.Y_out;
			//update
			share_a.update();
			share_b.update();
			//combinational logic
			if (counter>=134){
				sel1=1;
				sel2=1;
			}
			else{
				sel1=0;
				sel2=0;
			}

			quick_mux_128((share_a.X_out,share_a.Y_out),(ap_uint<128>)0,sel1,res1);
			quick_mux_128((share_b.X_out,share_b.Y_out),(ap_uint<128>)0,sel2,res2);
			cipher_out=res1^res2;


		}

void core::update(){

    	dp.counter=counter;
    	dp.data_ina=data_ina;
    	dp.data_inb=data_inb;
    	dp.data_rdy=data_rdy;
    	dp.key_ina=ks1.key_out;
    	dp.key_inb=ks2.key_out;
    	//datapath output
    	cipher_out=dp.cipher_out;
    	//ks1 input
    	ks1.counter=counter;
    	ks1.data_in=data_ina;
    	ks1.data_rdy=data_rdy;
    	//ks2 input
    	ks2.counter=counter;
		ks2.data_in=data_inb;
		ks2.data_rdy=data_rdy;
		//counter logic
		if(data_rdy==0) counter=0;
		else if(data_rdy==3) counter++;

		if(counter==1)Trig=1;
		else Trig=0;
		if((data_rdy==3) && (counter==134)) Done=1;
		else Done=0;
		dp.update();
		ks1.update();
		ks2.update();
    }

ap_uint<128> top(ap_uint<768> Din){
	ap_uint<128> Dout;

	    ap_uint<256> share_a = 0, share_b = 0, share_c = 0;
	    ap_uint<2> state = 0;
	    ap_uint<8> counter;
	    ap_uint<1> Done=0;
	    ap_uint<127> cipher_out;
	    int count=0;
	    share_a = 0;
		share_b = 0;
		share_c = 0;
		state = 0;
	    // TI_Simon_Core submodule
	    core my_simon_core;


	    share_a = Din.range(767, 512);
		share_b = Din.range(511, 256);
		share_c = Din.range(255, 0);
		state = 2;

			top_label1:while(count<393)
	    	{
				//debugging purpose
//				std::cout << "cycle: " << count << std::endl;
//
//				if(count==256)
//					std::cout << "256 reached "<< std::endl;
//				if(count==388)
//					std::cout << "300 reached "<< std::endl;
				//

	    	    Done = my_simon_core.Done;

				if (count == 128 && state == 2) state = 1;
				else if (count == 256 && state == 1) state = 3;
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

	    	    my_simon_core.update();

	    	 	cipher_out = my_simon_core.cipher_out;
	    	 	counter=my_simon_core.counter;
	    	 	count++;



	    	}


	    return cipher_out;
}

