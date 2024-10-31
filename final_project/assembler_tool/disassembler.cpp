#include <fstream>
#include <iostream>
#include "disassembler.h"
#include "common.h"

int Disassembler::disassemble(std::string program_file) {
  std::ifstream in(program_file);

  if (!in.is_open()) {
    return Status::FAILED_TO_OPEN;
  }

  std::vector<std::string> assembly_instructions;
  for (uint16_t machine_code; in >> std::hex >> machine_code;) {
    std::vector<int> instruction = parse_machine(machine_code);

    if (instruction[0] == -1) {
      return Status::INVALID_INSTRUCTION;
    }

    std::string assembly_instruction = convert_to_assembly(instruction);
    assembly_instructions.push_back(assembly_instruction);
  }

  for (std::string assembly_instruction : assembly_instructions) {
    std::cout << assembly_instruction << "\n";
  }

  return Status::SUCCESSFUL;
}

int Disassembler::disassemble_and_save(std::string input_file, std::string output_file) {
  std::ifstream in(input_file);

  if (!in.is_open()) {
    return Status::FAILED_TO_OPEN;
  }

  std::ofstream out(output_file);

  std::vector<std::string> assembly_instructions;
  for (uint16_t machine_code; in >> std::hex >> machine_code;) {
    std::vector<int> instruction = parse_machine(machine_code);

    if (instruction[0] == -1) {
      return Status::INVALID_INSTRUCTION;
    }

    std::string assembly_instruction = convert_to_assembly(instruction);
    assembly_instructions.push_back(assembly_instruction);
  }

  for (std::string assembly_instruction : assembly_instructions) {
    out << assembly_instruction << "\n";
  }

  return Status::SUCCESSFUL;
}
