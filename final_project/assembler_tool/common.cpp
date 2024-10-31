#include <cassert>
#include <unordered_map>
#include "common.h"

std::vector<int> parse_machine(uint16_t machine_code) {
  std::vector<int> instruction;

  int rx = machine_code >> 13 & 0x7;
  int ry = machine_code >> 10 & 0x7;

  int instruction_type = get_instruction_type_from_machine(machine_code);

  instruction.push_back(instruction_type);
  instruction.push_back(rx);
  instruction.push_back(ry);

  return instruction;
}

uint16_t convert_to_machine(std::vector<int> instruction) {
  uint16_t machine_code = 0;

  machine_code |= instruction[0] << 2;
  machine_code |= instruction[1] << 13;
  machine_code |= instruction[2] << 10;

  return machine_code;
}

int get_instruction_type_from_machine(uint16_t machine_code) {
  return (machine_code >> 2 & 0x7);
}

std::vector<int> parse_assembly(std::string assembly_instruction) {
  std::vector<int> instruction;

  std::vector<std::string> tokens;

  for (size_t pos = 0; pos < assembly_instruction.size();) {
    size_t next_pos = assembly_instruction.find(' ', pos);
    if (next_pos == std::string::npos)
      next_pos = assembly_instruction.size();
    tokens.push_back(assembly_instruction.substr(pos, next_pos - pos));
    pos = next_pos + 1;
  }

  instruction.push_back(get_instruction_type_from_assembly(tokens[0]));
  instruction.push_back(tokens[1][1] - '0');
  instruction.push_back(tokens[2][1] - '0');

  return instruction;
}

int get_instruction_type_from_assembly(std::string assembly_command) {
  static const std::unordered_map<std::string, int> command_map = {
      {"add", 0}, {"sub", 1}, {"and", 2}, {"or", 3},
      {"xor", 4}, {"shl", 5}, {"shr", 6}, {"cmp", 7}};
  auto it = command_map.find(assembly_command);
  return it != command_map.end() ? it->second : -1;
}

std::string get_assembly_command_from_type(int instruction_type) {
  switch (instruction_type) {
    case 0:
      return "add";
    case 1:
      return "sub";
    case 2:
      return "and";
    case 3:
      return "or";
    case 4:
      return "xor";
    case 5:
      return "shl";
    case 6:
      return "shr";
    case 7:
      return "cmp";
    default: {
      assert(false);
    }
  }
}

std::string convert_to_assembly(std::vector<int> instruction) {
  std::string assembly_instruction = "";

  assembly_instruction += get_assembly_command_from_type(instruction[0]);
  assembly_instruction += " r";
  assembly_instruction += (char)(instruction[1] + '0');
  assembly_instruction += " r";
  assembly_instruction += (char)(instruction[2] + '0');

  return assembly_instruction;
}
