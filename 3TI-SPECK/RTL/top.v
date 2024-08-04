module speck_toplevel(
    input clk,
    input reset,
    input start,
    input [767:0] d_in,
    output reg done,
    output reg [127:0] cipher_out
);

    reg data_ina, data_inb, data_inc;
    reg k_data_ina, k_data_inb, k_data_inc;
    reg carry_init_a, carry_init_b, carry_init_c;
    reg we, Start;
    wire [1:0] cipher_out1, cipher_out2, cipher_out3;
    wire rndlessthan32;

    reg [255:0] pka, pkb, pkc;
    reg [7:0] cycle;
    reg [1:0] state;

    // State encoding
    localparam IDLE = 2'b00,
               LOAD_DATA = 2'b01,
               ENCRYPTION = 2'b10,
               XOR_OUTPUT = 2'b11;

    bitSpeck128_128_hierarchy_carry_sharing uut (
        .clk(clk), 
        .data_ina(data_ina), 
        .data_inb(data_inb), 
        .data_inc(data_inc), 
        .k_data_ina(k_data_ina), 
        .k_data_inb(k_data_inb), 
        .k_data_inc(k_data_inc), 
        .carry_init_a(carry_init_a),
        .carry_init_b(carry_init_b),
        .carry_init_c(carry_init_c),
        .we(we), 
        .Start(Start),
        .cipher_out1(cipher_out1), 
        .cipher_out2(cipher_out2), 
        .cipher_out3(cipher_out3), 
        .rndlessthan32(rndlessthan32)
    );
    
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            done <= 0;
            cipher_out <= 0;
            we <= 0;
            Start <= 0;
            cycle <= 0;
            carry_init_a <= 1;
            carry_init_b <= 0;
            carry_init_c <= 1;
            pka <= 0;
            pkb <= 0;
            pkc <= 0;
            state <= IDLE;
        end else begin
            case (state)
                IDLE: begin
                    if (start) begin
                        cycle <= 0;
                        state <= LOAD_DATA;
                    end
                end
                LOAD_DATA: begin
                    if (cycle < 128) begin
                        pka[cycle + 128] <= d_in[cycle + 512];
                        pkb[cycle + 128] <= d_in[cycle + 256];
                        pkc[cycle + 128] <= d_in[cycle];
                        pka[cycle] <= d_in[cycle + 384];
                        pkb[cycle] <= d_in[cycle + 128];
                        pkc[cycle + 640] <= d_in[cycle + 640];
                        cycle <= cycle + 1;
                    end else begin
                        cycle <= 0;
                        state <= ENCRYPTION;
                    end
                end
                ENCRYPTION: begin
                    if (cycle < 128) begin
                        we <= 1;
                        data_ina <= pka[cycle + 128];
                        data_inb <= pkb[cycle + 128];
                        data_inc <= pkc[cycle + 128];
                        k_data_ina <= pka[cycle];
                        k_data_inb <= pkb[cycle];
                        k_data_inc <= pkc[cycle];
                        cycle <= cycle + 1;
                    end else begin
                        we <= 0;
                        Start <= 1;
                        if (!rndlessthan32) begin
                            cycle <= 0;
                            state <= XOR_OUTPUT;
                        end
                    end
                end
                XOR_OUTPUT: begin
                    if (cycle < 64) begin
                        cipher_out[cycle*2 +: 2] <= cipher_out1 ^ cipher_out2 ^ cipher_out3;
                        cycle <= cycle + 1;
                    end else begin
                        done <= 1;
                        state <= IDLE;
                    end
                end
            endcase
        end
    end

endmodule
