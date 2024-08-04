This is a repository containing 5 sets of TI-cipher comparison between HLS and RTL builds, in each folder HLS-C, HLS-generated HDL, RTL-HDL code will be in their according folders. All builds in this repository are for comparison and evaluation purpose, please do not use for actual security purpose.
The C++ codes aim to simulate the exact same behavior from verilog designs, does not provide the most efficient and optimized style of C coding for HLS to generate best performance circuit.
For the purpose of not letting HLS change too much from RTL design, pipelining for loops are turned off in C-Synthesis.

The implementation results for each RTL-HLS pair is located in the implementation_result.pdf.



This repository also contains minor submodules built with HLS comparing to RTL counter-part, however for submodules some sets of build does not have completely equivalent logic or behavior, it's only for purpose of understanding how HLS work at level of very simple behaviors.


For pairing manner we also listed the original RTL designs from other developers:

For all SIMON's design and SPECK's design are from this open-source repository: https://github.com/vernamlab/Lightweight-Threshold-Implementations/tree/master

For TI-LED's design please refer to: https://github.com/Secure-Embedded-Systems/Open-Source-Threshold-Implementation-of-LED-Block-Cipher
