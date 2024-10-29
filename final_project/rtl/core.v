module core(
  input clk,
  input reset,
  input run,
  output reg status
);
  reg [15:0] instruction;

  instruction_fetch_unit ifu(.clk(clk), .reset(reset), .done(done), .out(instruction));

  bitty_core bc(.clk(clk), .reset(reset), .run(run), .instruction(instruction), .done(status));

endmodule
