// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module top_process_r (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        data_in,
        key_in,
        shifter_enable1,
        lut_rol8_shifted_ext,
        s2,
        s3,
        ap_return
);

parameter    ap_ST_fsm_state1 = 4'd1;
parameter    ap_ST_fsm_state2 = 4'd2;
parameter    ap_ST_fsm_state3 = 4'd4;
parameter    ap_ST_fsm_state4 = 4'd8;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [0:0] data_in;
input  [0:0] key_in;
input  [0:0] shifter_enable1;
input  [0:0] lut_rol8_shifted_ext;
input  [0:0] s2;
input  [1:0] s3;
output  [0:0] ap_return;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[0:0] ap_return;

(* fsm_encoding = "none" *) reg   [3:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [0:0] datapath_share_fifo_ff_input_V;
reg   [5:0] datapath_share_fifo_ff_M_elems_V_address0;
reg    datapath_share_fifo_ff_M_elems_V_ce0;
wire   [0:0] datapath_share_fifo_ff_M_elems_V_q0;
reg   [5:0] datapath_share_fifo_ff_M_elems_V_address1;
reg    datapath_share_fifo_ff_M_elems_V_ce1;
wire   [0:0] datapath_share_fifo_ff_M_elems_V_q1;
reg   [0:0] datapath_share_lut_ff_input_V;
reg   [5:0] datapath_share_lut_ff_M_elems_V_address0;
reg    datapath_share_lut_ff_M_elems_V_ce0;
wire   [0:0] datapath_share_lut_ff_M_elems_V_q0;
reg   [5:0] datapath_share_lut_ff_M_elems_V_address1;
reg    datapath_share_lut_ff_M_elems_V_ce1;
wire   [0:0] datapath_share_lut_ff_M_elems_V_q1;
reg   [0:0] datapath_share_lut_out_V;
reg   [0:0] datapath_share_ff_input_V;
reg   [0:0] datapath_share_ff63_V;
wire   [1:0] s3_read_read_fu_50_p2;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_done;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_idle;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_ready;
wire   [5:0] grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address0;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce0;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_we0;
wire   [0:0] grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_d0;
wire   [5:0] grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address1;
wire    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce1;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_done;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_idle;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_ready;
wire   [5:0] grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address0;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce0;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_we0;
wire   [0:0] grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_d0;
wire   [5:0] grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address1;
wire    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce1;
reg    grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg;
wire    ap_CS_fsm_state2;
reg    grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg;
wire   [0:0] select_ln78_fu_157_p3;
wire    ap_CS_fsm_state4;
wire   [0:0] select_ln79_fu_169_p3;
wire   [0:0] ret_V_fu_217_p2;
reg    ap_block_state2_on_subcall_done;
wire    ap_CS_fsm_state3;
wire   [0:0] lut_rol8_V_fu_188_p3;
wire   [0:0] lut_rol1_shifted_V_fu_181_p3;
wire   [0:0] ret_V_4_fu_201_p2;
wire   [0:0] ret_V_3_fu_195_p2;
wire   [0:0] xor_ln1499_1_fu_211_p2;
wire   [0:0] xor_ln1499_fu_206_p2;
reg   [0:0] ap_return_preg;
reg   [3:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
reg    ap_ST_fsm_state2_blk;
wire    ap_ST_fsm_state3_blk;
wire    ap_ST_fsm_state4_blk;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 4'd1;
#0 datapath_share_fifo_ff_input_V = 1'd0;
#0 datapath_share_lut_ff_input_V = 1'd0;
#0 datapath_share_lut_out_V = 1'd0;
#0 datapath_share_ff_input_V = 1'd0;
#0 datapath_share_ff63_V = 1'd0;
#0 grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg = 1'b0;
#0 grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg = 1'b0;
#0 ap_return_preg = 1'd0;
end

top_process_r_datapath_share_fifo_ff_M_elems_V_RAM_AUTO_1R1W #(
    .DataWidth( 1 ),
    .AddressRange( 63 ),
    .AddressWidth( 6 ))
datapath_share_fifo_ff_M_elems_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(datapath_share_fifo_ff_M_elems_V_address0),
    .ce0(datapath_share_fifo_ff_M_elems_V_ce0),
    .we0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_we0),
    .d0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_d0),
    .q0(datapath_share_fifo_ff_M_elems_V_q0),
    .address1(datapath_share_fifo_ff_M_elems_V_address1),
    .ce1(datapath_share_fifo_ff_M_elems_V_ce1),
    .q1(datapath_share_fifo_ff_M_elems_V_q1)
);

top_process_r_datapath_share_fifo_ff_M_elems_V_RAM_AUTO_1R1W #(
    .DataWidth( 1 ),
    .AddressRange( 63 ),
    .AddressWidth( 6 ))
datapath_share_lut_ff_M_elems_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(datapath_share_lut_ff_M_elems_V_address0),
    .ce0(datapath_share_lut_ff_M_elems_V_ce0),
    .we0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_we0),
    .d0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_d0),
    .q0(datapath_share_lut_ff_M_elems_V_q0),
    .address1(datapath_share_lut_ff_M_elems_V_address1),
    .ce1(datapath_share_lut_ff_M_elems_V_ce1),
    .q1(datapath_share_lut_ff_M_elems_V_q1)
);

top_process_Pipeline_VITIS_LOOP_47_1 grp_process_Pipeline_VITIS_LOOP_47_1_fu_108(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start),
    .ap_done(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_done),
    .ap_idle(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_idle),
    .ap_ready(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_ready),
    .datapath_share_fifo_ff_input_V_load(datapath_share_fifo_ff_input_V),
    .datapath_share_fifo_ff_M_elems_V_address0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address0),
    .datapath_share_fifo_ff_M_elems_V_ce0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce0),
    .datapath_share_fifo_ff_M_elems_V_we0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_we0),
    .datapath_share_fifo_ff_M_elems_V_d0(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_d0),
    .datapath_share_fifo_ff_M_elems_V_address1(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address1),
    .datapath_share_fifo_ff_M_elems_V_ce1(grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce1),
    .datapath_share_fifo_ff_M_elems_V_q1(datapath_share_fifo_ff_M_elems_V_q1)
);

top_process_Pipeline_VITIS_LOOP_54_2 grp_process_Pipeline_VITIS_LOOP_54_2_fu_115(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start),
    .ap_done(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_done),
    .ap_idle(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_idle),
    .ap_ready(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_ready),
    .datapath_share_lut_ff_input_V_load(datapath_share_lut_ff_input_V),
    .datapath_share_lut_ff_M_elems_V_address0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address0),
    .datapath_share_lut_ff_M_elems_V_ce0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce0),
    .datapath_share_lut_ff_M_elems_V_we0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_we0),
    .datapath_share_lut_ff_M_elems_V_d0(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_d0),
    .datapath_share_lut_ff_M_elems_V_address1(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address1),
    .datapath_share_lut_ff_M_elems_V_ce1(grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce1),
    .datapath_share_lut_ff_M_elems_V_q1(datapath_share_lut_ff_M_elems_V_q1)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_return_preg <= 1'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            ap_return_preg <= ret_V_fu_217_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg <= 1'b0;
    end else begin
        if (((ap_start == 1'b1) & (shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
            grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg <= 1'b1;
        end else if ((grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_ready == 1'b1)) begin
            grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg <= 1'b0;
    end else begin
        if (((ap_start == 1'b1) & (shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
            grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg <= 1'b1;
        end else if ((grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_ready == 1'b1)) begin
            grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state2) & (1'b0 == ap_block_state2_on_subcall_done))) begin
        if ((s3_read_read_fu_50_p2 == 2'd0)) begin
            datapath_share_ff_input_V <= data_in;
        end else if ((s3_read_read_fu_50_p2 == 2'd1)) begin
            datapath_share_ff_input_V <= 1'd0;
        end else if ((s3_read_read_fu_50_p2 == 2'd2)) begin
            datapath_share_ff_input_V <= datapath_share_lut_out_V;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        datapath_share_ff63_V <= datapath_share_ff_input_V;
        datapath_share_fifo_ff_input_V <= select_ln78_fu_157_p3;
        datapath_share_lut_ff_input_V <= select_ln79_fu_169_p3;
        datapath_share_lut_out_V <= ret_V_fu_217_p2;
    end
end

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_block_state2_on_subcall_done)) begin
        ap_ST_fsm_state2_blk = 1'b1;
    end else begin
        ap_ST_fsm_state2_blk = 1'b0;
    end
end

assign ap_ST_fsm_state3_blk = 1'b0;

assign ap_ST_fsm_state4_blk = 1'b0;

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | ((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        ap_return = ret_V_fu_217_p2;
    end else begin
        ap_return = ap_return_preg;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_fifo_ff_M_elems_V_address0 = 6'd56;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_fifo_ff_M_elems_V_address0 = grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address0;
    end else begin
        datapath_share_fifo_ff_M_elems_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_fifo_ff_M_elems_V_address1 = 6'd62;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_fifo_ff_M_elems_V_address1 = grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_address1;
    end else begin
        datapath_share_fifo_ff_M_elems_V_address1 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_fifo_ff_M_elems_V_ce0 = 1'b1;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_fifo_ff_M_elems_V_ce0 = grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce0;
    end else begin
        datapath_share_fifo_ff_M_elems_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_fifo_ff_M_elems_V_ce1 = 1'b1;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_fifo_ff_M_elems_V_ce1 = grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_datapath_share_fifo_ff_M_elems_V_ce1;
    end else begin
        datapath_share_fifo_ff_M_elems_V_ce1 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_lut_ff_M_elems_V_address0 = 6'd56;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_lut_ff_M_elems_V_address0 = grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address0;
    end else begin
        datapath_share_lut_ff_M_elems_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_lut_ff_M_elems_V_address1 = 6'd62;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_lut_ff_M_elems_V_address1 = grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_address1;
    end else begin
        datapath_share_lut_ff_M_elems_V_address1 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_lut_ff_M_elems_V_ce0 = 1'b1;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_lut_ff_M_elems_V_ce0 = grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce0;
    end else begin
        datapath_share_lut_ff_M_elems_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        datapath_share_lut_ff_M_elems_V_ce1 = 1'b1;
    end else if (((shifter_enable1 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        datapath_share_lut_ff_M_elems_V_ce1 = grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_datapath_share_lut_ff_M_elems_V_ce1;
    end else begin
        datapath_share_lut_ff_M_elems_V_ce1 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((1'b1 == ap_CS_fsm_state2) & (1'b0 == ap_block_state2_on_subcall_done))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

always @ (*) begin
    ap_block_state2_on_subcall_done = (((grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_done == 1'b0) & (shifter_enable1 == 1'd1)) | ((grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_done == 1'b0) & (shifter_enable1 == 1'd1)));
end

assign grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start = grp_process_Pipeline_VITIS_LOOP_47_1_fu_108_ap_start_reg;

assign grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start = grp_process_Pipeline_VITIS_LOOP_54_2_fu_115_ap_start_reg;

assign lut_rol1_shifted_V_fu_181_p3 = ((s2[0:0] == 1'b1) ? datapath_share_lut_ff_M_elems_V_q1 : datapath_share_fifo_ff_M_elems_V_q1);

assign lut_rol8_V_fu_188_p3 = ((s2[0:0] == 1'b1) ? datapath_share_lut_ff_M_elems_V_q0 : datapath_share_fifo_ff_M_elems_V_q0);

assign ret_V_3_fu_195_p2 = (lut_rol8_V_fu_188_p3 & datapath_share_ff63_V);

assign ret_V_4_fu_201_p2 = (lut_rol8_shifted_ext & lut_rol1_shifted_V_fu_181_p3);

assign ret_V_fu_217_p2 = (xor_ln1499_fu_206_p2 ^ xor_ln1499_1_fu_211_p2);

assign s3_read_read_fu_50_p2 = s3;

assign select_ln78_fu_157_p3 = ((s2[0:0] == 1'b1) ? datapath_share_lut_out_V : datapath_share_ff63_V);

assign select_ln79_fu_169_p3 = ((s2[0:0] == 1'b1) ? datapath_share_ff63_V : datapath_share_lut_out_V);

assign xor_ln1499_1_fu_211_p2 = (ret_V_3_fu_195_p2 ^ lut_rol1_shifted_V_fu_181_p3);

assign xor_ln1499_fu_206_p2 = (ret_V_4_fu_201_p2 ^ key_in);

endmodule //top_process_r
