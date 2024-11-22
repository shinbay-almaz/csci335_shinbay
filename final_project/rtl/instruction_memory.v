module instruction_memory (
  input clk,
  input [7:0] addr,
  output reg [15:0] out
);
  reg [15:0] instructions [0:255];

  int i;

  initial begin
    for (i = 0; i < 256; i = i + 1) begin
      instructions[i] = 16'hfffe;
    end
    $readmemh("instructions.txt", instructions);
  end

  always @ (posedge clk) begin
    out <= instructions[addr];
  end
endmodule
