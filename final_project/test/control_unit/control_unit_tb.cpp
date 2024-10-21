#include "Vcontrol_unit.h"

#include "verilated.h"

#include <iostream>

using namespace std;

// Checker function to verify control signals
bool check_control_signals(Vcontrol_unit* control, int state) {
  bool is_correct = true;

  // Extracting parts of the instruction
  uint16_t expected_mux_sel = (control->instruction >> 13) & 0x7;  // Bits [15:13]
  uint16_t expected_alu_sel = (control->instruction >> 2) & 0x7;   // Bits [4:2]
  
  uint16_t mux_sel = control->mux_sel;
  uint16_t alu_sel = control->alu_sel;
  int en_i = control->en_i, en_s = control->en_s, en_c = control->en_c;
  int en_0 = control->en_0, en_1 = control->en_1, en_2 = control->en_2, en_3 = control->en_3;
  int en_4 = control->en_4, en_5 = control->en_5, en_6 = control->en_6, en_7 = control->en_7;
  int done = control->done;

  switch (state) {
    case 0: 
    case 1:
      is_correct &= (en_i == 0 && en_s == 0 && en_c == 0);
      is_correct &= (mux_sel == 0 && alu_sel == 0 && done == 0);
      is_correct &= (en_0 == 0 && en_1 == 0 && en_2 == 0 && en_3 == 0);
      is_correct &= (en_4 == 0 && en_5 == 0 && en_6 == 0 && en_7 == 0);
      break;
    case 2: // State0: expect en_i = 1, others 0
      is_correct &= (en_i == 1 && en_s == 0 && en_c == 0);
      is_correct &= (mux_sel == 0 && alu_sel == 0 && done == 0);
      is_correct &= (en_0 == 0 && en_1 == 0 && en_2 == 0 && en_3 == 0);
      is_correct &= (en_4 == 0 && en_5 == 0 && en_6 == 0 && en_7 == 0);
      break;
    case 3: // State1: expect en_s = 1 and mux_sel = instruction[15:13]
      is_correct &= (en_s == 1 && en_i == 0 && en_c == 0);
      is_correct &= (mux_sel == expected_mux_sel && done == 0);
      is_correct &= (en_0 == 0 && en_1 == 0 && en_2 == 0 && en_3 == 0);
      is_correct &= (en_4 == 0 && en_5 == 0 && en_6 == 0 && en_7 == 0);
      break;
    case 4: // State2: expect en_c = 1, mux_sel = instruction[12:10], alu_sel = instruction[4:2]
      is_correct &= (en_c == 1 && en_i == 0 && en_s == 0);
      is_correct &= (mux_sel == ((control->instruction >> 10) & 0x7));
      is_correct &= (alu_sel == expected_alu_sel && done == 0);
      is_correct &= (en_0 == 0 && en_1 == 0 && en_2 == 0 && en_3 == 0);
      is_correct &= (en_4 == 0 && en_5 == 0 && en_6 == 0 && en_7 == 0);
      break;
    case 5: // State3: expect correct enable signals based on instruction[15:13]
      is_correct &= (done == 1);
      switch (expected_mux_sel) {
        case 0: is_correct &= en_0 == 1; break;
        case 1: is_correct &= en_1 == 1; break;
        case 2: is_correct &= en_2 == 1; break;
        case 3: is_correct &= en_3 == 1; break;
        case 4: is_correct &= en_4 == 1; break;
        case 5: is_correct &= en_5 == 1; break;
        case 6: is_correct &= en_6 == 1; break;
        case 7: is_correct &= en_7 == 1; break;
        default: is_correct = false;  // Invalid mux selection
      }
      break;
    default:
      is_correct = false; // Invalid state
  }

  return is_correct;
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Vcontrol_unit* control = new Vcontrol_unit;

  // Clock tick simulation
  auto toggle_clock = [&control]() {
    control->clk = !control->clk; // Toggle the clock signal
    control->eval();              // Evaluate the register on clock edge
  };

  auto do_clock_cycle = [&toggle_clock]() {
    toggle_clock();
    toggle_clock();
  };

  cout << "Applying reset..." << endl;
  control->reset = 1;
  control->clk = 0;
  do_clock_cycle();
  control->reset = 0;

  for (int instr = 0; instr < (1 << 16); ++instr) {
    control->instruction = instr;
    control->run = 1;
    // Simulate the control unit for 4 clock cycles (enough to move through the FSM)
    for (int cycle = 0; cycle < 6; ++cycle) {
      // Check correctness using the checker function
      bool correct = check_control_signals(control, cycle);

      if (!correct) {
        cout << "Error: Incorrect control signals for instruction 0x" << hex << instr;
        cout << " at cycle " << dec << cycle << endl;
        exit(1);
      } 
      if (control->done) {
        cout << "Done signal activated on instruction 0x" << hex << instr << endl;
      }
      do_clock_cycle();
    }
  }

  // Cleanup
  control->final();
  delete control;

  return 0;
}
