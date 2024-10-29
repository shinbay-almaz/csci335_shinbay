#include <iostream>
#include "Vinstruction_fetch_unit.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vinstruction_fetch_unit* ifu = new Vinstruction_fetch_unit;

  auto toggle_clock = [&ifu]() {
    ifu->clk = !ifu->clk;
    ifu->eval();
  };

  // Set input signals of Instruction Fetch Unit to default
  ifu->clk = 0;
  ifu->reset = 0;
  ifu->done = 0;

  // Set reset signal to HIGH
  ifu->reset = 1;

  // Apply reset to Instruction Fetch Unit
  toggle_clock();  // Rising edge
  toggle_clock();  // Falling edge

  // Set reset signal to LOW
  ifu->reset = 0;

  // Read instructions from "instructions.txt" file
  freopen("instructions.txt", "r", stdin);

  // Compare each instruction from Instruction Fetch Unit and one from generated text file after each iteration
  for (int iter = 0; iter < 256; iter++) {
    // Instruction Fetch Unit should push PC address to Instruction Memory and return instruction at that address
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Get expected instruction from generated text file
    int expected_out;
    cin >> hex >> expected_out;

    cout << hex << expected_out << " " << hex << (int)ifu->out << endl;
    // Compare output of Instruction Fetch Unit and expected output
    assert((int)ifu->out == expected_out);

    // Assume that the execution of instruction is done
    ifu->done = 1;

    // Instruction Fetch should update its PC address
    toggle_clock();
    toggle_clock();

    // Reset done signal to default
    ifu->done = 0;
  }
  cout
      << "All instructions have been correctly fetched and no errors are found!"
      << endl;

  delete ifu;
  return 0;
}
