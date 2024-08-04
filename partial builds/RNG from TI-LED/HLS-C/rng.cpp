#include <ap_int.h>
class TFF {
public:
    ap_uint<1> q;

    TFF() : q(1) {}

    void update(ap_uint<1> t) {
            if (t == 0) q = q;
             else       q = ~q;
    }
};

class TFF1 {
public:
    ap_uint<1> q;

    TFF1() : q(0) {}

    void update(ap_uint<1> t) {
            if (t == 0) q = q;
            else        q = ~q;
        }
};

class Random {
public:
    ap_uint<4> o;
    TFF u1;
    TFF1 u2, u3, u4;

    Random() : o(0) {}

    ap_uint<4> update(ap_uint<4> cycle) {
        update_label1:for( int i=0;i<cycle;i++){
    	ap_uint<1> t0 = o[3] ^ o[2];
        ap_uint<1> t1 = o[0];
        ap_uint<1> t2 = o[1];
        ap_uint<1> t3 = o[2];

        u1.update(t0);
        o[0] = u1.q;

        u2.update(t1);
        o[1] = u2.q;

        u3.update(t2);
        o[2] = u3.q;

        u4.update(t3);
        o[3] = u4.q;
        }
        return o;
    }
};
// Function to generate a random 4-bit number


// Top-level function
ap_uint<4> top(ap_uint<4> t) {
	Random rng;
    return rng.update(t);
}
