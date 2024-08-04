#include <ap_int.h>
#include "speck_core.hpp"

ap_uint<128> speck_toplevel(ap_uint<768> d_in) {
    // Internal signals
    ap_uint<1> data_ina, data_inb, data_inc;
    ap_uint<1> k_data_ina, k_data_inb, k_data_inc;
    ap_uint<1> carry_init_a = 1, carry_init_b = 0, carry_init_c = 1;
    ap_uint<1> we, Start;
    ap_uint<2> state = 0;
    ap_uint<8> cycle = 0; // 8-bit for cycle count
    ap_uint<128> cipher_out = 0;

    core speck_core;
    speck_core.carry_init_a = carry_init_a;
    speck_core.carry_init_b = carry_init_b;
    speck_core.carry_init_c = carry_init_c;

    // State machine
    int clk_count=0;
    while (state != 3) {
    	clk_count++;
        switch (state) {
            case 0: // LOAD_DATA
                if (cycle < 128) {
                	Start = 1;
                    data_ina = d_in.bit(cycle + 512);
                    data_inb = d_in.bit(cycle + 256);
                    data_inc = d_in.bit(cycle );
                    k_data_ina = d_in.bit(cycle + 384);
                    k_data_inb = d_in.bit(cycle + 128);
                    k_data_inc = d_in.bit(cycle + 640);
                    speck_core.data_ina = data_ina;
                    speck_core.data_inb = data_inb;
                    speck_core.data_inc = data_inc;
                    speck_core.k_data_ina = k_data_ina;
                    speck_core.k_data_inb = k_data_inb;
                    speck_core.k_data_inc = k_data_inc;
                    we = 1;
                    speck_core.we = we;
                    speck_core.Start = Start;
                    speck_core.update();
                    cycle++;
                } else {
                    we = 0;
                    cycle = 0;
                    state = 1;
                }
                break;

            case 1: // ENCRYPTION
                speck_core.we = we;
                speck_core.Start = Start;
                speck_core.update();
                if (!speck_core.rndlessthan32) {
                    cycle = 0;
                    state = 2;
                }
                break;

            case 2: // XOR_OUTPUT
                if (cycle < 64) {
                    speck_core.update();
                    cipher_out.range(cycle*2+1, cycle*2) = speck_core.cipher_out1 ^ speck_core.cipher_out2 ^ speck_core.cipher_out3;
                    cycle++;
                } else {
                    state = 3; // Done
                }
                break;
        }
    }

    return cipher_out;
}

