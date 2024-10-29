#include <iostream>
#include "Vbitty_core.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vbitty_core* core = new Vbitty_core;

  auto toggle_clock = [&core]() {
    core->clk = !core->clk;
    core->eval();
  };

  // Set input signals of Bitty Core to default
  core->clk = 0;
  core->reset = 0;
  core->run = 0;

  // Set reset signal to HIGH
  core->reset = 1;
  toggle_clock();
  toggle_clock();

  // After applying reset, Bitty Core should initiate a Load Instruction From Memory State
  assert((int)core->done == 0);

  // Set reset signal to LOW and run signal to HIGH
  core->reset = 0;
  core->run = 1;

  // Execute every possible instruction and check Done signal
  for (int instruction = 0; instruction < (1 << 16); instruction++) {
    /* --- Load Instruction From Memory State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bitty Core should change its state to Fetch Instruction From Register State
    assert((int)core->done == 0);

    // Push instruction bits to Bitty Core
    core->instruction = instruction;

    /* --- Fetch Instruction From Register State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bityy Core should change its state to Save First Operand State
    assert((int)core->done == 0);

    /* --- Save First Operand State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bityy Core should change its state to Execute ALU State
    assert((int)core->done == 0);

    /* --- Execute ALU State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bityy Core should change its state to Update Register State
    assert((int)core->done == 1);

    /* --- Update Register State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bityy Core should change its state to Update PC State
    assert((int)core->done == 0);

    /* --- Update PC State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Bityy Core should change its state to Load Instruction From Memory State
    assert((int)core->done == 0);
  }
  cout
      << "All possible instructions have been executed and no errors are found!"
      << endl;

  delete core;
  return 0;
}
