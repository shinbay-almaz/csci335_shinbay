#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Valu.h"
#include "verilated.h"

using namespace std;

// Utility to format 16-bit values as binary strings
string format16(uint16_t val) {
  string res = "";
  for (int i = 0; i < 16; ++i) {
    res += (val & (1 << (15 - i))) ? '1' : '0';
  }
  return res;
}

// Print failed test case details
void printFailedTestCase(Valu* alu, uint16_t expected_out) {
  cout << "Test Failed!\n";
  cout << "Inputs:\n";
  cout << "in_a = " << format16(alu->in_a) << "\n";
  cout << "in_b = " << format16(alu->in_b) << "\n";
  cout << "select = " << (int)alu->select << "\n\n";

  cout << "Expected Outputs:\n";
  cout << "alu_out = " << format16(expected_out) << "\n";

  cout << "Actual Outputs:\n";
  cout << "alu_out = " << format16(alu->alu_out) << "\n";

  exit(1);  // Terminate on failure
}

// Utility function for ALU operations
uint16_t ALUOperation(uint16_t a, uint16_t b, int select) {
  switch (select) {
    case 0:
      return a + b;
    case 1:
      return a - b;
    case 2:
      return a & b;
    case 3:
      return a | b;
    case 4:
      return a ^ b;
    case 5:
      return a << (b & 0xF);
    case 6:
      return a >> (b & 0xF);
    case 7:
      return (a == b ? 0 : a > b ? 1 : 2);
    default:
      return 0;
  }
}

// Function to check ALU operations
void checkALU(Valu* alu, int select) {
  for (int t = 0; t < 1000; ++t) {
    uint16_t a = rand() & 0xFFFF;
    uint16_t b = rand() & 0xFFFF;

    alu->in_a = a;
    alu->in_b = b;
    alu->select = select;
    alu->eval();

    uint16_t expected_out = ALUOperation(a, b, select);

    if ((uint16_t)alu->alu_out != expected_out) {
      printFailedTestCase(alu, expected_out);
    }
  }
}

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  srand(time(0));

  Valu* alu = new Valu;

  // Testing ALU Operations
  cout << "Testing ALU Operations:\n";
  for (int select = 0; select < 8; ++select) {
    cout << "Testing ALU operation with select = " << select << "\n";
    checkALU(alu, select);
  }

  delete alu;
  cout << "All tests completed successfully!\n";
  return 0;
}
