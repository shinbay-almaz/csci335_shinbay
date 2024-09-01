module priority_encoder_9to4 (
    input wire in8,  // 1-bit input
    input wire in7,  // 1-bit input
	input wire in6,
	input wire in5,
	input wire in4,
	input wire in3,
	input wire in2,
	input wire in1,
	input wire in0,
    // continue defining input for all of the signals
    // as specified.

    output reg [3:0] out  // 4-bit output
);

always @(*) begin
    if (in8)
        out = 4'b1001;  // in8 is 1
    else if (in7)
    	out = 4'b1000;
  	else if (in6)
  		out = 4'b0111;
  	else if (in5)
      	out = 4'b0110;
 	else if (in4)
    	out = 4'b0101;
  	else if (in3)
    	out = 4'b0100;
  	else if (in2)
    	out = 4'b0011;
  	else if (in1)
    	out = 4'b0010;
  	else if (in0)
    	out = 4'b0001;
    else
        out = 4'b0000;  // No input is 1
end

endmodule
