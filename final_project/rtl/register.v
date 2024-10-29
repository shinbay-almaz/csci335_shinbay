module register (
  input [15:0] d_in,
  input reset,
  input clk, 
  input enable,
  input [15:0] init,
  output reg [15:0] d_out
);
initial begin
  d_out = init;
end

always @ (posedge clk, posedge reset) begin
  if (reset)
    d_out <= init;
  else if (enable)
    d_out <= d_in;
end

endmodule
