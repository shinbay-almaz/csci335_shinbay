#include "Vcontrol_unit.h"

#include "verilated.h"

#include <iostream>

#include <vector>

#include <cassert>

using namespace std;

enum State {
  LoadInstructionFromMemory,
  FetchInstructionFromReg,
  SaveFirstOperand,
  ExecuteALU,
  UpdateRegister,
  UpdatePC
};

vector<int> get_output_signals(Vcontrol_unit* control) {
  vector<int> output_signals;
  output_signals.push_back((int)control->done);
  output_signals.push_back((int)control->alu_sel);
  output_signals.push_back((int)control->mux_sel);
  output_signals.push_back((int)control->en_i);
  output_signals.push_back((int)control->en_s);
  output_signals.push_back((int)control->en_c);
  output_signals.push_back((int)control->en_0);
  output_signals.push_back((int)control->en_1);
  output_signals.push_back((int)control->en_2);
  output_signals.push_back((int)control->en_3);
  output_signals.push_back((int)control->en_4);
  output_signals.push_back((int)control->en_5);
  output_signals.push_back((int)control->en_6);
  output_signals.push_back((int)control->en_7);
  return output_signals;
}

void check_output_signals(Vcontrol_unit* control, State state) {
  vector<int> output_signals = get_output_signals(control);
  switch (state) {
    case State::LoadInstructionFromMemory: {
      cout << "Load Instruction From Memory" << endl;
      vector<int> expected_signals{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      assert(output_signals == expected_signals);
      break;
    }
    case State::FetchInstructionFromReg: {
      cout << "Get Instruction From Register" << endl;
      vector<int> expected_signals{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      assert(output_signals == expected_signals);
      break;
    }
    case State::SaveFirstOperand: {
      cout << "Save First Operand" << endl;
      vector<int> expected_signals{
          0, 0, (int)control->instruction >> 13, 0, 1, 0, 0, 0, 0, 0, 0, 0,
          0, 0};
      assert(output_signals == expected_signals);
      break;
    }
    case State::ExecuteALU: {
      cout << "Execute ALU" << endl;
      vector<int> expected_signals{0,
                                   (int)control->instruction >> 2 & 0x7,
                                   (int)control->instruction >> 10 & 0x7,
                                   0,
                                   0,
                                   1,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0};
      assert(output_signals == expected_signals);
      break;
    }
    case State::UpdateRegister: {
      cout << "Update Register" << endl;
      vector<int> expected_signals{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      expected_signals[(control->instruction >> 13) + 6] = 1;
      assert(output_signals == expected_signals);
      break;
    }
    case State::UpdatePC: {
      cout << "Update PC" << endl;
      vector<int> expected_signals{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      assert(output_signals == expected_signals);
      break;
    }
    default:
      assert(false);
  }
}

void print_control_unit_details(Vcontrol_unit* control, int instruction,
                                State state) {
  cout << "Executing the instruction 0x" << hex << instruction << " at state "
       << dec << (int)state << endl;
}

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vcontrol_unit* control = new Vcontrol_unit;

  auto toggle_clock = [&control]() {
    control->clk = !control->clk;
    control->eval();
  };

  // Set input signals of Control Unit to default
  control->clk = 0;
  control->reset = 0;
  control->run = 0;

  // Set reset signal to HIGH
  control->reset = 1;
  toggle_clock();  // Rising edge
  toggle_clock();  // Falling edge

  // After applying reset, a state of Control Unit should be Load Instruction From Memory State
  check_output_signals(control, State::LoadInstructionFromMemory);

  // Set reset signal to LOW and run signal to HIGH
  control->reset = 0;
  control->run = 1;

  // Execute every possible instruction and check output signals
  for (int instruction = 0; instruction < (1 << 16); instruction++) {
    /* --- Load Instruction From Memory State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction,
                               State::FetchInstructionFromReg);
    // Control Unit should change its state to Fetch Instruction From Register State
    check_output_signals(control, State::FetchInstructionFromReg);

    // Push instruction bits to Control Unit
    control->instruction = instruction;

    /* --- Fetch Instruction From Register State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction, State::SaveFirstOperand);
    // Control Unit should change its state to Save First Operand State
    check_output_signals(control, State::SaveFirstOperand);

    /* --- Save First Operand State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction, State::ExecuteALU);
    // Control Unit should change its state to Execute ALU State
    check_output_signals(control, State::ExecuteALU);

    /* --- Execute ALU State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction, State::UpdateRegister);
    // Control Unit should change its state to Update Register State
    check_output_signals(control, State::UpdateRegister);

    /* --- Update Register State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction, State::UpdatePC);
    // Control Unit should change its state to Update PC State
    check_output_signals(control, State::UpdatePC);

    /* --- Update PC State --- */
    toggle_clock();  // Rising edge
    toggle_clock();  // Falling edge

    // Debug
    print_control_unit_details(control, instruction,
                               State::LoadInstructionFromMemory);
    // Control Unit should change its state to Load Instruction From Memory State
    check_output_signals(control, State::LoadInstructionFromMemory);
  }

  cout << "All possible instructions have been tested and no errors are found!"
       << endl;

  delete control;
  return 0;
}
