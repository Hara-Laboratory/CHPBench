#include <ap_int.h>

class key_share{
public:
//input
	ap_uint<1> we,Start,EN;
	ap_uint<1> share_in,shiftlessthan8,shiftlessthan3,rndlessthan32,rnd0,keybit,Xbit_else,Ybit_else,carry_else;
//output
	ap_uint<1> Xbit_mine,Ybit_mine,carry_mine;

	ap_uint<56> X_63_8;
	ap_uint<8> X_7_0;
	ap_uint<61> Y_60_0;
	ap_uint<3> Y_63_61_even,Y_63_61_odd;
	void update();

	void key_share_roundTI(ap_uint<1> EN,ap_uint<1> keybit,ap_uint<1> Xbit,ap_uint<1> Ybit1,ap_uint<1> Ybit2,
			ap_uint<1> Xbit_else,ap_uint<1>  Ybit_else,ap_uint<1>  carry_else,
			ap_uint<1> &X_out,ap_uint<1> &Y_out,ap_uint<1> &carry);
};


class share{
public:
	//input
	ap_uint<1> we, Start,EN;
	ap_uint<1> share_in, shiftlessthan8,shiftlessthan3,rndlessthan32,rnd0;
	ap_uint<1> keybit,Xbit_else,Ybit_else,carry_else,carry_init;
	//output
	ap_uint<1> Xbit_mine,Ybit_mine,X_out,Y_out, carry_mine;
	ap_uint<1> share_out_X, share_out_Y;


	ap_uint<56> X_63_8;
	ap_uint<8> X_7_0;
	ap_uint<61> Y_60_0;
	ap_uint<3> Y_63_61_even, Y_63_61_odd;

	//else
	ap_uint<1> carry;

//	ap_uint<1> X_carry,Y_carry_even, Y_carry_odd, Y_carry_60_0,Y_carry;
	void update();

	void share_roundTI(ap_uint<1> EN,ap_uint<1> keybit, ap_uint<1> Xbit, ap_uint<1> Ybit1, ap_uint<1> Ybit2,
            ap_uint<1> Xbit_else, ap_uint<1> Ybit_else, ap_uint<1> carry_else,
            ap_uint<1> &Xout, ap_uint<1> &Yout, ap_uint<1> &carry,ap_uint<1> carry_init);
};

//class share_roundTI{
//public:
//	ap_uint
//};


class core{
public:
	//input
	ap_uint<1> EN,data_ina, data_inb, data_inc,k_data_ina,k_data_inb, k_data_inc,carry_init_a,carry_init_b,carry_init_c, we, Start;

	//output
	ap_uint<2> cipher_out1, cipher_out2, cipher_out3;
	ap_uint<1> rndlessthan32;

	//reg
	ap_uint<6> roundcnt,shiftcnt;

	//internal classes
	share dp1;
	share dp2;
	share dp3;

	key_share ks1;
	key_share ks2;
	key_share ks3;

	void update();

};




