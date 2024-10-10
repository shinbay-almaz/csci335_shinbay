#include "Vregister.h"  
#include "verilated.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vregister* reg = new Vregister;

    // Reset the register
    reg->reset = 1;
    reg->init_val = 0;
    reg->clk = 0;
    reg->enable = 0;
    reg->eval();  // Evaluate the register with reset
    reg->reset = 0;

    // Clock tick simulation
    auto toggle_clock = [&reg]() {
        reg->clk = !reg->clk;  // Toggle the clock signal
        reg->eval();           // Evaluate the register on clock edge
    };

    // Apply inputs and simulate clock edges
    auto apply_inputs = [&](int d_in, int enable) {
        reg->d_in = d_in;
        reg->enable = enable;
        toggle_clock();  // Rising edge
        toggle_clock();  // Falling edge
    };

    // Test the reset functionality
    cout << "Applying reset..." << endl;
    reg->reset = 1;
    toggle_clock();  // Simulate clock with reset
    cout << "d_out after reset: " << reg->d_out << endl;

    // Test without enabling (should retain value)
    cout << "Testing with enable = 0 (no change expected)..." << endl;
    reg->reset = 0;
    apply_inputs(0x0001, 0);  // Load some data but disable the register
    cout << "d_out after input with enable=0: " << reg->d_out << endl;

    // Test with enabling (should update the output)
    cout << "Testing with enable = 1 (value should change)..." << endl;
    apply_inputs(0xFFFF, 1);  // Load some data and enable the register
    cout << "d_out after input with enable=1: " << reg->d_out << endl;

    // Cleanup
    reg->final();
    delete reg;

    return 0;
}
