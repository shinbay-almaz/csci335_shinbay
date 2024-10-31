#include <iostream>
#include <string>
#include "common.h"
#include "assembler.h"
#include "disassembler.h"

using namespace std;

void print_usage(const char* program_name) {
  std::cerr << "Usage: " << program_name
            << " -i <input file> [-o <output file>] -a|-d\n";
}

int main(int argc, char** argv) {
  std::string input_file, output_file;
  bool assemble_flag = false;
  bool disassemble_flag = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-i" && i + 1 < argc) {
      input_file = argv[++i];
    } else if (arg == "-o" && i + 1 < argc) {
      output_file = argv[++i];
    } else if (arg == "-a") {
      assemble_flag = true;
    } else if (arg == "-d") {
      disassemble_flag = true;
    } else {
      print_usage(argv[0]);
      return 1;
    }
  }

  if (input_file.empty()) {
    std::cerr << "Error: The input file is required (-i <input file>).\n";
    print_usage(argv[0]);
    return 1;
  }
  if (assemble_flag == disassemble_flag) {
    std::cerr << "Error: Either -a (assemble) or -d (disassemble) must be "
                 "specified, not both.\n";
    print_usage(argv[0]);
    return 1;
  }

  if (assemble_flag) {
    Assembler assembler;
    int status;

    if (!output_file.empty()) {
      status = assembler.assemble_and_save(input_file, output_file);
    } else {
      status = assembler.assemble(input_file);
    }
    if (status == Status::FAILED_TO_OPEN) {
      std::cerr
          << "Error: Failed to open the input file and/or the output file.\n";
    } else if (status == Status::INVALID_INSTRUCTION) {
      std::cerr << "Error: Failed to assemble the input file.\n";
    }
    return status;
  } else if (disassemble_flag) {
    Disassembler disassembler;
    int status;
    if (!output_file.empty()) {
      status = disassembler.disassemble_and_save(input_file, output_file);
    } else {
      status = disassembler.disassemble(input_file);
    }
    if (status == Status::FAILED_TO_OPEN) {
      std::cerr
          << "Error: Failed to open the input file and/or the output file.\n";
    } else if (status == Status::INVALID_INSTRUCTION) {
      std::cerr << "Error: Failed to disassemble the input file.\n";
    }
    return status;
  }
}
