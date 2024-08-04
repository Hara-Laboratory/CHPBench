#include <ap_int.h>
#include <array>

// LUT Datapath class definition
class LUTDatapath {
public:
    void process(ap_uint<1> clk, ap_uint<1>& out, ap_uint<1> shift_out2, ap_uint<1> key_in,
                 ap_uint<1> lut_rol2, ap_uint<1> lut_rol1, ap_uint<1> lut_rol8,
                 ap_uint<1> lut_rol1_shifted, ap_uint<1> lut_rol8_ext) {

        if (clk == 1) {
            intreg = shift_out2 ^ lut_rol2 ^ (lut_rol1 & lut_rol8);
        }

        out = key_in ^ (lut_rol1_shifted & lut_rol8_ext) ^ intreg;
    }

private:
    ap_uint<1> intreg;
};

// DatapathShare class definition
class DatapathShare {
public:
    // Constructor to initialize variables
    DatapathShare() : shifter1(0), shifter2(0), ff63(0), lut_rol1(0), lut_rol1_shifted(0), lut_rol2(0), lut_rol8(0), lut_rol8_ext(0) {
        fifo_ff.fill(0);
        lut_ff.fill(0);
    }

    ap_uint<1> process(ap_uint<1> clk, ap_uint<1> data_in, ap_uint<1> key_in, ap_uint<1> shifter_enable1, ap_uint<1> shifter_enable2,
                       ap_uint<1> lut_rol8_shifted_ext, ap_uint<1> s1, ap_uint<1> s2, ap_uint<2> s3) {

        // Shift register
        if (shifter_enable1) {
            shifter1 = (shifter1 >> 1) | (shift_in1 << 54);
        }
        ap_uint<1> shift_out1 = shifter1[0];

        if (shifter_enable2) {
            shifter2 = (shifter2 >> 1) | (shift_in2 << 63);
        }
        ap_uint<1> shift_out2 = shifter2[0];

        // FIFO logic
        if (shifter_enable1) {
            for (int i = 62; i >= 55; --i) {
                fifo_ff[i] = (i == 55) ? fifo_ff_input : fifo_ff[i-1];
            }
        }

        // LUT FF logic
        if (shifter_enable1) {
            for (int i = 62; i >= 55; --i) {
                lut_ff[i] = (i == 55) ? lut_ff_input : lut_ff[i-1];
            }
        }

        // Update inputs
        shift_in2 = shift_out1;
        shift_in1 = (s1 == 0) ? lut_ff[55] : fifo_ff[55];

        switch (s3) {
            case 0:
                ff_input = data_in;
                break;
            case 1:
                ff_input = shift_out1;
                break;
            case 2:
                ff_input = lut_out;
                break;
            default:
                ff_input = ff_input;
                break;
        }

        if (shifter_enable1)
                {
                    lut_ff[62] = lut_ff_input;
                    lut_ff[61] = lut_ff[62];
                    lut_ff[60] = lut_ff[61];
                    lut_ff[59] = lut_ff[60];
                    lut_ff[58] = lut_ff[59];
                    lut_ff[57] = lut_ff[58];
                    lut_ff[56]= lut_ff[57];
                    lut_ff[55] = lut_ff[56];
                }

        fifo_ff_input = (s2 == 0) ? ff63 : lut_out;
        lut_ff_input = (s2 == 1) ? ff63 : lut_out;

        lut_rol1 = ff63;
        lut_rol1_shifted = (s2 == 0) ? fifo_ff[62] : lut_ff[62];
        lut_rol8_shifted_out = (s2 == 0) ? fifo_ff[55] : lut_ff[55];
        lut_rol2 = (s2 == 0) ? fifo_ff[62] : lut_ff[62];
        lut_rol8 = (s2 == 0) ? fifo_ff[56] : lut_ff[56];
        lut_rol8_ext = lut_rol8_shifted_ext;

        // LUT datapath processing
        LUTDatapath lut_datapath;
        lut_datapath.process(clk, lut_out, shift_out2, key_in, lut_rol2, lut_rol1, lut_rol8, lut_rol1_shifted, lut_rol8_ext);

        ff63 = ff_input;
        return lut_out;
    }

private:
    ap_uint<55> shifter1;
    ap_uint<64> shifter2;
    ap_uint<1> shift_in1, shift_in2;
    std::array<ap_uint<1>, 63> fifo_ff;
    std::array<ap_uint<1>, 63> lut_ff;
    ap_uint<1> ff63;
    ap_uint<1> lut_ff_input, fifo_ff_input, ff_input;
    ap_uint<1> lut_rol1, lut_rol1_shifted, lut_rol2, lut_rol8;
    ap_uint<1> lut_rol8_ext;
    ap_uint<1> lut_out;
    ap_uint<1> lut_rol8_shifted_out;
};

// Top-level function
ap_uint<1> top(ap_uint<1> clk, ap_uint<1> data_in, ap_uint<1> key_in, ap_uint<1> shifter_enable1, ap_uint<1> shifter_enable2,
               ap_uint<1> lut_rol8_shifted_ext, ap_uint<1> s1, ap_uint<1> s2, ap_uint<2> s3) {
    static DatapathShare datapath_share;
    return datapath_share.process(clk, data_in, key_in, shifter_enable1, shifter_enable2, lut_rol8_shifted_ext, s1, s2, s3);
}
