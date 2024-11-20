module instruction_fetch_unit (
  input clk,
  input reset,
  input done,
  input [15:0] last_alu_result,
  output reg [15:0] out
);

reg [7:0] cur_pc, next_pc;

/* verilator lint_off WIDTHEXPAND */
memory memory(.addr(cur_pc),
              .clk(clk),
              .out(out));

register pc(.clk(clk), 
            .reset(reset),
            .d_in(next_pc),
            .d_out(cur_pc),
            .enable(done));

branch_logic bl(.instruction(out) , 
                .pc(cur_pc), 
                .last_alu_result(last_alu_result), 
                .done(done), 
                .new_pc(next_pc));
/* verilator lint_on WIDTHEXPAND */

endmodule
