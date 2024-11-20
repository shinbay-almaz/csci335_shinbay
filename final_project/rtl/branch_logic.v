module branch_logic(
  input [15:0] instruction,
  input [7:0] pc,
  input [15:0] last_alu_result,
  input done,
  output reg [7:0] new_pc
);

always @ (*) begin
  new_pc = pc;
  if (done) begin
    new_pc = pc + 1;
    if (instruction[1:0] == 2'd2) begin
      if (instruction[3:2] == last_alu_result[1:0]) 
        new_pc = instruction[11:4];
    end
  end
end

endmodule
