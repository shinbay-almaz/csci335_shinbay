#include "BittyEmulator.h"
#include "BittyInstrGenerator.h"

#include <cassert>
#include <cstdint>
#include <iostream>

BittyEmulator emulator = BittyEmulator();

using namespace std;

extern "C" void compare_results(uint16_t instruction, uint16_t written_value) {
  emulator.Evaluate(instruction);

 // cout << ((instruction >> 13) & 0x7) << endl;
 // cout << ((instruction >> 10) & 0x7) << endl;
 // cout << ((instruction >> 3) & 0x7) << endl;
 // cout << written_value << " " << emulator.GetRegisterValue((instruction >> 13) & 0x7) << endl;

  cout << "Value of register " << dec << ((instruction >> 13) & 0x7) << " after an instruction 0x" << hex << instruction << ":" << endl;
  cout << "In Bitty Core => " << dec << written_value << endl;
  cout << "In Bitty Emulator => " << dec << emulator.GetRegisterValue((instruction >> 13) & 0x7) << endl;

  assert(emulator.GetRegisterValue((instruction >> 13) & 0x7) == written_value);
}
