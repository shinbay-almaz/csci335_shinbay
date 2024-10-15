#include <iostream>
#include <cassert>
#include "BittyInstrGenerator.h"
#include "Vbitty_core.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv)
{
  Verilated::commandArgs(argc, argv);
  Vbitty_core* core = new Vbitty_core;

  BittyInstructionGenerator generator;
 
  auto toggle_clock = [&core]() {
    core->clk = !core->clk;
    core->eval();
  };

  core->reset = 1;
  core->clk = 1;
  core->run = 0; 
  toggle_clock();
  toggle_clock();

  core->reset = 0;
  core->run = 1;
  uint16_t instruction = generator.Generate();
  for (int i = 0; i < 1000000; i++) {
    core->instruction = instruction;
    toggle_clock();
    toggle_clock();

    instruction = generator.Generate();
    for (int i = 0; i < 3; i++) {
      toggle_clock();
      toggle_clock();
    }
  }

  cout << "No problems are found!" << endl;

  return 0;
}
