#include "Vor_gate.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vor_gate* or_gate = new Vor_gate;

  or_gate->a = 0, or_gate->b = 0;
  or_gate->eval();
  std::cout << "a = 0, b = 0 -> y = " << (int)or_gate->y << "\n";
  or_gate->a = 0, or_gate->b = 1;
  or_gate->eval();
  std::cout << "a = 0, b = 1 -> y = " << (int)or_gate->y << "\n";
  or_gate->a = 1, or_gate->b = 0;
  or_gate->eval();
  std::cout << "a = 1, b = 0 -> y = " << (int)or_gate->y << "\n";
  or_gate->a = 1, or_gate->b = 1;
  or_gate->eval();
  std::cout << "a = 1, b = 1 -> y = " << (int)or_gate->y << "\n";

  delete or_gate;
  return 0;
}
