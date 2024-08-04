module speck_toplevel_tb;

    // Inputs
    reg clk;
    reg reset;
    reg start;
    reg [767:0] d_in;

    // Outputs
    wire done;
    wire [127:0] cipher_out;

    // Instantiate the Unit Under Test (UUT)
    speck_toplevel uut (
        .clk(clk), 
        .reset(reset),
        .start(start),
        .d_in(d_in),
        .done(done),
        .cipher_out(cipher_out)
    );
    reg [15:0] cycle;
    always @(posedge clk)
	begin
	cycle<=cycle+1;
	end
	
    initial begin
        // Initialize Inputs
        clk = 0;
        cycle=0;
        reset = 1;
        start = 0;
        d_in = 768'h6c617669757165207469206564616d200f0e0d0c0b0a090807060504030201006c617669757165207469206564616d200f0e0d0c0b0a090807060504030201006c617669757165207469206564616d200f0e0d0c0b0a09080706050403020100;
        
        // Wait for global reset
        #1000;
        reset = 0;
        #10;
        
        // Start the process
        start = 1;
        #30000;
        start = 0;
        
        // Wait for the done signal
        wait(done);
        #10;

        // Display the output
        $display("Cipher Output: %h", cipher_out);
        $finish;
    end

    always #5 clk = ~clk;

endmodule
