#include "Vbranch_logic.h"
#include "verilated.h"

#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vbranch_logic* bl = new Vbranch_logic;

  // Set input signals of Branch Logic to default
  bl->pc = 0;
  bl->done = 0;
  bl->instruction = 0;
  bl->last_alu_result = 0;
  bl->eval();

  while ((int)bl->pc != 0xFF) {
    int jump_address = rand() & 0xFF;
    int cond = rand() % 3;
    int last_alu_result = rand() % 3;

    bl->done = 1;
    bl->instruction = (jump_address << 4) + (cond << 2) + 2;
    bl->last_alu_result = last_alu_result;
    bl->eval();

    int expected_next_pc = (int)bl->pc + 1;
    if (cond == last_alu_result) {
      cout << "Making a jump to address 0x" << hex << jump_address << endl;
      expected_next_pc = jump_address;
    } else {
      cout << "Moving to the next address 0x" << hex << (int)bl->pc + 1 << endl;
    }

    int next_pc = (int)bl->new_pc;
    cout << expected_next_pc << " " << (int)bl->new_pc << endl;

    assert(next_pc == expected_next_pc);

    bl->pc = next_pc;
  }

  delete bl;
  return 0;
}
