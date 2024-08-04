// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module led_serial_top_keyn_shared (
        ap_ready,
        key_shared,
        i,
        j,
        k,
        ap_return
);


output   ap_ready;
input  [255:0] key_shared;
input  [0:0] i;
input  [1:0] j;
input  [1:0] k;
output  [7:0] ap_return;

wire   [3:0] shl_ln_fu_56_p3;
wire   [4:0] shl_ln778_1_fu_68_p3;
wire   [4:0] xor_ln778_fu_76_p2;
wire   [4:0] zext_ln778_fu_64_p1;
wire   [4:0] sub_ln778_fu_82_p2;
wire   [4:0] k_cast_fu_52_p1;
wire   [4:0] sub_ln778_1_fu_88_p2;
wire   [7:0] shl_ln778_2_fu_94_p3;
wire   [255:0] zext_ln628_fu_102_p1;
wire   [255:0] lshr_ln628_fu_106_p2;

assign ap_ready = 1'b1;

assign k_cast_fu_52_p1 = k;

assign lshr_ln628_fu_106_p2 = key_shared >> zext_ln628_fu_102_p1;

assign shl_ln778_1_fu_68_p3 = {{i}, {4'd0}};

assign shl_ln778_2_fu_94_p3 = {{sub_ln778_1_fu_88_p2}, {3'd0}};

assign shl_ln_fu_56_p3 = {{j}, {2'd0}};

assign sub_ln778_1_fu_88_p2 = (sub_ln778_fu_82_p2 - k_cast_fu_52_p1);

assign sub_ln778_fu_82_p2 = (xor_ln778_fu_76_p2 - zext_ln778_fu_64_p1);

assign xor_ln778_fu_76_p2 = (shl_ln778_1_fu_68_p3 ^ 5'd31);

assign zext_ln628_fu_102_p1 = shl_ln778_2_fu_94_p3;

assign zext_ln778_fu_64_p1 = shl_ln_fu_56_p3;

assign ap_return = lshr_ln628_fu_106_p2[7:0];

endmodule //led_serial_top_keyn_shared
