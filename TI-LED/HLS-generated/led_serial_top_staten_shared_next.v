// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module led_serial_top_staten_shared_next (
        ap_ready,
        state_shared_next_read,
        value_r,
        i,
        j,
        ap_return
);


output   ap_ready;
input  [127:0] state_shared_next_read;
input  [7:0] value_r;
input  [1:0] i;
input  [1:0] j;
output  [127:0] ap_return;

wire   [3:0] shl_ln_fu_56_p3;
wire   [3:0] xor_ln766_fu_64_p2;
wire   [3:0] j_cast_fu_52_p1;
wire   [3:0] sub_ln766_fu_70_p2;
wire   [6:0] shl_ln766_1_fu_76_p3;
wire   [127:0] zext_ln368_fu_84_p1;
wire   [127:0] shl_ln368_fu_88_p2;
wire   [127:0] xor_ln368_fu_94_p2;
wire   [127:0] zext_ln368_1_fu_106_p1;
wire   [127:0] and_ln368_fu_100_p2;
wire   [127:0] shl_ln368_1_fu_110_p2;

assign and_ln368_fu_100_p2 = (xor_ln368_fu_94_p2 & state_shared_next_read);

assign ap_ready = 1'b1;

assign j_cast_fu_52_p1 = j;

assign shl_ln368_1_fu_110_p2 = zext_ln368_1_fu_106_p1 << zext_ln368_fu_84_p1;

assign shl_ln368_fu_88_p2 = 128'd255 << zext_ln368_fu_84_p1;

assign shl_ln766_1_fu_76_p3 = {{sub_ln766_fu_70_p2}, {3'd0}};

assign shl_ln_fu_56_p3 = {{i}, {2'd0}};

assign sub_ln766_fu_70_p2 = (xor_ln766_fu_64_p2 - j_cast_fu_52_p1);

assign xor_ln368_fu_94_p2 = (shl_ln368_fu_88_p2 ^ 128'd340282366920938463463374607431768211455);

assign xor_ln766_fu_64_p2 = (shl_ln_fu_56_p3 ^ 4'd15);

assign zext_ln368_1_fu_106_p1 = value_r;

assign zext_ln368_fu_84_p1 = shl_ln766_1_fu_76_p3;

assign ap_return = (shl_ln368_1_fu_110_p2 | and_ln368_fu_100_p2);

endmodule //led_serial_top_staten_shared_next
