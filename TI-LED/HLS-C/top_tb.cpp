#include "led_top.hpp"
#include <iostream>

int main() {
    ap_uint<128> keyi = 0x29cdbaabf2fbe3467cc254f81be8e78d;
    ap_uint<64> datai = 0x67c6697351ff4aec;

    int cycle_count = 0;
    LEDSerial led_serial;
    led_serial.keyi = keyi;
    led_serial.datai = datai;

    ap_uint<4> previous_scount = led_serial.scount;
    ap_uint<5> previous_ctlstate = led_serial.ctlstate;
    ap_uint<4> previous_rcount = led_serial.rcount;
    bool previous_sbox_done = led_serial.sbox.done;
    int previous_sbox_ctlstate = static_cast<int>(led_serial.sbox.ctlstate);
    ap_uint<64> previous_state = led_serial.state;
    int previous_cmd = led_serial.cmd;

    while (!led_serial.done) {
        led_serial.update();
        cycle_count++;

        if (led_serial.scount != previous_scount) {
            std::cout << "scount changed to " << static_cast<int>(led_serial.scount) << " at cycle " << cycle_count << std::endl;
            previous_scount = led_serial.scount;
        }
//
        if (led_serial.ctlstate != previous_ctlstate) {
            std::cout << "ctlstate changed from "<<static_cast<int>(previous_ctlstate)<<"to " << static_cast<int>(led_serial.ctlstate) << " at cycle " << cycle_count << std::endl;
            previous_ctlstate = led_serial.ctlstate;
        }
//
        if (led_serial.rcount != previous_rcount) {
            std::cout << "rcount changed to " << static_cast<int>(led_serial.rcount) << " at cycle " << cycle_count << std::endl;
            previous_rcount = led_serial.rcount;
        }
//
//        bool current_sbox_done = led_serial.sbox.done;
//                if (current_sbox_done != previous_sbox_done) {
//                    std::cout << "sbox done changed to " << static_cast<int>(current_sbox_done) << " at cycle " << cycle_count << std::endl;
//                    previous_sbox_done = current_sbox_done;
//                }
//        if (static_cast<int>(led_serial.sbox.ctlstate) != previous_sbox_ctlstate) {
//                            std::cout << "sbox ctlstate changed to " << static_cast<int>(led_serial.sbox.ctlstate) << " at cycle " << cycle_count << std::endl;
//                            previous_sbox_ctlstate = static_cast<int>(led_serial.sbox.ctlstate);
//                        }
//

        if (led_serial.cmd != previous_cmd) {
            std::cout << "cmd changed to " << static_cast<int>(led_serial.cmd) << " at cycle " << cycle_count << std::endl;
            previous_cmd = led_serial.cmd;
        }

        if (led_serial.state != previous_state) {
                    std::cout << "state changed to " << led_serial.state.to_uint64() << " at cycle " << cycle_count << std::endl;
                    previous_state = led_serial.state;
                }

                if (cycle_count == 500){
                	break;
                }
  }

    ap_uint<64> result = led_serial.dataq;

    std::cout << "Result: " << std::hex << result << std::endl;
    std::cout << "Number of cycles: " << cycle_count << std::endl;

    return 0;
}
