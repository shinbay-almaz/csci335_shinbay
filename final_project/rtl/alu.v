module alu (
  input wire [15:0] in_a,     // 16-bit input A
  input wire [15:0] in_b,     // 16-bit input B
  input wire [2:0] select,    // 3-bit operation selector
  output reg [15:0] alu_out   // 16-bit output from ALU (logic operations)
);

  always @(*) begin
    case (select)
      3'd0:  alu_out = in_a + in_b;          // add a, b
      3'd1:  alu_out = in_a - in_b;          // sub a, b
      3'd2:  alu_out = in_a & in_b;          // and a, b
      3'd3:  alu_out = in_a | in_b;          // or a, b
      3'd4:  alu_out = in_a ^ in_b;          // xor a, b
      3'd5:  alu_out = in_a << in_b;         // shl a, b
      3'd6:  alu_out = in_a >> in_b;         // shr a, b
      3'd7:  begin                             // cmp a, b
        if (in_a == in_b) alu_out = 0;
        else if (in_a > in_b) alu_out = 1;
        else alu_out = 2;
      end
    endcase
  end

endmodule
