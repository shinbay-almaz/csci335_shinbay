#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <string>
#include <vector>

enum Status { SUCCESSFUL, FAILED_TO_OPEN, INVALID_INSTRUCTION };

std::vector<int> parse_assembly(std::string assembly_instruction);

std::vector<int> parse_machine(uint16_t machine_code);

std::string convert_to_assembly(std::vector<int> instruction);

uint16_t convert_to_machine(std::vector<int> instruction);

int get_instruction_type_from_machine(uint16_t machine_code);

int get_instruction_type_from_assembly(std::string assembly_command);

std::string get_assembly_command_from_type(int instruction_type);

#endif
