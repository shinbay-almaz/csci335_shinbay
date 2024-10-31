#include <fstream>
#include <iostream>
#include "assembler.h"
#include "common.h"

int Assembler::assemble(std::string program_file) {
  std::ifstream in(program_file);

  if (!in.is_open()) {
    return Status::FAILED_TO_OPEN; 
  }

  std::vector<uint16_t> machine_codes;

  for (std::string assembly_instruction; getline(in, assembly_instruction);) {
    std::vector<int> instruction = parse_assembly(assembly_instruction);

    if (instruction[0] == -1) {
      return Status::INVALID_INSTRUCTION;
    }

    uint16_t machine_code = convert_to_machine(instruction);
    machine_codes.push_back(machine_code);
  }

  for (uint16_t machine_code : machine_codes) {
    std::cout << std::hex << machine_code << "\n";
  }

  return Status::SUCCESSFUL;
}

int Assembler::assemble_and_save(std::string input_file, std::string output_file) {
  std::ifstream in(input_file);

  if (!in.is_open()) {
    return Status::FAILED_TO_OPEN;
  }

  std::ofstream out(output_file);

  if (!out.is_open()) {
    return Status::FAILED_TO_OPEN;
  }

  std::vector<uint16_t> machine_codes;

  for (std::string assembly_instruction; getline(in, assembly_instruction);) {
    std::vector<int> instruction = parse_assembly(assembly_instruction);

    if (instruction[0] == -1) {
      return Status::INVALID_INSTRUCTION;
    }

    uint16_t machine_code = convert_to_machine(instruction);
    machine_codes.push_back(machine_code);
  }

  for (uint16_t machine_code : machine_codes) {
    out << std::hex << machine_code << "\n";
  }
  
  return Status::SUCCESSFUL;
}
