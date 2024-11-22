module data_memory(
  input [15:0] data_in,
  output reg [15:0] data_out,
  input read,
  input write,
  input [15:0] mem_addr
);

reg [15:0] memory [0:65535];

int i;

initial begin
  for (i = 0; i < 65536; i = i + 1) begin
    memory[i] = 16'd0;
  end
end

always @ (*) begin
  if (read) begin
    data_out = memory[mem_addr];
  end else begin
    data_out = data_in;
  end
end

always @ (posedge write) begin
  memory[mem_addr] = data_in;
end

endmodule
