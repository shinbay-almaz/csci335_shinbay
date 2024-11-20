#include <fstream>
#include <iostream>
#include "BittyEmulator.h"

using namespace std;

BittyEmulator::BittyEmulator() {
  registers_ = vector<uint16_t>(8);

  PC = 0;

  ifstream is("instructions.txt");

  for (uint16_t instruction; is >> hex >> instruction;)
    memory_.push_back(instruction);
}

uint16_t BittyEmulator::GetRegisterValue(uint16_t reg_num) {
  return registers_[reg_num];
}

void BittyEmulator::Evaluate(uint16_t instruction) {
  uint16_t format = (instruction & 0x3);
  uint16_t rx, ry;
  uint16_t rx_val, ry_val;
  uint16_t select;
  switch (format) {
    case 0: {
      rx = (instruction >> 13);        // First register number (read/write)
      ry = (instruction >> 10) & 0x7;  // Second register number (read)

      //cout << rx << " " << ry << "\n";

      select = (instruction >> 2) & 0x7;  // ALU select

      rx_val = GetRegisterValue(rx);
      ry_val = GetRegisterValue(ry);
      break;
    }
    case 1: {
      rx = (instruction >> 13);

      rx_val = GetRegisterValue(rx);
      ry_val = (instruction >> 5) & 0xFF;

      select = (instruction >> 2) & 0x7;
      break;
    }
    case 2: {
      return;
    }
    default: {
      std::cerr << instruction << std::endl;
      std::cerr << "Unsupported instruction format" << std::endl;
      exit(1);
    }
  }

  //cout << rx_val << " " << ry_val << "\n";
  // Evaluate the result based on ALU select
  switch (select) {
    case 0:  // add rx, ry
      rx_val += ry_val;
      break;
    case 1:  // sub rx, ry
      rx_val -= ry_val;
      break;
    case 2:  // and rx, ry
      rx_val &= ry_val;
      break;
    case 3:  // or rx, ry
      rx_val |= ry_val;
      break;
    case 4:  // xor rx, ry
      rx_val ^= ry_val;
      break;
    case 5:  // shl rx, ry
      rx_val <<= (ry_val & 0xF);
      break;
    case 6:  // shr rx, ry
      rx_val >>= (ry_val & 0xF);
      break;
    default:  // cmp rx, ry
      rx_val = rx_val == ry_val ? 0 : rx_val > ry_val ? 1 : 2;
      break;
  }

  registers_[rx] = rx_val;
  last_ALU_result = rx_val;
}

uint8_t BittyEmulator::Branch(uint16_t instruction) {
  uint16_t format = instruction & 0x3;
  uint16_t cond = instruction >> 2 & 0x3;

  if (format == 2)
    if (cond == last_ALU_result)
      return (instruction >> 4);

  return PC + 1;
}

uint16_t BittyEmulator::RunOneInstruction() {
  uint16_t instruction = memory_[PC];

  Evaluate(instruction);

  PC = Branch(instruction);

  return instruction;
}
