module core(
  input clk,
  input reset,
  input run,
  output reg done
);
  reg [15:0] instruction;
  reg [15:0] last_alu_result;
  
  reg is_jump_instruction;
  assign is_jump_instruction = (instruction[1:0] == 2'd2);
  reg is_program_running;
  assign is_program_running = (instruction != 16'hfffe);

  reg bc_done, ifu_done;
  assign ifu_done = is_program_running & (bc_done | is_jump_instruction);

  reg core_run;
  assign core_run = run & (!is_jump_instruction) & is_program_running;

  assign done = !is_program_running;

  reg [15:0] mem_addr;

  monitor monitor(.instruction(instruction),
                  .written_value(last_alu_result),
                  .done(ifu_done),
                  .mem_addr(mem_addr));

  instruction_fetch_unit ifu(.clk(clk), 
                             .reset(reset),
                             .done(ifu_done),
                             .last_alu_result(last_alu_result),
                             .out(instruction));

  bitty_core bc(.clk(clk),
                .reset(reset),
                .run(core_run),
                .instruction(instruction), 
                .done(bc_done),
                .last_alu_result(last_alu_result), .mem_addr(mem_addr));

endmodule
