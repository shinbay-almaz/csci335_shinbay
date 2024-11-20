module mux (
  input [15:0] in0,
  input [15:0] in1,
  input [15:0] in2,
  input [15:0] in3,
  input [15:0] in4,
  input [15:0] in5,
  input [15:0] in6,
  input [15:0] in7,
  input [15:0] in8,
  input [3:0] mux_sel,
  output reg [15:0] out
);
  always @ (*) begin
    case (mux_sel) 
      4'd0: out = in0;
      4'd1: out = in1;
      4'd2: out = in2;
      4'd3: out = in3;
      4'd4: out = in4;
      4'd5: out = in5;
      4'd6: out = in6;
      4'd7: out = in7;
      4'd8: out = in8;
      default: out = 16'd0;
    endcase
  end
endmodule
