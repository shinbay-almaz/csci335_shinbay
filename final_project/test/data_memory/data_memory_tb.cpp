#include "verilated.h"
#include "Vdata_memory.h"

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vdata_memory* memory = new Vdata_memory;
  srand(time(0));

  const int MEM_SZ = (1 << 16);

  vector<int> expected_memory = vector<int>(MEM_SZ);

  // Default values
  memory->data_in = 0;
  memory->read = 0;
  memory->write = 0;
  memory->mem_addr = 0;

  for (int iter = 0; iter < 100000; iter++) {
    int data = rand() & 0xFFFF;
    int mem_addr = rand() & 0xFFFF;
    if (rand() & 1) { // WRITE
      expected_memory[mem_addr] = data;
      
      memory->mem_addr = mem_addr;
      memory->data_in = data;
      memory->write = 1;
      memory->read = 0;
      memory->eval();

      assert((int)memory->data_out == data);
    } else { // READ
      memory->mem_addr = mem_addr;
      memory->write = 0;
      memory->read = 1;
      memory->eval();

      assert((int)memory->data_out == expected_memory[mem_addr]);
    }
  }

  delete memory;
  return 0;
}
