#include "Vbranch_logic.h"
#include "verilated.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vbranch_logic* bl = new Vbranch_logic;

  // Set input signals of Branch Logic to default
  bl->pc = 0;
  bl->done = 0;
  bl->eval();

  for (int i = 0; i < 255; i++) {
    bl->done = 1;
    bl->eval();

    int next_pc = (int)bl->new_pc;
  
    cout << (int)bl->pc << " " << (int)bl->new_pc << endl;

    assert(next_pc == (int)bl->pc + 1);

    bl->pc = next_pc;
  }

  delete bl;
  return 0;
}


