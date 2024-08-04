#include <ap_int.h>

void and4(ap_uint<4> a1, ap_uint<4> a2, ap_uint<4>& andout);

void sub1(ap_uint<64> i1, ap_uint<64> i2, ap_uint<64> i3, ap_uint<64> i4, ap_uint<64> &o1);

void quick_mux_128(ap_uint<128> in1, ap_uint<128> in2, ap_uint<1> sel, ap_uint<128> &out);


class p_keysch10 {
	private:
		ap_uint<64> KX;
		ap_uint<68> Z;

		ap_uint<64> c = 0xFFFFFFFFFFFFFFFC;

	public:
		ap_uint<64> KY;
		ap_uint<64> key_out;
		//input
		ap_uint<8> counter;
		ap_uint<1> data_in;
		ap_uint<2> data_rdy;
		p_keysch10() : KX(0), KY(0) {Z.range(67,34)=0b1010111101110000001101001001100010;
		Z.range(33,0 )=0b1000010001111110010110110011101011;}
		void update();

};


class p_keysch11 {
    private:
        ap_uint<64> KX;

    public:
        ap_uint<64> KY;
        ap_uint<64> key_out;
        //input
        ap_uint<8> counter;
		ap_uint<1> data_in;
		ap_uint<2> data_rdy;


        void update();
};

class data_share2 {
    private:
        ap_uint<64> X, Y,temp;

    public:
        //input
        ap_uint<2> data_rdy;
        ap_uint<1> counter;
        ap_uint<1> data_in;
        ap_uint<64> key_in;
        ap_uint<64> Y_in;

        ap_uint<64> X_out, Y_out;

        ap_uint<64> XL1_1, XL2_1, XL8_1, YL1_1, YL8_2;
        void update();
};

class datapath {
    private:
    	//wires
    	ap_uint<64> Xout_a, Xout_b, Yout_a, Yout_b;
    	ap_uint<128> res1,res2;
    	//regs
    	ap_uint<1> sel1,sel2;
    	//submodules
    	data_share2 share_a,share_b;
    public:
    	//input
		ap_uint<1> data_ina,data_inb;
		ap_uint<2> data_rdy;
		ap_uint<8> counter;
		ap_uint<64> key_ina, key_inb;
		//output
		ap_uint<128> cipher_out;

		void update(/*ap_uint<1> data_ina, ap_uint<1> data_inb,ap_uint<2> data_rdy,ap_uint<8> counter,ap_uint<64> key_ina,ap_uint<64> key_inb*/);
};

class core {

public:
	//input
	ap_uint<1> data_ina;
	ap_uint<1> data_inb;
	ap_uint<2> data_rdy=0;
	//reg
	ap_uint<8> counter;
	//output
	ap_uint<128> cipher_out;
	ap_uint<1> Done=0;
	ap_uint<1> Trig=0;

	//submodule
	p_keysch10 ks1;
	p_keysch11 ks2;
	datapath dp;

	void update();
};

ap_uint<128> top(ap_uint<768> Din);

