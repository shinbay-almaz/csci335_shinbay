module bitty_core (
  input [15:0] instruction,
  input clk,
  input reset,
  input run,
  output reg done
);

reg en_i, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7;
reg [15:0] regInst_out;
reg [15:0] regS_out;
reg [15:0] regC_out;
reg [15:0] reg0_out;
reg [15:0] reg1_out;
reg [15:0] reg2_out;
reg [15:0] reg3_out;
reg [15:0] reg4_out;
reg [15:0] reg5_out;
reg [15:0] reg6_out;
reg [15:0] reg7_out;
reg [2:0] mux_sel;
reg [3:0] alu_sel;
reg alu_mode;

mux mux(.mux_sel(mux_sel),
        .in0(reg0_out),
        .in1(reg1_out),
        .in2(reg2_out),
        .in3(reg3_out),
        .in4(reg4_out),
        .in5(reg5_out),
        .in6(reg6_out),
        .in7(reg7_out),
        .out(mux_out));

register reg_inst(.clk(clk),
                  .reset(reset),
                  .enable(en_i),
                  .d_in(instruction),
                  .d_out(regInst_out));
register reg_s(.clk(clk),
                  .reset(reset),
                  .enable(en_s),
                  .d_in(mux_out),
                  .d_out(regS_out));
register reg_c(.clk(clk),
                  .reset(reset),
                  .enable(en_c),
                  .d_in(alu_out),
                  .d_out(regC_out));
register reg_0(.clk(clk),
                  .reset(reset),
                  .enable(en_0),
                  .d_in(regC_out),
                  .d_out(reg0_out));
register reg_1(.clk(clk),
                  .reset(reset),
                  .enable(en_1),
                  .d_in(regC_out),
                  .d_out(reg1_out));
register reg_2(.clk(clk),
                  .reset(reset),
                  .enable(en_2),
                  .d_in(regC_out),
                  .d_out(reg2_out));
register reg_3(.clk(clk),
                  .reset(reset),
                  .enable(en_3),
                  .d_in(regC_out),
                  .d_out(reg3_out));
register reg_4(.clk(clk),
                  .reset(reset),
                  .enable(en_4),
                  .d_in(regC_out),
                  .d_out(reg4_out));
register reg_5(.clk(clk),
                  .reset(reset),
                  .enable(en_5),
                  .d_in(regC_out),
                  .d_out(reg5_out));
register reg_6(.clk(clk),
                  .reset(reset),
                  .enable(en_6),
                  .d_in(regC_out),
                  .d_out(reg6_out));
register reg_7(.clk(clk),
                  .reset(reset),
                  .enable(en_7),
                  .d_in(regC_out),
                  .d_out(reg7_out));

alu alu(.in_a(regS_out),
        .in_b(mux_out),
        .sel(alu_sel),
        .mode(alu_mode),
        .out(alu_out));

control_unit control(.instruction(regInst_out),
                .run(run),
                .clk(clk),
                .reset(reset),
                .done(done),
                .alu_sel(alu_sel),
                .alu_mode(alu_mode),
                .mux_sel(mux_sel),
                .en_i(en_i),
                .en_s(en_s),
                .en_c(en_c),
                .en_0(en_0),
                .en_1(en_1),
                .en_2(en_2),
                .en_3(en_3),
                .en_4(en_4),
                .en_5(en_5),
                .en_6(en_6),
                .en_7(en_7));



endmodule
