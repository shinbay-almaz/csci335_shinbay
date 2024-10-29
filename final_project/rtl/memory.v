module memory (
  input clk,
  input [7:0] addr,
  output reg [15:0] out
);
  reg [15:0] instructions [0:255];

  initial begin
    $readmemh("instructions.txt", instructions);
  end

  always @ (posedge clk) begin
    out <= instructions[addr];
  end
endmodule
