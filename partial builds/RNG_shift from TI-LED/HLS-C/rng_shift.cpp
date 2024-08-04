#include <ap_int.h>
#include <ctime>

// Function to generate an 8-bit random number using a similar approach to the provided Verilog code
ap_uint<8> rng_function(bool vrst, bool rst, bool clk, bool rd) {
    static ap_uint<32> out_tmp;
    static ap_uint<32> tmp0;
    static ap_uint<32> tmp1;
    static ap_uint<32> tmp2;
    static ap_uint<32> tmp3;

    static ap_uint<32> tmp0_reg;
    static ap_uint<32> tmp1_reg;
    static ap_uint<32> tmp2_reg;

    static ap_uint<3> cnt;
    static bool cnt_en;
    static bool cnt_rst;

    const ap_uint<32> seed = 0x8e20a6e5;

    ap_uint<8> rng_out = out_tmp(7, 0);

    if (!vrst) {
        tmp0_reg = seed;
        tmp1_reg = 0;
        tmp2_reg = 0;
        out_tmp = 0;
        cnt_en = false;
        cnt = 0;
    } else if (rst) {
        tmp0_reg = tmp0_reg;
        out_tmp = out_tmp;
        cnt_en = false;
        cnt_rst = false;
        cnt = 0;
    } else {
        tmp1 = tmp0_reg ^ (tmp0_reg << 13);
        tmp2 = tmp1 ^ (tmp1 >> 17);
        tmp3 = tmp2 ^ (tmp2 << 5);

        if (rd) {
            cnt = cnt + 1;
            if (cnt == 3) {
                out_tmp = tmp3;
            }
            if (cnt == 2) {
                tmp0_reg = tmp3;
            }
            if (cnt == 3) {
                cnt = 0;
            }
            if (cnt < 3) {
                out_tmp = out_tmp >> 8;
            }
        } else {
            cnt = cnt;
            out_tmp = tmp3;
        }
    }

    return rng_out;
}

// Top-level function
ap_uint<8> top(bool vrst, bool rst, bool clk, bool rd) {
    return rng_function(vrst, rst, clk, rd);
}
