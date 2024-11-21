#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include "BittyInstructionGenerator.h"

uint16_t BittyInstructionGenerator::Generate(int N) {
  uint16_t instruction = 0;
  uint16_t format = rand() % (3 + can_be_branch);
  if (format == 0) {
    uint16_t rx = rand() & 0x7;
    uint16_t ry = rand() & 0x7;
    uint16_t alu_sel = rand() & 0x7;
    can_be_branch = (alu_sel == 7);
    instruction = (rx << 13) + (ry << 10) + (alu_sel << 2) + format;
  } else if (format == 1) {
    uint16_t rx = rand() & 0x7;
    uint16_t immediate = rand() & 0xFF;
    uint16_t alu_sel = rand() & 0x7;
    can_be_branch = (alu_sel == 7);
    instruction = (rx << 13) + (immediate << 5) + (alu_sel << 2) + format;
  } else if (format == 2) {
    uint16_t rx = rand() & 0x7;
    uint16_t ry = rand() & 0x7;
    uint16_t ls_bit = rand() & 0x1;
    can_be_branch = false;
    instruction = (rx << 13) + (ry << 10) + (ls_bit << 2) + 3;
  } else {
    uint16_t immediate = rand() % N;
    uint16_t cond = rand() % 3;
    can_be_branch = true;
    instruction = (immediate << 4) + (cond << 2) + 2; 
  }
  return instruction;
}

using namespace std;

int main(int argc, char** argv) {
  srand(time(0));
  int N = stoi(argv[1]);

  BittyInstructionGenerator generator;

  freopen("instructions.txt", "w", stdout);

  for (int i = 0; i < N; i++) {
    uint16_t instruction = generator.Generate(N);
    cout << hex << instruction << endl;
  }
}
