module instruction_fetch_unit (
  input clk,
  input reset,
  input done,
  output reg [15:0] out
);

reg [7:0] pc_in, pc_out;

assign pc_in = pc_out + 1;

/* verilator lint_off WIDTHEXPAND */
memory memory(.addr(pc_out), .clk(clk), .out(out));

register pc(.clk(clk), .reset(reset), .d_in(pc_in), .d_out(pc_out), .enable(done), .init(16'd0));
/* verilator lint_on WIDTHEXPAND */

endmodule
