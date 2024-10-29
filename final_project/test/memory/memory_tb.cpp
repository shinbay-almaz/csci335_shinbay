#include <cstdint>
#include <iostream>
#include "Vmemory.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vmemory* memory = new Vmemory;

  // Set input signals of Instruction Memory to default
  memory->clk = 0;
  memory->addr = 0;

  auto toggle_clock = [&memory]() {
    memory->clk = !memory->clk;
    memory->eval();
  };

  // Initial evaluation to load instructions from disk
  memory->eval();

  // Read from "instructions.txt" file
  freopen("Instructions.txt", "r", stdin);

  // Compare each instruction fetched from generated text file and one fetched from Instruction Memory
  for (int i = 0; i < 256; i++) {
    // Set address to get instruction from Instruction Memory
    memory->addr = i;

    // Get instruction in one clock cycle
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Get expected instruction from generated text file
    int expected_instr;
    cin >> hex >> expected_instr;

    // Print for debug purposes
    cout << "Instruction at address 0x" << hex << i << ":" << endl;
    cout << hex << (int)memory->out << " (Instruction Memory)" << endl;
    cout << hex << expected_instr << " (Generated Text File)" << endl;

    // Check for consistency between generated text file and Instruction Memory
    assert(expected_instr == (int)memory->out);
  }

  cout << "All addresses have been checked and no errors are found!" << endl;

  delete memory;
  return 0;
}
