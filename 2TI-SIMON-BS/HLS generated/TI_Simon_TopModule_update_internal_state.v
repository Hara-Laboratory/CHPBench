// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module TI_Simon_TopModule_update_internal_state (
        ap_ready,
        p_read,
        p_read1,
        p_read2,
        p_read5,
        p_read6,
        p_read7,
        p_read8,
        p_read9,
        p_read4,
        p_read10,
        this_shift_in1_read,
        this_shift_in2_read,
        p_read20,
        p_read21,
        p_read22,
        p_read23,
        p_read24,
        p_read25,
        p_read26,
        p_read27,
        p_read28,
        p_read29,
        p_read30,
        p_read31,
        p_read32,
        p_read33,
        p_read34,
        p_read35,
        this_lut_ff_input_read,
        this_fifo_ff_input_read,
        p_read15,
        this_ff_input_read,
        ap_return_0,
        ap_return_1,
        ap_return_2,
        ap_return_3,
        ap_return_4,
        ap_return_5,
        ap_return_6,
        ap_return_7,
        ap_return_8,
        ap_return_9,
        ap_return_10,
        ap_return_11,
        ap_return_12,
        ap_return_13,
        ap_return_14,
        ap_return_15,
        ap_return_16,
        ap_return_17,
        ap_return_18,
        ap_return_19,
        ap_return_20,
        ap_return_21,
        ap_return_22,
        ap_return_23,
        ap_return_24,
        ap_return_25,
        ap_return_26,
        ap_return_27,
        ap_return_28,
        ap_return_29,
        ap_return_30
);


output   ap_ready;
input  [0:0] p_read;
input  [0:0] p_read1;
input  [0:0] p_read2;
input  [0:0] p_read5;
input  [0:0] p_read6;
input  [1:0] p_read7;
input  [0:0] p_read8;
input  [0:0] p_read9;
input  [54:0] p_read4;
input  [63:0] p_read10;
input  [0:0] this_shift_in1_read;
input  [0:0] this_shift_in2_read;
input  [0:0] p_read20;
input  [0:0] p_read21;
input  [0:0] p_read22;
input  [0:0] p_read23;
input  [0:0] p_read24;
input  [0:0] p_read25;
input  [0:0] p_read26;
input  [0:0] p_read27;
input  [0:0] p_read28;
input  [0:0] p_read29;
input  [0:0] p_read30;
input  [0:0] p_read31;
input  [0:0] p_read32;
input  [0:0] p_read33;
input  [0:0] p_read34;
input  [0:0] p_read35;
input  [0:0] this_lut_ff_input_read;
input  [0:0] this_fifo_ff_input_read;
input  [0:0] p_read15;
input  [0:0] this_ff_input_read;
output  [0:0] ap_return_0;
output  [0:0] ap_return_1;
output  [0:0] ap_return_2;
output  [54:0] ap_return_3;
output  [63:0] ap_return_4;
output  [0:0] ap_return_5;
output  [0:0] ap_return_6;
output  [0:0] ap_return_7;
output  [0:0] ap_return_8;
output  [0:0] ap_return_9;
output  [0:0] ap_return_10;
output  [0:0] ap_return_11;
output  [0:0] ap_return_12;
output  [0:0] ap_return_13;
output  [0:0] ap_return_14;
output  [0:0] ap_return_15;
output  [0:0] ap_return_16;
output  [0:0] ap_return_17;
output  [0:0] ap_return_18;
output  [0:0] ap_return_19;
output  [0:0] ap_return_20;
output  [0:0] ap_return_21;
output  [0:0] ap_return_22;
output  [0:0] ap_return_23;
output  [0:0] ap_return_24;
output  [0:0] ap_return_25;
output  [0:0] ap_return_26;
output  [0:0] ap_return_27;
output  [0:0] ap_return_28;
output  [0:0] ap_return_29;
output  [0:0] ap_return_30;

wire   [53:0] tmp_fu_286_p4;
wire   [54:0] p_Result_s_fu_296_p3;
wire   [54:0] p_Val2_s_fu_304_p3;
wire   [62:0] tmp_s_fu_316_p4;
wire   [63:0] p_Result_2_fu_326_p3;
wire   [63:0] p_Val2_1_fu_334_p3;
wire   [0:0] select_ln50_fu_346_p3;
wire   [0:0] select_ln50_8_fu_410_p3;
wire   [0:0] icmp_ln94_fu_498_p2;
wire   [0:0] icmp_ln94_2_fu_510_p2;
wire   [0:0] or_ln94_fu_516_p2;
wire   [0:0] icmp_ln94_1_fu_504_p2;
wire   [0:0] p_Result_1_fu_312_p1;
wire   [0:0] select_ln50_1_fu_354_p3;
wire   [0:0] select_ln50_15_fu_466_p3;
wire   [0:0] select_ln50_7_fu_402_p3;
wire   [0:0] select_ln50_9_fu_418_p3;
wire   [0:0] or_ln94_1_fu_522_p2;
wire   [0:0] select_ln94_fu_528_p3;
wire   [0:0] select_ln50_17_fu_482_p3;
wire   [0:0] select_ln50_16_fu_474_p3;
wire   [0:0] this_lut_ff55_0_this_fifo_ff55_0_fu_544_p3;
wire   [0:0] p_Result_3_fu_342_p1;
wire   [0:0] select_ln50_14_fu_458_p3;
wire   [0:0] select_ln50_13_fu_450_p3;
wire   [0:0] select_ln50_12_fu_442_p3;
wire   [0:0] select_ln50_11_fu_434_p3;
wire   [0:0] select_ln50_10_fu_426_p3;
wire   [0:0] select_ln50_2_fu_362_p3;
wire   [0:0] select_ln50_3_fu_370_p3;
wire   [0:0] select_ln50_4_fu_378_p3;
wire   [0:0] select_ln50_5_fu_386_p3;
wire   [0:0] select_ln50_6_fu_394_p3;
wire   [0:0] this_lut_ff62_0_this_fifo_ff62_0_fu_536_p3;
wire   [0:0] this_lut_ff56_0_this_fifo_ff56_0_fu_552_p3;
wire   [0:0] this_fifo_ff55_0_this_lut_ff55_0_fu_490_p3;
wire   [0:0] select_ln143_fu_560_p3;

assign ap_ready = 1'b1;

assign or_ln94_1_fu_522_p2 = (or_ln94_fu_516_p2 | icmp_ln94_1_fu_504_p2);

assign or_ln94_fu_516_p2 = (icmp_ln94_fu_498_p2 | icmp_ln94_2_fu_510_p2);

assign p_Result_1_fu_312_p1 = p_Val2_s_fu_304_p3[0:0];

assign p_Result_2_fu_326_p3 = {{this_shift_in2_read}, {tmp_s_fu_316_p4}};

assign p_Result_3_fu_342_p1 = p_Val2_1_fu_334_p3[0:0];

assign p_Result_s_fu_296_p3 = {{this_shift_in1_read}, {tmp_fu_286_p4}};

assign p_Val2_1_fu_334_p3 = ((p_read9[0:0] == 1'b1) ? p_Result_2_fu_326_p3 : p_read10);

assign p_Val2_s_fu_304_p3 = ((p_read8[0:0] == 1'b1) ? p_Result_s_fu_296_p3 : p_read4);

assign select_ln143_fu_560_p3 = ((or_ln94_1_fu_522_p2[0:0] == 1'b1) ? select_ln94_fu_528_p3 : p_read15);

assign select_ln50_10_fu_426_p3 = ((p_read8[0:0] == 1'b1) ? p_read24 : p_read25);

assign select_ln50_11_fu_434_p3 = ((p_read8[0:0] == 1'b1) ? p_read23 : p_read24);

assign select_ln50_12_fu_442_p3 = ((p_read8[0:0] == 1'b1) ? p_read22 : p_read23);

assign select_ln50_13_fu_450_p3 = ((p_read8[0:0] == 1'b1) ? p_read21 : p_read22);

assign select_ln50_14_fu_458_p3 = ((p_read8[0:0] == 1'b1) ? p_read20 : p_read21);

assign select_ln50_15_fu_466_p3 = ((p_read8[0:0] == 1'b1) ? this_fifo_ff_input_read : p_read20);

assign select_ln50_16_fu_474_p3 = ((p_read8[0:0] == 1'b1) ? p_read33 : p_read1);

assign select_ln50_17_fu_482_p3 = ((p_read8[0:0] == 1'b1) ? p_read34 : p_read);

assign select_ln50_1_fu_354_p3 = ((p_read8[0:0] == 1'b1) ? this_lut_ff_input_read : p_read28);

assign select_ln50_2_fu_362_p3 = ((p_read8[0:0] == 1'b1) ? this_fifo_ff_input_read : p_read29);

assign select_ln50_3_fu_370_p3 = ((p_read8[0:0] == 1'b1) ? p_read29 : p_read30);

assign select_ln50_4_fu_378_p3 = ((p_read8[0:0] == 1'b1) ? p_read30 : p_read31);

assign select_ln50_5_fu_386_p3 = ((p_read8[0:0] == 1'b1) ? p_read31 : p_read32);

assign select_ln50_6_fu_394_p3 = ((p_read8[0:0] == 1'b1) ? p_read32 : p_read33);

assign select_ln50_7_fu_402_p3 = ((p_read8[0:0] == 1'b1) ? p_read33 : p_read34);

assign select_ln50_8_fu_410_p3 = ((p_read8[0:0] == 1'b1) ? p_read34 : p_read35);

assign select_ln50_9_fu_418_p3 = ((p_read8[0:0] == 1'b1) ? p_read25 : p_read26);

assign select_ln50_fu_346_p3 = ((p_read8[0:0] == 1'b1) ? p_read26 : p_read27);

assign select_ln94_fu_528_p3 = ((icmp_ln94_2_fu_510_p2[0:0] == 1'b1) ? p_read2 : p_Result_1_fu_312_p1);

assign this_fifo_ff55_0_this_lut_ff55_0_fu_490_p3 = ((p_read5[0:0] == 1'b1) ? select_ln50_fu_346_p3 : select_ln50_8_fu_410_p3);

assign this_lut_ff55_0_this_fifo_ff55_0_fu_544_p3 = ((p_read6[0:0] == 1'b1) ? select_ln50_8_fu_410_p3 : select_ln50_fu_346_p3);

assign this_lut_ff56_0_this_fifo_ff56_0_fu_552_p3 = ((p_read6[0:0] == 1'b1) ? select_ln50_7_fu_402_p3 : select_ln50_9_fu_418_p3);

assign this_lut_ff62_0_this_fifo_ff62_0_fu_536_p3 = ((p_read6[0:0] == 1'b1) ? select_ln50_1_fu_354_p3 : select_ln50_15_fu_466_p3);

assign tmp_fu_286_p4 = {{p_read4[54:1]}};

assign tmp_s_fu_316_p4 = {{p_read10[63:1]}};

assign ap_return_0 = select_ln50_17_fu_482_p3;

assign ap_return_1 = select_ln50_16_fu_474_p3;

assign ap_return_10 = select_ln50_11_fu_434_p3;

assign ap_return_11 = select_ln50_10_fu_426_p3;

assign ap_return_12 = select_ln50_9_fu_418_p3;

assign ap_return_13 = select_ln50_fu_346_p3;

assign ap_return_14 = select_ln50_1_fu_354_p3;

assign ap_return_15 = select_ln50_2_fu_362_p3;

assign ap_return_16 = select_ln50_3_fu_370_p3;

assign ap_return_17 = select_ln50_4_fu_378_p3;

assign ap_return_18 = select_ln50_5_fu_386_p3;

assign ap_return_19 = select_ln50_6_fu_394_p3;

assign ap_return_2 = this_lut_ff55_0_this_fifo_ff55_0_fu_544_p3;

assign ap_return_20 = select_ln50_7_fu_402_p3;

assign ap_return_21 = select_ln50_8_fu_410_p3;

assign ap_return_22 = this_ff_input_read;

assign ap_return_23 = this_lut_ff62_0_this_fifo_ff62_0_fu_536_p3;

assign ap_return_24 = this_lut_ff56_0_this_fifo_ff56_0_fu_552_p3;

assign ap_return_25 = this_lut_ff62_0_this_fifo_ff62_0_fu_536_p3;

assign ap_return_26 = this_fifo_ff55_0_this_lut_ff55_0_fu_490_p3;

assign ap_return_27 = p_Result_1_fu_312_p1;

assign ap_return_28 = this_ff_input_read;

assign ap_return_29 = this_ff_input_read;

assign ap_return_3 = p_Val2_s_fu_304_p3;

assign ap_return_30 = select_ln143_fu_560_p3;

assign ap_return_4 = p_Val2_1_fu_334_p3;

assign ap_return_5 = p_Result_3_fu_342_p1;

assign ap_return_6 = select_ln50_15_fu_466_p3;

assign ap_return_7 = select_ln50_14_fu_458_p3;

assign ap_return_8 = select_ln50_13_fu_450_p3;

assign ap_return_9 = select_ln50_12_fu_442_p3;

assign icmp_ln94_1_fu_504_p2 = ((p_read7 == 2'd1) ? 1'b1 : 1'b0);

assign icmp_ln94_2_fu_510_p2 = ((p_read7 == 2'd0) ? 1'b1 : 1'b0);

assign icmp_ln94_fu_498_p2 = ((p_read7 == 2'd2) ? 1'b1 : 1'b0);

endmodule //TI_Simon_TopModule_update_internal_state
