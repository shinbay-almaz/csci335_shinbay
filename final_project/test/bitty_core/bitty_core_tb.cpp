#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vbitty_core* core = new Vbitty_core;

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
  core->instruction = 0x1200;
  core->run = 1;
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0xE200;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0xE204;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b0110100000001000;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b0101000000001100;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b1101010000010000;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b1010010000010100;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b1000110000011000;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  core->instruction = 0b0011010000011100;
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";
  for (int i = 0; i < 3; i++) {
    toggle_clock();
    toggle_clock();
  }
  cout << "Done = " << (int)core->done << "\n";
  toggle_clock();
  toggle_clock();
  cout << "reg[0] = " << (int)core->reg0_out << "\n";
  cout << "reg[1] = " << (int)core->reg1_out << "\n";
  cout << "reg[2] = " << (int)core->reg2_out << "\n";
  cout << "reg[3] = " << (int)core->reg3_out << "\n";
  cout << "reg[4] = " << (int)core->reg4_out << "\n";
  cout << "reg[5] = " << (int)core->reg5_out << "\n";
  cout << "reg[6] = " << (int)core->reg6_out << "\n";
  cout << "reg[7] = " << (int)core->reg7_out << "\n";

  delete core; 
  return 0;
}
