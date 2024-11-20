module branch_logic(
//  input [15:0] instruction,
  input [7:0] pc,
//  input [15:0] last_alu_result,
  input done,
  output reg [7:0] new_pc
);

always @ (*) begin
  if (done) begin
    new_pc = pc + 1;
  end else new_pc = pc;
  /*
  if (instruction[1:0] == 2'd2) begin
    if ({14'd0, instruction[3:2]} == last_alu_result) begin
      new_pc = instruction[11:4];
    end else begin
      new_pc = pc + 1;
    end
  end else begin
    new_pc = pc + 1;
  end
  */
end

endmodule
