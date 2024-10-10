#include "BittyEmulator.h"
#include <iostream>

using namespace std;

BittyEmulator::BittyEmulator() 
{
  registers_.resize(8);
  registers_[0] = 0;
  registers_[1] = 1;
  registers_[2] = 2;
  registers_[3] = 3;
  registers_[4] = 4;
  registers_[5] = 5;
  registers_[6] = 6;
  registers_[7] = 7;
}

uint16_t BittyEmulator::GetRegisterValue(uint16_t reg_num) {
  return registers_[reg_num];
}

void BittyEmulator::Evaluate(uint16_t instruction)
{
  uint16_t rx = (instruction >> 13);      // First register number (read/write)
  uint16_t ry = (instruction >> 10) & 0x7; // Second register number (read)
 
  //cout << rx << " " << ry << "\n";

  uint16_t select = (instruction >> 2) & 0x7; // ALU select 
  
  uint16_t rx_val = GetRegisterValue(rx);
  uint16_t ry_val = GetRegisterValue(ry);

  //cout << rx_val << " " << ry_val << "\n";

  // Evaluate the result based on ALU select
  switch (select) {
    case 0: // add rx, ry
      rx_val += ry_val;
      break;
    case 1: // sub rx, ry
      rx_val -= ry_val;
      break;
    case 2: // and rx, ry
      rx_val &= ry_val;
      break;
    case 3: // or rx, ry
      rx_val |= ry_val;
      break;
    case 4: // xor rx, ry
      rx_val ^= ry_val;
      break;
    case 5: // shl rx, ry
      if (ry_val < 16) rx_val <<= ry_val;
      else rx_val = 0;
      break;
    case 6: // shr rx, ry
      if (ry_val < 16) rx_val >>= ry_val;
      else rx_val = 0;
      break;
    default: // cmp rx, ry
      rx_val = rx_val == ry_val ? 0 : rx_val > ry_val ? 1 : 2;
      break;
  }

  registers_[rx] = rx_val;
}
