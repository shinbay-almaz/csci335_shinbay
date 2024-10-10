module register (
  input [15:0] d_in,
  input [15:0] init_val,
  input reset,
  input clk, 
  input enable,
  output reg [15:0] d_out
);

always @ (posedge clk, posedge reset) begin
  if (reset)
    d_out <= init_val;
  else begin
    if (enable) 
      d_out <= d_in;
    else 
      d_out <= d_out;
  end
end

endmodule
