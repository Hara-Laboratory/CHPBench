#include <ap_int.h>
#include "TI_Simon_Core.hpp"

int main() {
    // Instantiate the Simon Core
    TI_Simon_Core simon_core;

    std::string binary = "0110001101110011011001010110010000100000011100110111001001100101011011000110110001100101011101100110000101110010011101000010000000001111000011100000110100001100000010110000101000001001000010000000011100000110000001010000010000000011000000100000000100000000";
        int pka[256];
        for (int i = 0; i < 256; ++i) {
            pka[i] = binary[255-i] - '0';
        }
        int pkb[256]={0};

    // Reset the Simon Core
    simon_core.reset();

    for(int i = 0; i <= 255; i++) {
        if(i < 128) {
            simon_core.data_rdy = 2;
            simon_core.data_ina = pka[i];
            simon_core.data_inb = pkb[i];
        } else {
            simon_core.data_rdy = 1;
            simon_core.data_ina = pka[i];
            simon_core.data_inb = pkb[i];
        }

        // Call the tick function
        simon_core.tick();


        // For example, you might print simon_core.cipher_outa, simon_core.cipher_outb, simon_core.round_counter, simon_core.Done, simon_core.Trig values here.
    }

    // Set data_rdy to 3 and call Simon Core function once more
    simon_core.data_rdy = 3;
    while(true) {
    	simon_core.tick();
    	std::cout << "Cipher out a: " << simon_core.cipher_outa.to_uint() << std::endl;
    	std::cout << "Cipher out b: " << simon_core.cipher_outb.to_uint() << std::endl;
    	printf("\n");

    }

    return 0;
}
