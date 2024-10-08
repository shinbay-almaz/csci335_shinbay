#include "Vmux.h"  
#include "verilated.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Vmux* mux = new Vmux;

  // Initialize the inputs for the MUX
  mux->in0 = 0;
  mux->in1 = 1;
  mux->in2 = 2;
  mux->in3 = 3;
  mux->in4 = 4;
  mux->in5 = 5;
  mux->in6 = 6;
  mux->in7 = 7;

  // Function to apply a MUX select value and print the result
  auto apply_mux_select = [&](int select) {
    mux->mux_sel = select;  // Apply the select input
    mux->eval();           
    cout << "MUX select = " << select << ", output = " << mux->out;

    // Check if the output is correct based on the selected input
    if (select < 10) {
      if (mux->out == select) {
        cout << " (OK)" << endl;
      } else {
        cout << " (WRONG)" << endl;
      }
    } else {
      if (mux->out == 0) {
        cout << " (OK)" << endl;
      } else {
        cout << " (WRONG)" << endl;
      }
    }
  };

  // Apply different MUX select values (0 to 15)
  cout << "Testing MUX with different select inputs:" << endl;
  for (int i = 0; i < 8; ++i) {
    apply_mux_select(i);
  }

  // Cleanup and exit
  mux->final();
  delete mux;

  return 0;
}

