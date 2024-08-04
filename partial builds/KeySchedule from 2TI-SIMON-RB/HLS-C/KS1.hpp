#include <ap_int.h>

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
