module register (
  input [15:0] d_in,
  input reset,
  input clk, 
  input enable,
  output reg [15:0] d_out
);

parameter INIT_VAL = 16'd2;

always @ (posedge clk, posedge reset) begin
  if (reset)
    d_out <= INIT_VAL;
  else if (enable)
    d_out <= d_in;
end

endmodule
