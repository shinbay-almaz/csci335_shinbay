module control_unit(
  input clk,
  input reset,
  input [15:0] instruction,
  input run,
  output reg done,
  output reg [2:0] alu_sel,
  output reg [3:0] mux_sel,
  output reg en_i, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7, read, write, en_m,
  output reg mem_sel,
  output reg [7:0] immediate
);

parameter LoadInstructionFromMemoryState = 3'b000;
parameter FetchInstructionFromRegState   = 3'b001;
parameter SaveFirstOperandState          = 3'b010;
parameter ExecuteALUState                = 3'b011;
parameter UpdateRegisterState            = 3'b100;
parameter UpdatePCState                  = 3'b101;

reg [2:0] current_state, next_state;

// Model state register (sequential logic)
always @ (posedge clk or posedge reset) begin
  if (reset) 
    current_state <= LoadInstructionFromMemoryState;
  else 
    current_state <= next_state;
end

// Model next state decode logic (combinational logic)
always @ (*) begin
  next_state = current_state;
  if (run) begin
    case (current_state)
      LoadInstructionFromMemoryState : next_state = FetchInstructionFromRegState;
      FetchInstructionFromRegState   : next_state = SaveFirstOperandState;
      SaveFirstOperandState          : next_state = ExecuteALUState;
      ExecuteALUState                : next_state = UpdateRegisterState;
      UpdateRegisterState            : next_state = UpdatePCState;
      UpdatePCState                  : next_state = LoadInstructionFromMemoryState;
      default                        : next_state = LoadInstructionFromMemoryState;
    endcase
  end
end

// Model output logic (combinational logic)
always @ (*) begin
  // Set output signals to default
  en_i = 0; en_s = 0; en_c = 0; done = 0;
  en_0 = 0; en_1 = 0; en_2 = 0; en_3 = 0;
  en_4 = 0; en_5 = 0; en_6 = 0; en_7 = 0;
  mem_sel = 0; read = 0; write = 0; en_m = 0;
  mux_sel = 4'd0; alu_sel = 3'd0;
  immediate = instruction[12:5];

  case (current_state) 
    LoadInstructionFromMemoryState : begin
      // Do nothing for now
    end
    FetchInstructionFromRegState   : begin
      en_i = 1;
    end
    SaveFirstOperandState          : begin
      en_s = 1; mux_sel = {1'd0, instruction[15:13]};
    end
    ExecuteALUState                : begin
      en_c = 1;
      en_m = 1;
      case (instruction[1:0])
        2'd0: begin
          mux_sel = {1'd0, instruction[12:10]};
        end
        2'd1: begin
          mux_sel = 4'd8;
        end
        2'd3: begin
          mux_sel = {1'd0, instruction[12:10]};
        end
        default: begin
          $display("Wrong format!");
        end
      endcase
      if (instruction[1:0] < 2) begin
        alu_sel = instruction[4:2];
      end else begin
        read = !instruction[2];
        write = instruction[2];
        mem_sel = 1;
      end
    end
    UpdateRegisterState            : begin
      if (instruction[2:0] != 3'b111) begin
        case (instruction[15:13])
          3'd0: en_0 = 1;
          3'd1: en_1 = 1;
          3'd2: en_2 = 1;
          3'd3: en_3 = 1;
          3'd4: en_4 = 1;
          3'd5: en_5 = 1;
          3'd6: en_6 = 1;
          3'd7: en_7 = 1;
        endcase
      end
      done = 1;
    end
    UpdatePCState                  : begin
      // Do nothing for now
    end
    default                        : begin
      // Do nothing for now
    end
  endcase
end

        



endmodule

