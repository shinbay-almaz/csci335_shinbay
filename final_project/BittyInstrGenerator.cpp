#include "BittyInstrGenerator.h"
#include <random>
#include <ctime>

uint16_t BittyInstructionGenerator::Generate() {
  uint16_t instruction = 0;

  uint16_t rx = rand() & 0x7;
  uint16_t ry = rand() & 0x7;

  uint16_t alu_sel = rand() & 0x7;

  instruction = (rx << 13) + (ry << 10) + (alu_sel << 2);

  return instruction;
}
