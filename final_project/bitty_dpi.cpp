#include "emulator/BittyEmulator.h"
#include "BittyInstrGenerator.h"

#include <cassert>
#include <cstdint>
#include <iostream>

BittyEmulator emulator = BittyEmulator();

using namespace std;

extern "C" void compare_results(uint16_t instruction, uint16_t written_value) {
  uint16_t expected_instruction = emulator.RunOneInstruction();

 // cout << ((instruction >> 13) & 0x7) << endl;
 // cout << ((instruction >> 10) & 0x7) << endl;
 // cout << ((instruction >> 3) & 0x7) << endl;
 // cout << written_value << " " << emulator.GetRegisterValue((instruction >> 13) & 0x7) << endl;

  cout << hex << expected_instruction << " " << instruction << endl;
  cout << "Value of register " << dec << ((instruction >> 13) & 0x7) << " after an instruction 0x" << hex << instruction << ":" << endl;
  cout << "In Bitty Core => " << dec << written_value << endl;
  cout << "In Bitty Emulator => " << dec << emulator.GetRegisterValue((instruction >> 13) & 0x7) << endl;
  assert(expected_instruction == instruction);

  uint16_t format = instruction & 0x3;
  if (format != 2) assert(emulator.GetRegisterValue((instruction >> 13) & 0x7) == written_value);
}
