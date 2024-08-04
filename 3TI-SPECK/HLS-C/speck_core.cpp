#include <ap_int.h>
#include "speck_core.hpp"


void core::update(){
	//wire
	ap_uint<1> shiftlessthan8,shiftlessthan3,rnd0,rc;
	//wires
		ap_uint<1> X_m1, X_m2, X_m3, Y_m1, Y_m2, Y_m3, C_m1, C_m2, C_m3;
		ap_uint<1> K_X_m1, K_X_m2, K_X_m3, K_Y_m1, K_Y_m2, K_Y_m3, K_C_m1, K_C_m2, K_C_m3;
		ap_uint<1> share_out1, share_out2, share_out3;
		ap_uint<1> share_out11, share_out22, share_out33;

	shiftlessthan8 = (shiftcnt < 8);
	shiftlessthan3 = (shiftcnt < 3);
	rndlessthan32 = (roundcnt < 32);
	rnd0 =roundcnt.bit(0);

	ap_uint<1> temp[2];


	//connecting sub modules
	//dp1--------------------------------
		//input
	dp1.we=we;
	dp1.Start=Start;
	dp1.EN=EN;
	dp1.share_in=data_ina;
	dp1.shiftlessthan8=shiftlessthan8;
	dp1.shiftlessthan3=shiftlessthan3;
	dp1.rndlessthan32 =rndlessthan32;
	dp1.rnd0=rnd0;
	dp1.keybit=K_Y_m1;
	dp1.Xbit_else=X_m2;
	dp1.Ybit_else=Y_m2;
	dp1.carry_else=C_m2;
	dp1.carry_init=1;
			//output
	dp1.update();
	temp[0]=X_m1;
	temp[1]=Y_m1;
	temp[2]=C_m1;
	X_m1=dp1.Xbit_mine;
	Y_m1=dp1.Ybit_mine;
	C_m1=dp1.carry_mine;
	share_out1=dp1.share_out_X;
	share_out11=dp1.share_out_Y;

	//dp2---------------------------------
			//input
	dp2.we=we;
	dp2.Start=Start;
	dp2.EN=EN;
	dp2.share_in=data_inb;
	dp2.shiftlessthan8=shiftlessthan8;
	dp2.shiftlessthan3=shiftlessthan3;
	dp2.rndlessthan32 =rndlessthan32;
	dp2.rnd0=rnd0;
	dp2.keybit=K_Y_m2;
	dp2.Xbit_else=X_m3;
	dp2.Ybit_else=Y_m3;
	dp2.carry_else=C_m3;
	dp2.carry_init=0;

	dp2.update();
			//output
	X_m2=dp2.Xbit_mine;
	Y_m2=dp2.Ybit_mine;
	C_m2=dp2.carry_mine;
	share_out2=dp2.share_out_X;
	share_out22=dp2.share_out_Y;

	//dp3----------------------------------
			//input
	dp3.we=we;
	dp3.Start=Start;
	dp3.EN=EN;
	dp3.share_in=data_inc;
	dp3.shiftlessthan8=shiftlessthan8;
	dp3.shiftlessthan3=shiftlessthan3;
	dp3.rndlessthan32 =rndlessthan32;
	dp3.rnd0=rnd0;
	dp3.keybit=K_Y_m3;
	dp3.Xbit_else=temp[0];
	dp3.Ybit_else=temp[1];
	dp3.carry_else=temp[2];
	dp3.carry_init=1;

	dp3.update();
			//output
	X_m3=dp3.Xbit_mine;
	Y_m3=dp3.Ybit_mine;
	C_m3=dp3.carry_mine;
	share_out3=dp3.share_out_X;
	share_out33=dp3.share_out_Y;

	//ks1---------------------------------
		//input
	ks1.we=we;
	ks1.Start=Start;
	ks1.EN=EN;
	ks1.share_in=k_data_ina;
	ks1.shiftlessthan8=shiftlessthan8;
	ks1.shiftlessthan3=shiftlessthan3;
	ks1.rndlessthan32 =rndlessthan32;
	ks1.rnd0=rnd0;
	ks1.keybit=rc;
	ks1.Xbit_else=K_X_m2;
	ks1.Ybit_else=K_Y_m2;
	ks1.carry_else=K_C_m2;

	ks1.update();
		//output
	temp[0]=K_X_m1;
	temp[1]=K_Y_m1;
	temp[2]=K_C_m1;
	K_X_m1=ks1.Xbit_mine;
	K_Y_m1=ks1.Ybit_mine;
	K_C_m1=ks1.carry_mine;

	//KS2---------------------------------
		//input
	ks2.we=we;
	ks2.Start=Start;
	ks2.EN=EN;
	ks2.share_in=k_data_ina;
	ks2.shiftlessthan8=shiftlessthan8;
	ks2.shiftlessthan3=shiftlessthan3;
	ks2.rndlessthan32 =rndlessthan32;
	ks2.rnd0=rnd0;
	ks2.keybit=0;
	ks2.Xbit_else=K_X_m3;
	ks2.Ybit_else=K_Y_m3;
	ks2.carry_else=K_C_m3;

	ks2.update();
		//output
	K_X_m2=ks2.Xbit_mine;
	K_Y_m2=ks2.Ybit_mine;
	K_C_m2=ks2.carry_mine;

	//KS3---------------------------------
		//input
	ks3.we=we;
	ks3.Start=Start;
	ks3.EN=EN;
	ks3.share_in=k_data_ina;
	ks3.shiftlessthan8=shiftlessthan8;
	ks3.shiftlessthan3=shiftlessthan3;
	ks3.rndlessthan32 =rndlessthan32;
	ks3.rnd0=rnd0;
	ks3.keybit=0;
	ks3.Xbit_else=temp[0];
	ks3.Ybit_else=temp[1];
	ks3.carry_else=temp[2];
	ks3.update();
		//output
	K_X_m3=ks3.Xbit_mine;
	K_Y_m3=ks3.Ybit_mine;
	K_C_m3=ks3.carry_mine;


	EN=(rndlessthan32)&&(shiftcnt!=63)&&(Start);


	rc = (shiftcnt == 0) ? roundcnt.bit(0) :
	     ((shiftcnt == 1) ? roundcnt.bit(1) :
	      ((shiftcnt == 2) ? roundcnt.bit(2) :
	       ((shiftcnt == 3) ? roundcnt.bit(3) :
	        ((shiftcnt == 4) ? roundcnt.bit(4) :
	         ((shiftcnt == 5) ? roundcnt.bit(5) : ap_uint<1>(0))))));
	if(~Start){
		roundcnt=0;
		shiftcnt=0;
	}
	else{
		if(rndlessthan32){
			shiftcnt++;
			if(~EN)roundcnt++;
		}
	}

	cipher_out1.bit(0) = share_out1;
	cipher_out1.bit(1) = share_out11;

	cipher_out2.bit(0) = share_out2;
	cipher_out2.bit(1) = share_out22;

	cipher_out3.bit(0) = share_out3;
	cipher_out3.bit(1) = share_out33;




}

void share::update(){
	// Combinational logic for wire ments
		ap_uint<1>  Y_out,X_out;
		ap_uint<1> X_carry,Y_carry_even, Y_carry_odd,Y_carry,Y_carry_60_0;


	     X_carry = shiftlessthan8 ? X_7_0.bit(0): X_out;
	     Y_carry_even = rnd0 ? Y_out : Y_60_0.bit(0);
	     Y_carry_odd = rnd0 ? Y_60_0.bit(0): Y_out;
	     Y_carry = rnd0 ? Y_63_61_odd.bit(0): Y_63_61_even.bit(0);
	     Y_carry_60_0 = rnd0 ? (shiftlessthan3 ? Y_63_61_odd.bit(0) : Y_63_61_even.bit(0)) :
	                                        (shiftlessthan3 ? Y_63_61_even.bit(0) : Y_63_61_odd.bit(0));

	    // Sequential logic - mimicking the behavior of the alwaYs block
	    if (we) {

//	    	Y_60_0 = (Y_63_61_even.bit(0), Y_60_0.range(60, 1));
	    	Y_60_0.range(59,0)=Y_60_0.range(60, 1);
	    	Y_60_0.bit(60)=Y_63_61_even.bit(0);

//	    	Y_63_61_even = (X_7_0.bit(0), Y_63_61_even.range(2, 1));
	    	Y_63_61_even.range(1, 0) = Y_63_61_even.range(2, 1);
	    	Y_63_61_even.bit(2) = X_7_0.bit(0);

//	    	X_7_0 = (X_63_8.bit(0), X_7_0.range(7, 1));
	    	X_7_0.range(6, 0) = X_7_0.range(7, 1);
	    	X_7_0.bit(7) = X_63_8.bit(0);

//	        X_63_8 = (share_in, X_63_8.range(55, 1));
	    	X_63_8.range(54, 0) = X_63_8.range(55, 1);
	    	X_63_8.bit(55) = share_in;

	    }
	    else if (Start) {
	        if (rndlessthan32) {
	            if (shiftlessthan8) {
//	                X_7_0 = (X_out, X_7_0.range(7, 1));
	            	X_7_0.range(6, 0) = X_7_0.range(7, 1);
	            	X_7_0.bit(7) = X_out;
	            }
//	            X_63_8 = (X_carry, X_63_8.range(55, 1));
	            X_63_8.range(54, 0) = X_63_8.range(55, 1);
	            X_63_8.bit(55) = X_carry;

//	            Y_60_0 = (Y_carry_60_0, Y_60_0.range(60, 1));
	            Y_60_0.range(59, 0) = Y_60_0.range(60, 1);
	            Y_60_0.bit(60) = Y_carry_60_0;

//	            Y_63_61_even = (Y_carry_even, Y_63_61_even.range(2, 1));
	            Y_63_61_even.range(1, 0) = Y_63_61_even.range(2, 1);
	            Y_63_61_even.bit(2) = Y_carry_even;

//	            Y_63_61_odd = (Y_carry_odd, Y_63_61_odd.range(2, 1));
	            Y_63_61_odd.range(1, 0) = Y_63_61_odd.range(2, 1);
	            Y_63_61_odd.bit(2) = Y_carry_odd;
	        }
	        else {
//	        	X_7_0 = (X_63_8.bit(0), X_7_0.range(7, 1));
	        	X_7_0.range(6, 0) = X_7_0.range(7, 1);
	        	X_7_0.bit(7) = X_63_8.bit(0);

//	            X_63_8 = (0, X_63_8.range(55, 1));
	        	X_63_8.range(54, 0) = X_63_8.range(55, 1);
	        	X_63_8.bit(55) = 0;


//	            Y_60_0 = (Y_63_61_even.bit(0), Y_60_0.range(60, 1));
	        	Y_60_0.range(59, 0) = Y_60_0.range(60, 1);
	        	Y_60_0.bit(60) = Y_63_61_even.bit(0);

//	            Y_63_61_even = (0, Y_63_61_even.range(2, 1));
	        	Y_63_61_even.range(1, 0) = Y_63_61_even.range(2, 1);
	        	Y_63_61_even.bit(2) = 0;
	        }
	    }
	    // assign outputs
	    Xbit_mine = X_63_8.bit(0);
	    Ybit_mine = Y_60_0.bit(0);
	    share_out_X = X_7_0.bit(0);
	    share_out_Y = Y_60_0.bit(0);
	    share_roundTI(EN,keybit,Xbit_mine,Ybit_mine,Y_carry,Xbit_else,Ybit_else,carry_else,X_out,Y_out,carry_mine,carry_init);
}

void share::share_roundTI(ap_uint<1> EN,ap_uint<1> keybit, ap_uint<1> Xbit, ap_uint<1> Ybit1, ap_uint<1> Ybit2,
        ap_uint<1> Xbit_else, ap_uint<1> Ybit_else, ap_uint<1> carry_else,
        ap_uint<1> &Xout, ap_uint<1> &Yout, ap_uint<1> &carry,ap_uint<1> carry_init) {

		X_out = carry ^ Xbit ^ Ybit1 ^ keybit;
		Y_out = X_out ^ Ybit2;

		if(~EN){
			carry=carry_init;
		}
		else{

	        // When EN is high, carry is updated based on the nonlinear operation
	        carry = (Xbit && carry) ^ (Xbit && carry_else) ^ (Xbit_else && carry)
	              ^ (Xbit && Ybit1) ^ (Xbit && Ybit_else) ^ (Xbit_else && Ybit1)
	              ^ (Ybit1 && carry) ^ (Ybit1 && carry_else) ^ (Ybit_else && carry);
		}
}


void key_share::update(){
	ap_uint<1> X_out,Y_out,X_carry,Y_carry_even,Y_carry_odd,Y_carry_60_0,Y_carry;
	//assign block


	 X_carry=(shiftlessthan8) ? X_7_0.bit(0) : X_out;
	 Y_carry_even = rnd0 ? Y_out : Y_60_0.bit(0);
	 Y_carry_odd  = rnd0 ? Y_60_0.bit(0) : Y_out;
	 Y_carry      = rnd0 ? Y_63_61_odd.bit(0): Y_63_61_even.bit(0);
	 Y_carry_60_0 = rnd0 ? ((shiftlessthan3) ? Y_63_61_odd.bit(0)  : Y_63_61_even.bit(0)):
													 ((shiftlessthan3) ? Y_63_61_even.bit(0) :  Y_63_61_odd.bit(0));

	 Xbit_mine = X_63_8.bit(0);
	 Ybit_mine = Y_60_0.bit(0);

	 if (we) {
	     Y_60_0.range(59, 0) = Y_60_0.range(60, 1);
	     Y_60_0.bit(60) = Y_63_61_even.bit(0);

	     Y_63_61_even.range(1, 0) = Y_63_61_even.range(2, 1);
	     Y_63_61_even.bit(2) = X_7_0.bit(0);

	     X_7_0.range(6, 0) = X_7_0.range(7, 1);
	     X_7_0.bit(7) = X_63_8.bit(0);

	     X_63_8.range(54, 0) = X_63_8.range(55, 1);
	     X_63_8.bit(55) = share_in;
	 } else if (Start) {
	     if (rndlessthan32) {
	         if (shiftlessthan8) {
	             X_7_0.range(6, 0) = X_7_0.range(7, 1);
	             X_7_0.bit(7) = X_out;
	         }
	         X_63_8.range(54, 0) = X_63_8.range(55, 1);
	         X_63_8.bit(55) = X_carry;

	         // Processing the right block in 64 clock cycles
	         Y_60_0.range(59, 0) = Y_60_0.range(60, 1);
	         Y_60_0.bit(60) = Y_carry_60_0;

	         Y_63_61_even.range(1, 0) = Y_63_61_even.range(2, 1);
	         Y_63_61_even.bit(2) = Y_carry_even;

	         Y_63_61_odd.range(1, 0) = Y_63_61_odd.range(2, 1);
	         Y_63_61_odd.bit(2) = Y_carry_odd;
	     }
	 }

	 key_share_roundTI(EN, keybit, Xbit_mine, Ybit_mine, Y_carry, Xbit_else,  Ybit_else,  carry_else,X_out, Y_out, carry_mine);
}


void key_share::key_share_roundTI(ap_uint<1> EN,ap_uint<1> keybit,ap_uint<1> Xbit,ap_uint<1> Ybit1,ap_uint<1> Ybit2,
		ap_uint<1> Xbit_else,ap_uint<1>  Ybit_else,ap_uint<1>  carry_else,
		ap_uint<1> &X_out,ap_uint<1> &Y_out,ap_uint<1> &carry){

	X_out = carry ^ Xbit ^ Ybit1 ^ keybit;
	Y_out = X_out ^ Ybit2;

	if(~EN)carry=0;
	else{
	carry = (Xbit && carry) ^ (Xbit && carry_else) ^ (Xbit_else && carry)
					  ^ (Xbit && Ybit1) ^ (Xbit && Ybit_else) ^ (Xbit_else && Ybit1)
					  ^ (Ybit1 && carry) ^ (Ybit1 && carry_else) ^ (Ybit_else && carry);
	}
}
