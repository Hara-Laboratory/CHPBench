// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module led_serial_top_keyn (
        ap_ready,
        key,
        i,
        j,
        k,
        ap_return
);


output   ap_ready;
input  [127:0] key;
input  [0:0] i;
input  [1:0] j;
input  [1:0] k;
output  [3:0] ap_return;

wire   [3:0] shl_ln_fu_54_p3;
wire   [4:0] shl_ln770_1_fu_66_p3;
wire   [4:0] xor_ln770_fu_74_p2;
wire   [4:0] zext_ln770_fu_62_p1;
wire   [4:0] sub_ln770_fu_80_p2;
wire   [4:0] k_cast_fu_50_p1;
wire   [4:0] sub_ln770_1_fu_86_p2;
wire   [6:0] shl_ln770_2_fu_92_p3;
wire   [127:0] zext_ln628_fu_100_p1;
wire   [127:0] lshr_ln628_fu_104_p2;

assign ap_ready = 1'b1;

assign k_cast_fu_50_p1 = k;

assign lshr_ln628_fu_104_p2 = key >> zext_ln628_fu_100_p1;

assign shl_ln770_1_fu_66_p3 = {{i}, {4'd0}};

assign shl_ln770_2_fu_92_p3 = {{sub_ln770_1_fu_86_p2}, {2'd0}};

assign shl_ln_fu_54_p3 = {{j}, {2'd0}};

assign sub_ln770_1_fu_86_p2 = (sub_ln770_fu_80_p2 - k_cast_fu_50_p1);

assign sub_ln770_fu_80_p2 = (xor_ln770_fu_74_p2 - zext_ln770_fu_62_p1);

assign xor_ln770_fu_74_p2 = (shl_ln770_1_fu_66_p3 ^ 5'd31);

assign zext_ln628_fu_100_p1 = shl_ln770_2_fu_92_p3;

assign zext_ln770_fu_62_p1 = shl_ln_fu_54_p3;

assign ap_return = lshr_ln628_fu_104_p2[3:0];

endmodule //led_serial_top_keyn
