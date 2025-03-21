module branch_logic(
  input [15:0] instruction,
  input [7:0] pc,
  input [15:0] last_alu_result,
  input done,
  output reg [7:0] new_pc
);

always @ (posedge done) begin
    $display("Instruction: %x", instruction);
    $display("Instruction Condition: %d", instruction[3:2]);
    $display("Last ALU result: %d", last_alu_result);
    new_pc = pc + 1;
    if (instruction[1:0] == 2'd2) begin
      if (instruction[3:2] == last_alu_result[1:0]) new_pc = instruction[11:4];
    end
end

endmodule
