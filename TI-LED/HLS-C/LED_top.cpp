#include <ap_int.h>

#define CMD_IDLE            0
#define CMD_LOAD            1
#define CMD_ADDSHARE_NIBBLE 2
#define CMD_ADDSHARE_KEY    3
#define CMD_ADDCONSTANT     4
#define CMD_SBOX_CAL        5
#define CMD_SBOX_SHIFT      6
#define CMD_SHIFTROW        7
#define CMD_MIXCOLCOMPUTE   8
#define CMD_MIXCOLROTATE    9
#define CMD_ADDKEY          10
#define CMD_BACK_SHARE      11

#define STATE_IDLE          0
#define STATE_LOAD          1
#define STATE_ADDSHARE_NIBBLE 2
#define STATE_ADDSHARE_KEY  3
#define STATE_INIT          4
#define STATE_ADDCONSTANT   5
#define STATE_SBOX_CAL      6
#define STATE_SBOX_SHIFT    7
#define STATE_SHIFTROW      8
#define STATE_MIXCOL0       9
#define STATE_MIXCOL1       10
#define STATE_MIXCOL2       11
#define STATE_MIXCOL3       12
#define STATE_MIXCOL4       13
#define STATE_NEXTROUND     14
#define STATE_ADDKEY        15
#define STATE_NEXTSTEP      16
#define STATE_BACK_SHARE    17

#define STATE_SBOXG 1
#define STATE_SBOXF 2
#define STATE_FINISH 3

class TFF {
public:
    ap_uint<1> q;

    TFF() : q(1) {}

    void update(ap_uint<1> t, ap_uint<1> c) {
        if (c == 1) {
            if (t == 0) q = q;
             else       q = ~q;
        }
    }
};

class TFF1 {
public:
    ap_uint<1> q;

    TFF1() : q(0) {}

    void update(ap_uint<1> t, ap_uint<1> c) {
        if (c == 1) {
            if (t == 0) q = q;
            else        q = ~q;
        }
    }
};

class Random {
public:
    ap_uint<4> o;
    TFF u1;
    TFF1 u2, u3, u4;

    Random() : o(0) {}

    ap_uint<4> update(ap_uint<1> clk) {
        ap_uint<1> t0 = o[3] ^ o[2];
        ap_uint<1> t1 = o[0];
        ap_uint<1> t2 = o[1];
        ap_uint<1> t3 = o[2];

        u1.update(t0, clk);
        o[0] = u1.q;

        u2.update(t1, clk);
        o[1] = u2.q;

        u3.update(t2, clk);
        o[2] = u3.q;

        u4.update(t3, clk);
        o[3] = u4.q;
        return o;
    }
};

class SBox {
public:
	 	ap_int<8> nibblesi_8;
		ap_int<8> mask;
		ap_int<8> nibblesq_8;
		ap_int<12> nibblesq_12;
		ap_int<4> y1, y2, y3;
		bool done;
		ap_int<4> ctlstate;
		ap_int<1>start;

    SBox() : nibblesi_8(0), mask(0), nibblesq_8(0), done(false), ctlstate(STATE_IDLE) {}



    void update() {
         ap_uint<4> ctlstate_next = ctlstate;
        ap_uint<12> nibblesq_12_next = nibblesq_12;
        ap_uint<4> y1_next = y1;
        ap_uint<4> y2_next = y2;
        ap_uint<4> y3_next = y3;

        ap_uint<4> n1 = mask.range(3, 0) ^ mask.range(7, 4);
        ap_uint<4> n2 = nibblesi_8.range(7, 4) ^ mask.range(7, 4);
        ap_uint<4> n3 = nibblesi_8.range(3, 0) ^ mask.range(3, 0);

         switch (ctlstate) {
            case STATE_IDLE:
                ctlstate_next = start ? STATE_SBOXG : STATE_IDLE;
                done = false;
                break;
            case STATE_SBOXG:
                y1_next = G1((n2, n3));
                y2_next = G2((n1, n3));
                y3_next = G3((n1, n2));
                ctlstate_next = STATE_SBOXF;
                break;
            case STATE_SBOXF:
                nibblesq_12_next.range(3, 0) = F1((y2, y1));
                nibblesq_12_next.range(7, 4) = F2((y3, y1));
                nibblesq_12_next.range(11, 8) = F3((y3, y2));
                ctlstate_next = STATE_FINISH;
                done = true;
                break;
            case STATE_FINISH:

                ctlstate_next = STATE_IDLE;
                break;
        }
         ctlstate = ctlstate_next;

        nibblesq_12=nibblesq_12_next;
    }

    ap_uint<4> G1(ap_uint<8> G1input) {
        ap_uint<4> result;
        result[3] = G1input[6] ^ G1input[5] ^ G1input[4];
        result[2] = 1 ^ G1input[6] ^ G1input[5];
        result[1] = 1 ^ G1input[7] ^ G1input[5] ^ (G1input[6] & G1input[4]) ^ (G1input[6] & G1input[0]) ^ (G1input[2] & G1input[4]) ^ (G1input[5] & G1input[4]) ^ (G1input[5] & G1input[0]) ^ (G1input[1] & G1input[4]);
        result[0] = 1 ^ G1input[4] ^ (G1input[7] & G1input[6]) ^ (G1input[7] & G1input[2]) ^ (G1input[3] & G1input[6]) ^ (G1input[7] & G1input[5]) ^ (G1input[7] & G1input[1]) ^ (G1input[3] & G1input[5]) ^ (G1input[6] & G1input[5]) ^ (G1input[6] & G1input[1]) ^ (G1input[2] & G1input[5]);
        return result;
    }

    ap_uint<4> G2(ap_uint<8> G2input) {
        ap_uint<4> result;
        result[3] = G2input[2] ^ G2input[1] ^ G2input[0];
        result[2] = G2input[2] ^ G2input[1];
        result[1] = G2input[3] ^ G2input[1] ^ (G2input[2] & G2input[0]) ^ (G2input[2] & G2input[4]) ^ (G2input[6] & G2input[0]) ^ (G2input[1] & G2input[0]) ^ (G2input[1] & G2input[4]) ^ (G2input[5] & G2input[0]);
        result[0] = G2input[0] ^ (G2input[3] & G2input[2]) ^ (G2input[3] & G2input[6]) ^ (G2input[7] & G2input[2]) ^ (G2input[3] & G2input[1]) ^ (G2input[3] & G2input[5]) ^ (G2input[7] & G2input[1]) ^ (G2input[2] & G2input[1]) ^ (G2input[2] & G2input[5]) ^ (G2input[6] & G2input[1]);
        return result;
    }

    ap_uint<4> G3(ap_uint<8> G3input) {
        ap_uint<4> result;
        result[3] = G3input[6] ^ G3input[5] ^ G3input[4];
        result[2] = G3input[6] ^ G3input[5];
        result[1] = G3input[7] ^ G3input[5] ^ (G3input[6] & G3input[4]) ^ (G3input[6] & G3input[0]) ^ (G3input[2] & G3input[4]) ^ (G3input[5] & G3input[4]) ^ (G3input[5] & G3input[0]) ^ (G3input[1] & G3input[4]);
        result[0] = G3input[4] ^ (G3input[7] & G3input[6]) ^ (G3input[7] & G3input[2]) ^ (G3input[3] & G3input[6]) ^ (G3input[7] & G3input[5]) ^ (G3input[7] & G3input[1]) ^ (G3input[3] & G3input[5]) ^ (G3input[6] & G3input[5]) ^ (G3input[6] & G3input[1]) ^ (G3input[2] & G3input[5]);
        return result;
    }

    ap_uint<4> F1(ap_uint<8> F1input) {
        ap_uint<4> result;
        result[3] = F1input[6] ^ F1input[5] ^ F1input[4] ^ (F1input[7] & F1input[4]) ^ (F1input[7] & F1input[0]) ^ (F1input[3] & F1input[4]);
        result[2] = F1input[7] ^ (F1input[5] & F1input[4]) ^ (F1input[5] & F1input[0]) ^ (F1input[1] & F1input[4]);
        result[1] = F1input[6] ^ F1input[5] ^ (F1input[7] & F1input[4]) ^ (F1input[7] & F1input[0]) ^ (F1input[3] & F1input[4]);
        result[0] = F1input[5] ^ (F1input[6] & F1input[4]) ^ (F1input[6] & F1input[0]) ^ (F1input[2] & F1input[4]);
        return result;
    }

    ap_uint<4> F2(ap_uint<8> F2input) {
        ap_uint<4> result;
        result[3] = F2input[2] ^ F2input[1] ^ F2input[0] ^ (F2input[3] & F2input[0]) ^ (F2input[3] & F2input[4]) ^ (F2input[7] & F2input[0]);
        result[2] = F2input[3] ^ (F2input[1] & F2input[0]) ^ (F2input[1] & F2input[4]) ^ (F2input[5] & F2input[0]);
        result[1] = F2input[2] ^ F2input[1] ^ (F2input[3] & F2input[0]) ^ (F2input[3] & F2input[4]) ^ (F2input[7] & F2input[0]);
        result[0] = F2input[1] ^ (F2input[2] & F2input[0]) ^ (F2input[6] & F2input[0]) ^ (F2input[2] & F2input[4]);
        return result;
    }

    ap_uint<4> F3(ap_uint<8> F3input) {
        ap_uint<4> result;
        result[3] = F3input[6] ^ F3input[5] ^ F3input[4] ^ (F3input[7] & F3input[4]) ^ (F3input[7] & F3input[0]) ^ (F3input[3] & F3input[4]);
        result[2] = F3input[7] ^ (F3input[5] & F3input[4]) ^ (F3input[5] & F3input[0]) ^ (F3input[1] & F3input[4]);
        result[1] = F3input[6] ^ F3input[5] ^ (F3input[7] & F3input[4]) ^ (F3input[7] & F3input[0]) ^ (F3input[3] & F3input[4]);
        result[0] = F3input[5] ^ (F3input[6] & F3input[4]) ^ (F3input[6] & F3input[0]) ^ (F3input[2] & F3input[4]);
        return result;
    }
};

class LEDSerial {
public:
		ap_uint<5> ctlstate;
	    ap_uint<4> bcount, rcount, scount;
	    ap_uint<5> keycount;
	    ap_uint<64> state, state_next;
	    ap_uint<128> key, key_next;
	    ap_uint<128> state_shared, state_shared_next;
	    ap_uint<256> key_shared, key_shared_next;
	    ap_uint<6> rc, rc_next;
	    ap_uint<1> sbox_start;
	    ap_uint<5> ctlstate_next = 0;
	            ap_uint<4> bcount_next =0;
	            ap_uint<4> rcount_next = 0;
	            ap_uint<4> scount_next = 0;
	            ap_uint<5> keycount_next = 0;
	            ap_uint<4> cmd = CMD_IDLE;


	    Random random_0, random_1;
	    SBox sbox;
	    ap_uint<8> temp_reg1,temp_reg2,temp_reg3,temp_reg4,temp_reg5;



    ap_uint<128> keyi;
    ap_uint<64> datai;
    ap_uint<64> dataq;
    bool done;
    ap_uint<8> mask;

    LEDSerial() : keyi(0), datai(0), dataq(0), done(false), mask(0),
                  ctlstate(STATE_IDLE), bcount(0), rcount(0), scount(0), keycount(0),
                  state(0), state_shared(0), key(0), key_shared(0) {}

    void update() {//logic for connecting submodules with core
        mask.range(3,0)=random_0.update(1);
        mask.range(7,4)=random_1.update(1);

        control_logic();

		mask.range(3,0)=random_0.update(0);
		mask.range(7,4)=random_1.update(0);
    }


    void control_logic() {//logic for core
         ctlstate_next = ctlstate;
         bcount_next = bcount;
         rcount_next = rcount;
         scount_next = scount;
         keycount_next = keycount;
         state_next = state;
         state_shared_next = state_shared;
         key_next = key;
         key_shared_next = key_shared;
         rc_next = rc;
         cmd = CMD_IDLE;



         switch (ctlstate) {
             case STATE_IDLE:
                 cmd = CMD_IDLE;
                 bcount_next = 0;
                 rcount_next = 0;
                 scount_next = 0;
                 ctlstate_next = STATE_LOAD;
                 break;
             case STATE_LOAD:
                 cmd = CMD_LOAD;
                 ctlstate_next = STATE_ADDSHARE_NIBBLE;
                 break;
             case STATE_ADDSHARE_NIBBLE:
                 cmd = CMD_ADDSHARE_NIBBLE;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_ADDSHARE_KEY;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_ADDSHARE_NIBBLE;
                 }
                 break;
             case STATE_ADDSHARE_KEY:
                 cmd = CMD_ADDSHARE_KEY;
                 if (keycount == 31) {
                     keycount_next = ap_int<5>(0);
                     ctlstate_next = STATE_INIT;
                 } else {
                     keycount_next = keycount + 1;
                     ctlstate_next = STATE_ADDSHARE_KEY;
                 }
                 break;
             case STATE_INIT:
                 cmd = CMD_ADDKEY;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_ADDCONSTANT;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_INIT;
                 }
                 break;
             case STATE_ADDCONSTANT:
                 cmd = CMD_ADDCONSTANT;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_SBOX_CAL;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_ADDCONSTANT;
                 }
                 break;
             case STATE_SBOX_CAL:
                 cmd = CMD_SBOX_CAL;
                 sbox_start = 1;
                 ctlstate_next = sbox.done ? STATE_SBOX_SHIFT : STATE_SBOX_CAL;
                 break;
             case STATE_SBOX_SHIFT:
                 cmd = CMD_SBOX_SHIFT;
                 sbox_start = 0;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_SHIFTROW;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_SBOX_CAL;
                 }
                 break;
             case STATE_SHIFTROW:
                 cmd = CMD_SHIFTROW;
                 ctlstate_next = STATE_MIXCOL0;
                 break;
             case STATE_MIXCOL0:
                 cmd = CMD_MIXCOLCOMPUTE;
                 ctlstate_next = STATE_MIXCOL1;
                 break;
             case STATE_MIXCOL1:
                 cmd = CMD_MIXCOLCOMPUTE;
                 ctlstate_next = STATE_MIXCOL2;
                 break;
             case STATE_MIXCOL2:
                 cmd = CMD_MIXCOLCOMPUTE;
                 ctlstate_next = STATE_MIXCOL3;
                 break;
             case STATE_MIXCOL3:
                 cmd = CMD_MIXCOLCOMPUTE;
                 ctlstate_next = STATE_MIXCOL4;
                 break;
             case STATE_MIXCOL4:
                 cmd = CMD_MIXCOLROTATE;
                 if (bcount == 3) {
                     bcount_next = 0;
                     ctlstate_next = STATE_NEXTROUND;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_MIXCOL0;
                 }
                 break;
             case STATE_NEXTROUND:
                 if (rcount == 3) {
                     rcount_next = 0;
                     ctlstate_next = STATE_ADDKEY;
                 } else {
                     rcount_next = rcount + 1;
                     ctlstate_next = STATE_ADDCONSTANT;
                 }
                 break;
             case STATE_ADDKEY:
                 cmd = CMD_ADDKEY;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_NEXTSTEP;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_ADDKEY;
                 }
                 break;
             case STATE_NEXTSTEP:
                 if (scount == 11) {
                     scount_next = 0;
                     ctlstate_next = STATE_BACK_SHARE;
                 } else {
                     scount_next = scount + 1;
                     ctlstate_next = STATE_ADDCONSTANT;
                 }
                 break;
             case STATE_BACK_SHARE:
                 cmd = CMD_BACK_SHARE;
                 if (bcount == 15) {
                     bcount_next = 0;
                     ctlstate_next = STATE_IDLE;
                 } else {
                     bcount_next = bcount + 1;
                     ctlstate_next = STATE_BACK_SHARE;
                 }
                 break;
         }
        sbox.nibblesi_8=staten_shared(state_shared,0,0);
        sbox.mask=mask;
        sbox.start=sbox_start;
        sbox.update();
        ap_uint<8>temp;
        switch (cmd) {
                case CMD_IDLE:
                    break;

                case CMD_LOAD:
                    key_next = keyi;
                    state_next = datai;
                    break;

                case CMD_ADDSHARE_NIBBLE:

                	temp =0;
                	temp.range(7,4)=staten(state, 0, 0) ^ mask.range(3, 0);
                	temp.range(3,0)=mask.range(3,0);
                    keyn_shared_next(key_shared_next, temp, 1, 3, 3);

                    staten_shared_next(state_shared_next, temp, 3, 3);

                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);

                    staten_next(state_next, 0, 3, 3);
                    staten_next(state_next, staten(state, 3, 3), 3, 2);
                    staten_next(state_next, staten(state, 3, 2), 3, 1);
                    staten_next(state_next, staten(state, 3, 1), 3, 0);
                    staten_next(state_next, staten(state, 3, 0), 2, 3);
                    staten_next(state_next, staten(state, 2, 3), 2, 2);
                    staten_next(state_next, staten(state, 2, 2), 2, 1);
                    staten_next(state_next, staten(state, 2, 1), 2, 0);
                    staten_next(state_next, staten(state, 2, 0), 1, 3);
                    staten_next(state_next, staten(state, 1, 3), 1, 2);
                    staten_next(state_next, staten(state, 1, 2), 1, 1);
                    staten_next(state_next, staten(state, 1, 1), 1, 0);
                    staten_next(state_next, staten(state, 1, 0), 0, 3);
                    staten_next(state_next, staten(state, 0, 3), 0, 2);
                    staten_next(state_next, staten(state, 0, 2), 0, 1);
                    staten_next(state_next, staten(state, 0, 1), 0, 0);

                    break;

                case CMD_ADDSHARE_KEY:
                	temp =0;
                	temp.range(7,4)=keyn(key, 0, 0, 0) ^ mask.range(7, 4);
                	temp.range(3,0)=mask.range(7,4);
                    keyn_shared_next(key_shared_next, temp, 1, 3, 3);

                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 3), 1, 0, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 0), 1, 0, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 1), 1, 0, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 2), 1, 0, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 3), 1, 1, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 0), 1, 1, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 1), 1, 1, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 2), 1, 1, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 3), 1, 2, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 0), 1, 2, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 1), 1, 2, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 2), 1, 2, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 3), 1, 3, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 0), 1, 3, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 1), 1, 3, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 2), 1, 3, 3);

                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 0), 0, 0, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 1), 0, 0, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 2), 0, 0, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 3), 0, 1, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 0), 0, 1, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 1), 0, 1, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 2), 0, 1, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 3), 0, 2, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 0), 0, 2, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 1), 0, 2, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 2), 0, 2, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 3), 0, 3, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 0), 0, 3, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 1), 0, 3, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 2), 0, 3, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 3), 1, 0, 0);

                    keyn_next(key_next, keyn(key, 0, 0, 0), 0, 0, 1);
                    keyn_next(key_next, keyn(key, 0, 0, 1), 0, 0, 2);
                    keyn_next(key_next, keyn(key, 0, 0, 2), 0, 0, 3);
                    keyn_next(key_next, keyn(key, 0, 0, 3), 0, 1, 0);
                    keyn_next(key_next, keyn(key, 0, 1, 0), 0, 1, 1);
                    keyn_next(key_next, keyn(key, 0, 1, 1), 0, 1, 2);
                    keyn_next(key_next, keyn(key, 0, 1, 2), 0, 1, 3);
                    keyn_next(key_next, keyn(key, 0, 1, 3), 0, 2, 0);
                    keyn_next(key_next, keyn(key, 0, 2, 0), 0, 2, 1);
                    keyn_next(key_next, keyn(key, 0, 2, 1), 0, 2, 2);
                    keyn_next(key_next, keyn(key, 0, 2, 2), 0, 2, 3);
                    keyn_next(key_next, keyn(key, 0, 2, 3), 0, 3, 0);
                    keyn_next(key_next, keyn(key, 0, 3, 0), 0, 3, 1);
                    keyn_next(key_next, keyn(key, 0, 3, 1), 0, 3, 2);
                    keyn_next(key_next, keyn(key, 0, 3, 2), 0, 3, 3);
                    keyn_next(key_next, keyn(key, 1, 0, 0), 1, 0, 1);
                    keyn_next(key_next, keyn(key, 1, 0, 1), 1, 0, 2);
                    keyn_next(key_next, keyn(key, 1, 0, 2), 1, 0, 3);
                    keyn_next(key_next, keyn(key, 1, 0, 3), 1, 1, 0);
                    keyn_next(key_next, keyn(key, 1, 1, 0), 1, 1, 1);
                    keyn_next(key_next, keyn(key, 1, 1, 1), 1, 1, 2);
                    keyn_next(key_next, keyn(key, 1, 1, 2), 1, 1, 3);
                    keyn_next(key_next, keyn(key, 1, 1, 3), 1, 2, 0);
                    keyn_next(key_next, keyn(key, 1, 2, 0), 1, 2, 1);
                    keyn_next(key_next, keyn(key, 1, 2, 1), 1, 2, 2);
                    keyn_next(key_next, keyn(key, 1, 2, 2), 1, 2, 3);
                    keyn_next(key_next, keyn(key, 1, 2, 3), 1, 3, 0);
                    keyn_next(key_next, keyn(key, 1, 3, 0), 1, 3, 1);
                    keyn_next(key_next, keyn(key, 1, 3, 1), 1, 3, 2);
                    keyn_next(key_next, keyn(key, 1, 3, 2), 1, 3, 3);
                    keyn_next(key_next, 0, 1, 3, 3);

                    break;

                case CMD_ADDKEY:
                	temp =0;
                	temp=staten_shared(state_shared, 0, 0) ^ keyn_shared(key_shared, 0, 0, 0);

                    staten_shared_next(state_shared_next, temp, 3, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);

                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 1), 0, 0, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 2), 0, 0, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 3), 0, 0, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 0), 0, 0, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 1), 0, 1, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 2), 0, 1, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 1, 3), 0, 1, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 0), 0, 1, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 1), 0, 2, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 2), 0, 2, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 2, 3), 0, 2, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 0), 0, 2, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 1), 0, 3, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 2), 0, 3, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 3, 3), 0, 3, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 0), 0, 3, 3);

                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 1), 1, 0, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 2), 1, 0, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 0, 3), 1, 0, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 0), 1, 0, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 1), 1, 1, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 2), 1, 1, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 1, 3), 1, 1, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 0), 1, 1, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 1), 1, 2, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 2), 1, 2, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 2, 3), 1, 2, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 0), 1, 2, 3);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 1), 1, 3, 0);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 2), 1, 3, 1);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 1, 3, 3), 1, 3, 2);
                    keyn_shared_next(key_shared_next, keyn_shared(key_shared, 0, 0, 0), 1, 3, 3);

                    break;

                case CMD_ADDCONSTANT:
                	staten_shared_next(state_shared_next, logic_round(staten_shared(state_shared, 0, 0), logic_addconst_decode(bcount,mask,rc)), 3, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);

                    break;

                case CMD_SBOX_CAL:
                    // Do nothing here. `staten_shared(0,0)` already connect to sbox input.
                    break;

                case CMD_SBOX_SHIFT:

                    staten_shared_next(state_shared_next, sbox.nibblesq_8, 3, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);

                    break;

                case CMD_SHIFTROW:
                	rc_next.range(5,1) = rc.range(4, 0);
                	rc_next.bit(0)=(1 ^ rc[4] ^ rc[5]);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 0), 0, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 3);

                    break;

                case CMD_MIXCOLCOMPUTE:
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 0);

                    temp_reg1 = staten_shared(state_shared, 0, 0);
                    temp_reg2 = staten_shared(state_shared, 1, 0);
                    temp_reg3 = staten_shared(state_shared, 2, 0);
                    temp_reg4 = staten_shared(state_shared, 3, 0);

                    temp_reg5.range(7, 4) = logic_fmul4(temp_reg1.range(7, 4)) ^ temp_reg2.range(7, 4) ^ logic_fmul2(temp_reg3.range(7, 4)) ^ logic_fmul2(temp_reg4.range(7, 4));
                    temp_reg5.range(3, 0) = logic_fmul4(temp_reg1.range(3, 0)) ^ temp_reg2.range(3, 0) ^ logic_fmul2(temp_reg3.range(3, 0)) ^ logic_fmul2(temp_reg4.range(3, 0));

                    staten_shared_next(state_shared_next, temp_reg5, 3, 0);

                    break;

                case CMD_MIXCOLROTATE:
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 3, 3);

                    break;

                case CMD_BACK_SHARE:
                    temp_reg1 = staten_shared(state_shared, 0, 0);
                    staten_next(state_next, temp_reg1.range(7, 4) ^ temp_reg1.range(3, 0), 3, 3);

                    staten_next(state_next, staten(state, 3, 3), 3, 2);
                    staten_next(state_next, staten(state, 3, 2), 3, 1);
                    staten_next(state_next, staten(state, 3, 1), 3, 0);
                    staten_next(state_next, staten(state, 3, 0), 2, 3);
                    staten_next(state_next, staten(state, 2, 3), 2, 2);
                    staten_next(state_next, staten(state, 2, 2), 2, 1);
                    staten_next(state_next, staten(state, 2, 1), 2, 0);
                    staten_next(state_next, staten(state, 2, 0), 1, 3);
                    staten_next(state_next, staten(state, 1, 3), 1, 2);
                    staten_next(state_next, staten(state, 1, 2), 1, 1);
                    staten_next(state_next, staten(state, 1, 1), 1, 0);
                    staten_next(state_next, staten(state, 1, 0), 0, 3);
                    staten_next(state_next, staten(state, 0, 3), 0, 2);
                    staten_next(state_next, staten(state, 0, 2), 0, 1);
                    staten_next(state_next, staten(state, 0, 1), 0, 0);

                    staten_shared_next(state_shared_next, 0, 3, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 3), 3, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 2), 3, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 1), 3, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 3, 0), 2, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 3), 2, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 2), 2, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 1), 2, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 2, 0), 1, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 3), 1, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 2), 1, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 1), 1, 0);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 1, 0), 0, 3);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 3), 0, 2);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 2), 0, 1);
                    staten_shared_next(state_shared_next, staten_shared(state_shared, 0, 1), 0, 0);

                    break;
            }
        ctlstate = ctlstate_next;
        bcount = bcount_next;
        rcount = rcount_next;
        scount = scount_next;
        keycount = keycount_next;
        state = state_next;
        state_shared = state_shared_next;
        key = key_next;
        key_shared = key_shared_next;
        rc = rc_next;
        done = (ctlstate == STATE_IDLE);
        dataq = state_next;
    }



	private:
    ap_uint<8> staten(ap_uint<64> state, int i, int j) {
    	        return state.range((15 - (j + 4 * i)) * 4 + 3, (15 - (j + 4 * i)) * 4);
    	    }

    	    void staten_next(ap_uint<64>& state_next, ap_uint<8> value, int i, int j) {
    	        state_next.range((15 - (j + 4 * i)) * 4 + 3, (15 - (j + 4 * i)) * 4) = value;
    	    }

    	    ap_uint<8> staten_shared(ap_uint<128> state_shared, int i, int j) {
    	        return state_shared.range((15 - (j + 4 * i)) * 8 + 7, (15 - (j + 4 * i)) * 8);
    	    }

    	    void staten_shared_next(ap_uint<128>& state_shared_next, ap_uint<8> value, int i, int j) {
    	        state_shared_next.range((15 - (j + 4 * i)) * 8 + 7, (15 - (j + 4 * i)) * 8) = value;
    	    }

    	    ap_uint<8> keyn(ap_uint<128> key, int i, int j, int k) {
    	        return key.range((31 - (k + 4 * j + 16 * i)) * 4 + 3, (31 - (k + 4 * j + 16 * i)) * 4);
    	    }

    	    void keyn_next(ap_uint<128>& key_next, ap_uint<8> value, int i, int j, int k) {
    	        key_next.range((31 - (k + 4 * j + 16 * i)) * 4 + 3, (31 - (k + 4 * j + 16 * i)) * 4) = value;
    	    }

    	    ap_uint<8> keyn_shared(ap_uint<256> key_shared, int i, int j, int k) {
    	        return key_shared.range((31 - (k + 4 * j + 16 * i)) * 8 + 7, (31 - (k + 4 * j + 16 * i)) * 8);
    	    }

    	    void keyn_shared_next(ap_uint<256>& key_shared_next, ap_uint<8> value, int i, int j, int k) {
    	        key_shared_next.range((31 - (k + 4 * j + 16 * i)) * 8 + 7, (31 - (k + 4 * j + 16 * i)) * 8) = value;
    	    }

    	    inline ap_uint<8> logic_round(ap_uint<8> d, ap_uint<8> k) {
    	        return d ^ k;
    	    }

    	    inline ap_uint<8> logic_addconst_decode(ap_uint<4> d, ap_uint<8> mask, ap_uint<6> rc) {
    	        switch (d) {
    	            case 0x0: return (8 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x1: return (rc.range(5, 3) ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x2: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x3: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x4: return (9 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x5: return (rc.range(2, 0) ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x6: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x7: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x8: return (2 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0x9: return (rc.range(5, 3) ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xA: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xB: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xC: return (3 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xD: return (rc.range(2, 0) ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xE: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            case 0xF: return (0 ^ mask.range(3, 0), mask.range(3, 0));
    	            default: return 0;
    	        }
    	    }

    	    inline ap_uint<4> logic_fmul2(ap_uint<4> d) {
    	        return (d.range(2, 0), d[3] ^ d[0]);
    	    }

    	    inline ap_uint<4> logic_fmul4(ap_uint<4> d) {
    	        return logic_fmul2(logic_fmul2(d));
    	    }
};

ap_uint<64> led_serial_top(ap_uint<128> keyi, ap_uint<64> datai) {
    LEDSerial led_serial;

    led_serial.keyi = keyi;
    led_serial.datai = datai;

    led_serial_top_label0:while (!led_serial.done) {
        led_serial.update();
    }

    return led_serial.dataq;
}
