import "DPI-C" function void compare_results(input shortint unsigned instruction, input shortint unsigned written_value);

module monitor (
  input done,
  input [15:0] instruction, 
  input [15:0] written_value,
  input [15:0] mem_addr
);
  
always @(posedge done) begin
  $display("Memory Address in Verilog: %d", mem_addr);
  compare_results(instruction, written_value);
end

endmodule
