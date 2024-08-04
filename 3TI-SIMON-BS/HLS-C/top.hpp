#ifndef TI_SIMON_TOP_MODULE_HPP
#define TI_SIMON_TOP_MODULE_HPP

#include <ap_int.h>
#include "TI_Simon_Core.hpp"
// Constants
const int DATA_INPUT_WIDTH = 128 * 6;
const int DATA_OUTPUT_WIDTH = 128;
const int ROUND_COUNT = 68;

// Function prototype
ap_uint<128> TI_Simon_TopModule(ap_uint<DATA_INPUT_WIDTH> Din);

#endif // TI_SIMON_TOP_MODULE_HPP
