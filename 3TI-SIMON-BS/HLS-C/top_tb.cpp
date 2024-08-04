#include "E:\vitis_project\ti2_simon_new\TI2_Simon_Top.hpp"
#include <iostream>
#include <cstdint>  // for uint64_t

int main() {
    // Inputs
    uint64_t DinA[12] = {0};  // Initialize all elements to 0
    ap_uint<768> Din=0;

    // Outputs (These will be populated inside the top function, but we're just declaring them here for clarity)
    ap_uint<128> Dout;
    bool Dvld;
    bool BSY;
    bool Trig;


    // Setting Din value similar to your Verilog testbench
    // Assuming Din[0] is the least significant 64 bits and Din[11] is the most significant
    DinA[0] = 0x0102030405060708;
    DinA[1] = 0x090a0b0c0d0e0f10;
    DinA[2] = 0x1111121314151617;
    DinA[3] = 0x18191a1b1c1d1e1f;
    DinA[4] = 0x2021222324252627;
    DinA[5] = 0x28292a2b2c2d2e2f;
    DinA[6] = 0x3031323334353637;
    DinA[7] = 0x38393a3b3c3d3e3f;
    DinA[8] = 0x4041424344454647;
    DinA[9] = 0x48494a4b4c4d4e4f;
    DinA[10] = 0x5051525354555657;
    DinA[11] = 0x58595a5b5c5d5e5f;

    for (int i = 0; i < 12; i++) {
            Din.range((i+1)*64 - 1, i*64) = DinA[i];
        }



    Dout = TI_Simon_TopModule(Din);

    // Print the result
    std::cout << "Dout: " << Dout.to_string(16) << std::endl;

    return 0;
}
