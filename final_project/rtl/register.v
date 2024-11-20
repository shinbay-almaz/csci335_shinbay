module register (
  input [15:0] d_in,
  input reset,
  input clk, 
  input enable,
  output reg [15:0] d_out
);

always @ (posedge clk, posedge reset) begin
  if (reset)
    d_out <= 16'd0;
  else if (enable)
    d_out <= d_in;
end

endmodule
