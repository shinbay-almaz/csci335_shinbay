#include "Vlock.h"
#include "verilated.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vlock *lock = new Vlock;

  vector<int> sequence{1, 3, 1, 3, 3, 0, 3, 3, 5, 9, 3, 3, 5, 2, 7, 3, 3, 5, 2, 5, 4, 3, 3, 5, 2, 5, 6};

  lock->reset = 1;
  lock->clk = 0;
  lock->eval();
  lock->reset = 0;

  for (int digit : sequence) {
    lock->digit = digit;

    lock->clk = !lock->clk;
    lock->eval();

    lock->clk = !lock->clk;
    lock->eval();

    if (lock->locked) {
      cout << "Locked after input " << digit << endl;
    } else {
      cout << "Unlocked after input " << digit << endl;
    }
  }

  if (lock->locked) {
    cout << "The output is not correct!" << endl; 
  } 

  delete lock;
  return 0;
}
