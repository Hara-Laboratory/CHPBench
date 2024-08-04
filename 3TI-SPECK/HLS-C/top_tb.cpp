#include <iostream>
#include <ap_int.h>
#include "top.hpp"

int main() {
    // Test input
    ap_uint<768> test_input = ap_uint<768>("0x6c617669757165207469206564616d200f0e0d0c0b0a090807060504030201006c617669757165207469206564616d200f0e0d0c0b0a090807060504030201006c617669757165207469206564616d200f0e0d0c0b0a09080706050403020100");
    ap_uint<128> result;

    result = speck_toplevel(test_input);

    // Print the result
    std::cout << "Cipher Output: " << std::hex << result << std::endl;

    return 0;
}
