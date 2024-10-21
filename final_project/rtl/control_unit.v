module control_unit (
  input [15:0] instruction,
  input run,
  input clk,
  input reset,
  output reg done,
  output reg [2:0] alu_sel, 
  output reg [2:0] mux_sel,
  output reg en_i, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7
);

  parameter State0 = 3'b000;
  parameter State1 = 3'b001;
  parameter State2 = 3'b010;
  parameter State3 = 3'b011;
  parameter State4 = 3'b100;
  parameter State5 = 3'b101;

  reg [2:0] current_state, next_state;

 /* always @ (posedge clk or posedge reset) begin
    if (reset) begin
      current_state <= State0;
    end else begin
      current_state <= next_state;
    end
  end */
 always @ (posedge clk or posedge reset) begin
    if (reset) begin
        current_state <= State0;
 //       $display("Reset activated, entering State0");
    end else begin
        current_state <= next_state;
 //       $display("Transitioning to state: %b", next_state);
    end
end


  always @ (*) begin
    if (run) begin
      case (current_state)
        State0: begin
          next_state = State1;
        end
        State1: begin
          next_state = State2;
        end
        State2: begin
          next_state = State3;
        end
        State3: begin
          next_state = State4;
        end
        State4: begin
          next_state = State5;
        end
        default: begin
          next_state = State0;
        end
      endcase
    end else begin
      next_state = State0;
    end
  end

  always @ (*) begin
    en_i = 0;
    en_s = 0; en_c = 0; en_0 = 0; en_1 = 0; en_2 = 0; 
    en_3 = 0; en_4 = 0; en_5 = 0; en_6 = 0; en_7 = 0;
    mux_sel = 3'd0;
    alu_sel = 3'd0;
    done = 0;
    case (current_state)
      State2: begin
        en_i = 1;
      end
      State3: begin
        en_s = 1;
        mux_sel = instruction[15:13];
      end
      State4: begin
        en_c = 1;
        mux_sel = instruction[12:10];
        alu_sel = instruction[4:2];
      end
      State5: begin
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
        done = 1;
      end
    endcase
  end



endmodule
