module Arithmetic (
  input wire carry_in,       // Carry input (single bit)
  input wire [15:0] in_a,    // 16-bit input A
  input wire [15:0] in_b,    // 16-bit input B
  input wire [3:0] select,   // 4-bit operation selector
  output reg carry_out,      // Carry output / Borrow flag (single bit)
  output wire compare,       // Compare output (1 if A == B)
  output reg [15:0] ar_out   // 16-bit output from ALU
);
always @(*) begin
    // Initialize outputs
    ar_out = 16'b0000000000000000;
    carry_out = 1'b0;
    compare = (in_a == in_b);

    case ({carry_in, select})
        // When carry_in is 0
        {1'b0, 4'b0000}: {carry_out, ar_out} = in_a;                                            // A
        {1'b0, 4'b0001}: ar_out = in_a | in_b;                                                  // A + B
        {1'b0, 4'b0010}: ar_out = in_a | ~in_b;                                                 // A + B'
        {1'b0, 4'b0011}: ar_out = 16'hFFFF;                                                     // -1 (all ones)
        {1'b0, 4'b0100}: ar_out = (in_a | (in_a & ~in_b));                                      // A + AB'
        {1'b0, 4'b0101}: {carry_out, ar_out} = (in_a | in_b) + {1'b0, (in_a & ~in_b)};          // (A + B) plus AB'
        {1'b0, 4'b0110}: {carry_out, ar_out} = in_a - in_b - 1;                                 // A minus B minus 1
        {1'b0, 4'b0111}: {carry_out, ar_out} = {1'b0, (in_a & ~in_b)} - 1;                      // AB' minus 1
        {1'b0, 4'b1000}: {carry_out, ar_out} = in_a + (in_a & in_b);                            // A plus AB
        {1'b0, 4'b1001}: {carry_out, ar_out} = in_a + in_b;                                     // A plus B
        {1'b0, 4'b1010}: {carry_out, ar_out} = {1'b0, (in_a | ~in_b)} + (in_a & in_b);          // (A + B') plus AB
        {1'b0, 4'b1011}: {carry_out, ar_out} = (in_a & in_b) - 1;                               // AB
        {1'b0, 4'b1100}: {carry_out, ar_out} = in_a + in_a;                                     // A plus A
        {1'b0, 4'b1101}: {carry_out, ar_out} = (in_a | in_b) + in_a;                            // (A + B) plus A
        {1'b0, 4'b1110}: {carry_out, ar_out} = {1'b0, (in_a | ~in_b)} + in_a;                   // (A + B') plus A
        {1'b0, 4'b1111}: {carry_out, ar_out} = in_a - 1;                                        // A - 1

        // When carry_in is 1
        {1'b1, 4'b0000}: {carry_out, ar_out} = in_a + 16'd1;                                    // A plus 1
        {1'b1, 4'b0001}: {carry_out, ar_out} = (in_a | in_b) + 16'd1;                           // (A + B) plus 1
        {1'b1, 4'b0010}: {carry_out, ar_out} = (in_a | (16'hFFFF - in_b)) + 16'd1;              // (A + B') plus 1
        {1'b1, 4'b0011}: {carry_out, ar_out} = {1'b1, 16'd0};                                   // Zero (all zeroes)
        {1'b1, 4'b0100}: {carry_out, ar_out} = {1'b0, (in_a | (in_a & ~in_b))} + 16'd1;         // (A + AB') plus 1
        {1'b1, 4'b0101}: {carry_out, ar_out} = (in_a | in_b) + {1'b0, (in_a & ~in_b)} + 16'd1;  // (A + B) plus AB' plus 1
        {1'b1, 4'b0110}: {carry_out, ar_out} = in_a - in_b;                                     // A minus B
        {1'b1, 4'b0111}: ar_out = in_a & ~in_b;                                                 // AB'
        {1'b1, 4'b1000}: {carry_out, ar_out} = in_a + (in_a & in_b) + 16'd1;                    // A plus AB plus 1
        {1'b1, 4'b1001}: {carry_out, ar_out} = in_a + in_b + 16'd1;                             // A plus B plus 1
        {1'b1, 4'b1010}: {carry_out, ar_out} = {1'b0, (in_a | ~in_b)} + (in_a & in_b) + 16'd1;  // (A + B') plus AB plus 1
        {1'b1, 4'b1011}: ar_out = in_a & in_b;                                                  // AB
        {1'b1, 4'b1100}: {carry_out, ar_out} = in_a + in_a + 16'd1;                             // A plus A plus 1
        {1'b1, 4'b1101}: {carry_out, ar_out} = (in_a | in_b) + in_a + 16'd1;                    // (A + B) plus A plus 1
        {1'b1, 4'b1110}: {carry_out, ar_out} = {1'b0, (in_a | ~in_b)} + in_a + 16'd1;           // (A + B') plus A plus 1
        {1'b1, 4'b1111}: ar_out = in_a;                                                         // A

        default: ar_out = 16'b0000000000000000;                                                 // Default case
    endcase
 end

endmodule

module Logic (
  input wire [15:0] in_a,     // 16-bit input A
  input wire [15:0] in_b,     // 16-bit input B
  input wire [3:0] select,    // 4-bit operation selector
  output reg [15:0] logic_out // 16-bit output from ALU (logic operations)
);

  always @(*) begin
    case (select)
      4'd0:  logic_out = ~in_a;          // NOT A
      4'd1:  logic_out = ~(in_a | in_b); // NOR
      4'd2:  logic_out = ~in_a & in_b;   // ~A AND B
      4'd3:  logic_out = 16'b0;          // Always 0
      4'd4:  logic_out = ~(in_a & in_b); // NAND
      4'd5:  logic_out = ~in_b;          // NOT B
      4'd6:  logic_out = in_a ^ in_b;    // XOR
      4'd7:  logic_out = in_a & ~in_b;   // A AND ~B
      4'd8:  logic_out = ~in_a | in_b;   // ~A OR B
      4'd9:  logic_out = ~(in_a ^ in_b); // XNOR
      4'd10: logic_out = in_b;           // B
      4'd11: logic_out = in_a & in_b;    // A AND B
      4'd12: logic_out = 16'b1;          // Always 1
      4'd13: logic_out = in_a | ~in_b;   // A OR ~B
      4'd14: logic_out = in_a | in_b;    // A OR B
      4'd15: logic_out = in_a;           // A
      default: logic_out = 16'b0;        // Default case
    endcase
  end

endmodule

module alu (
  input wire carry_in,          // Carry input (single bit)
  input wire [15:0] in_a,       // 16-bit input A
  input wire [15:0] in_b,       // 16-bit input B
  input wire [3:0] select,      // 4-bit operation selector
  input wire mode,              // Mode: 0 for arithmetic, 1 for logic
  output wire carry_out,        // Carry output (borrow flag in subtraction)
  output wire compare,          // Compare output (1 if A == B)
  output wire [15:0] alu_out    // 16-bit output from ALU
);

  wire [15:0] ar_out, logic_out;

  // Instantiate Arithmetic and Logic modules
  Arithmetic ar (
    .carry_in(carry_in),
    .in_a(in_a),
    .in_b(in_b),
    .select(select),
    .carry_out(carry_out),
    .compare(compare),
    .ar_out(ar_out)
  );

  Logic lg (
    .in_a(in_a),
    .in_b(in_b),
    .select(select),
    .logic_out(logic_out)
  );

  // Select between arithmetic or logic output based on mode
  assign alu_out = (mode == 1'b0) ? ar_out : logic_out;

endmodule
