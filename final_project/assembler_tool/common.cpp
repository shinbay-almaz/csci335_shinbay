#include <cassert>
#include <unordered_map>
#include "common.h"

std::vector<int> parse_machine(uint16_t machine_code) {
  std::vector<int> instruction;

  int instruction_type = get_instruction_type_from_machine(machine_code);

  instruction.push_back(instruction_type);
  if (instruction_type < 8) {
    int rx = machine_code >> 13 & 0x7;
    int ry = machine_code >> 10 & 0x7;
    instruction.push_back(rx);
    instruction.push_back(ry);
  } else if (instruction_type < 16) {
    int rx = machine_code >> 13 & 0x7;
    int immed = machine_code >> 5 & 0xFF;
    instruction.push_back(rx);
    instruction.push_back(immed);
  } else {
    int immed = machine_code >> 4 & 0xFFF;
    instruction.push_back(immed);
  }
  return instruction;
}

uint16_t convert_to_machine(std::vector<int> instruction) {
  uint16_t machine_code = 0;

  uint16_t format = instruction[0] < 8 ? 0 : (instruction[0] < 16 ? 1 : 2);
  machine_code |= format;

  switch (format) {
    case 0: {
      machine_code |= instruction[0] << 2;
      machine_code |= instruction[1] << 13;
      machine_code |= instruction[2] << 10;
      break;
    }
    case 1: {
      machine_code |= (instruction[0] - 8) << 2;
      machine_code |= instruction[1] << 13;
      machine_code |= instruction[2] << 5;
      break;
    }
    case 2: {
      machine_code |= (instruction[0] - 16) << 2;
      machine_code |= instruction[1] << 4;
      break;
    }
    default: {
      break;
    }
  }
  return machine_code;
}

int get_instruction_type_from_machine(uint16_t machine_code) {
  uint16_t format = machine_code & 0x3;
  switch (format) {
    case 0:
      return machine_code >> 2 & 0x7;
    case 1:
      return (machine_code >> 2 & 0x7) + 8;
    case 2:
      return (machine_code >> 2 & 0x3) + 16;
    default:
      return -1;
  }
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
  if (instruction[0] < 8) {
    instruction.push_back(tokens[1][1] - '0');
    instruction.push_back(tokens[2][1] - '0');
  } else if (instruction[0] < 16) {
    instruction.push_back(tokens[1][1] - '0');
    instruction.push_back(std::stoi(tokens[2].substr(1)));
  } else {
    instruction.push_back(std::stoi(tokens[1].substr(1)));
  }
  return instruction;
}

int get_instruction_type_from_assembly(std::string assembly_command) {
  static const std::unordered_map<std::string, int> command_map = {
      {"add", 0},   {"sub", 1},  {"and", 2},   {"or", 3},    {"xor", 4},
      {"shl", 5},   {"shr", 6},  {"cmp", 7},   {"addi", 8},  {"subi", 9},
      {"andi", 10}, {"ori", 11}, {"xori", 12}, {"shli", 13}, {"shri", 14},
      {"cmpi", 15}, {"bie", 16}, {"big", 17},  {"bil", 18}};
  auto it = command_map.find(assembly_command);
  return it != command_map.end() ? it->second : -1;
}

std::string get_assembly_command_from_type(int instruction_type) {
  static const std::vector<std::string> commands = {
      "add",  "sub",  "and",  "or",   "xor", "shl",  "shr",
      "cmp",  "addi", "subi", "andi", "ori", "xori", "shli",
      "shri", "cmpi", "bie",  "big",  "bil"};
  if (instruction_type >= commands.size())
    return "unknown";
  return commands[instruction_type];
}

std::string convert_to_assembly(std::vector<int> instruction) {
  std::string assembly_instruction = "";

  assembly_instruction += get_assembly_command_from_type(instruction[0]);
  if (instruction[0] < 8) {
    assembly_instruction += " r";
    assembly_instruction += (char) (instruction[1] + '0');
    assembly_instruction += " r";
    assembly_instruction += (char) (instruction[2] + '0');
  } else if (instruction[0] < 16) {
    assembly_instruction += " r";
    assembly_instruction += (char) (instruction[1] + '0');
    assembly_instruction += " #";
    assembly_instruction += std::to_string(instruction[2]);
  } else {
    assembly_instruction += " #";
    assembly_instruction += std::to_string(instruction[1]);
  }
  return assembly_instruction;
}
