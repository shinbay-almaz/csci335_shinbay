#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include "BittyInstructionGenerator.h"

uint16_t BittyInstructionGenerator::Generate() {
  uint16_t instruction = 0;

  uint16_t rx = rand() & 0x7;
  uint16_t ry = rand() & 0x7;

  uint16_t alu_sel = rand() & 0x7;

  instruction = (rx << 13) + (ry << 10) + (alu_sel << 2);

  return instruction;
}

using namespace std;

int main(int argc, char** argv) {
  srand(time(0));
  int N = stoi(argv[1]);

  BittyInstructionGenerator generator;

  freopen("instructions.txt", "w", stdout);

  for (int i = 0; i < N; i++) {
    uint16_t instruction = generator.Generate();

    cout << hex << instruction << endl;
  }
}
