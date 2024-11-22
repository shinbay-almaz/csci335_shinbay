#include "BittyInstrGenerator.h"
#include "emulator/BittyEmulator.h"

#include <cassert>
#include <cstdint>
#include <iostream>

BittyEmulator emulator = BittyEmulator();

using namespace std;

extern "C" void compare_results(uint16_t instruction, uint16_t written_value) {
  // Run Emulator to execute the current instruction at PC and check with the instruction from Core Module
  uint16_t expected_instruction = emulator.RunOneInstruction();
  cout << "Actual: " << hex << instruction << " Expected: " << hex
       << expected_instruction << endl;
  assert(expected_instruction == instruction);

  uint16_t instruction_format = instruction & 0x3;

  switch (instruction_format) {
    case 0:
    case 1: {
      cout << "Done ALU Operation" << endl;
      uint16_t rx = instruction >> 13 & 0x7;
      uint16_t expected_value = emulator.GetRegisterValue(rx);
      cout << "Written Value: " << dec << written_value
           << "\nExpected Value: " << dec << expected_value << endl;
      assert(written_value == expected_value);
      break;
    }
    case 2: {
      cout << "Done Jump Operation" << endl;
      break;
    }
    case 3: {
      cout << "Done Memory Operation" << endl;
      uint16_t rx = instruction >> 13 & 0x7;
      uint16_t ry = instruction >> 10 & 0x7;
      uint16_t is_write = instruction >> 2 & 0x1;
      uint16_t expected_addr = emulator.GetRegisterValue(ry);
      cout << "Expected Address: " << hex << expected_addr << endl;
      if (is_write) {
      //  uint16_t expected_addr = emulator.GetRegisterValue(ry);
      //  cout  << "Memory Address: " << hex << mem_addr 
      //       << "\nExpected Memory Address: " << hex << expected_addr << endl;
      //  assert(mem_addr == expected_addr);
        uint16_t expected_value = emulator.GetMemoryValue(expected_addr);
        cout << "Written Value To Memory: " << dec << written_value
             << "\nExpected Value: " << dec << expected_value << endl;
        assert(written_value == expected_value);
      } else {
        uint16_t expected_value = emulator.GetRegisterValue(rx);
        cout << "Written Value to Register: " << dec << written_value
             << "\nExpected Value: " << dec << expected_value << endl;
        assert(written_value == expected_value);
      }
      break;
    }
  }
  /*


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
  */
}
