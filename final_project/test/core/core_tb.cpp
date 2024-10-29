#include <iostream>
#include <cassert>
#include "Vcore.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv)
{
  Verilated::commandArgs(argc, argv);
  Vcore* core = new Vcore;
 
  auto toggle_clock = [&core]() {
    core->clk = !core->clk;
    core->eval();
  };
 
  // Set input signals of Core to default
  core->clk = 0;
  core->reset = 0;
  core->run = 0;

  // Apply reset signal 
  core->reset = 1;
  toggle_clock(); // Rising edge
  toggle_clock(); // Falling edge
  
  // Set reset signal to LOW and run signal to HIGH
  core->reset = 0;
  core->run = 1;

  // Simulate clock ticks
  for (int i = 0; i < 256; i++) {
    // Each instruction should take 6 clock cycles
    for (int j = 0; j < 6; j++) {
      toggle_clock();
      toggle_clock();
      if (j == 3) {
        assert((int)core->done == 1);
      }
    }
  }

  cout << "All generated instructions have been executed and no errors are found!" << endl;

  delete core;
  return 0;
}
