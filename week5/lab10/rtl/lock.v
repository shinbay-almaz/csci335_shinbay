module lock (
    input clk,
    input reset,           // Asynchronous reset
    input [3:0] digit,
    output reg locked
);
    // State encoding
    parameter Locked = 3'b000;
    parameter State1 = 3'b001;
    parameter State2 = 3'b010;
    parameter State3 = 3'b011;
    parameter State4 = 3'b100;
    parameter State5 = 3'b101;
    parameter Unlocked = 3'b110;

    reg [2:0] current_state, next_state;

    // Model state register (sequential logic)
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= Locked;
        end else begin
            current_state <= next_state;
        end
    end

    // Model next state decode logic (combinational logic)
    always @(*) begin
        case (current_state)
            Locked: begin
              if (digit == 4'd3)
                next_state = State1;
              else
                next_state = Locked;
            end
            State1: begin
              if (digit == 4'd3)
                next_state = State2;
              else
                next_state = Locked;
            end
            State2: begin
              if (digit == 4'd5)
                next_state = State3;
              else 
                next_state = Locked;
            end
            State3: begin
              if (digit == 4'd2)
                next_state = State4;
              else 
                next_state = Locked;
            end
            State4: begin
              if (digit == 4'd5)
                next_state = State5;
              else 
                next_state = Locked;
            end
            State5: begin
              if (digit == 4'd6)
                next_state = Unlocked;
              else 
                next_state = Locked;
            end
            Unlocked: begin
              next_state = Unlocked;
            end
            default: begin
                next_state = Locked;
            end
        endcase
    end

    // Model output logic (combinational logic)
    always @(*) begin
        case (current_state)
            Unlocked: begin
                locked = 1'b0; 
            end
            default: begin
                locked = 1'b1; 
            end
        endcase
    end
endmodule
