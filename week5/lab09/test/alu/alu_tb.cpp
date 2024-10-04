#include "Valu.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

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
void printFailedTestCase(Valu* alu, uint16_t expected_out, int expected_carry, int expected_compare) {
    cout << "Test Failed!\n";
    cout << "Inputs:\n";
    cout << "carry_in = " << (int)alu->carry_in << "\n";
    cout << "in_a = " << format16(alu->in_a) << "\n";
    cout << "in_b = " << format16(alu->in_b) << "\n";
    cout << "mode = " << (int)alu->mode << "\n";
    cout << "select = " << (int)alu->select << "\n\n";

    cout << "Expected Outputs:\n";
    cout << "carry_out = " << expected_carry << "\n";
    cout << "compare = " << expected_compare << "\n";
    cout << "alu_out = " << format16(expected_out) << "\n";

    cout << "Actual Outputs:\n";
    cout << "carry_out = " << (int)alu->carry_out << "\n";
    cout << "compare = " << (int)alu->compare << "\n";
    cout << "alu_out = " << format16(alu->alu_out) << "\n";

    exit(1); // Terminate on failure
}

uint16_t arithmeticOperation(uint16_t a, uint16_t b, int carry_in, int select, int* carry_out) {
    uint32_t result;
    switch (select) {
        case 0: 
            result = a + carry_in; // A
            break;
        case 1: 
            result = (a | b) + carry_in; // A + B
            break;
        case 2: 
            result = (a | (0xFFFF - b)) + carry_in; // A + B'
            break;
        case 3: 
            result = (0xFFFF + carry_in); // -1
            break;
        case 4: 
            result = (a | (a & (0xFFFF - b))) + carry_in; // A + AB'
            break;
        case 5: 
            result = (a | b) + (a & (0xFFFF - b)) + carry_in; // (A + B) plus AB'
            break;
        case 6: 
            result = a - b - 1 + carry_in; // A minus B minus 1
            break;
        case 7: 
            result = (a & (0xFFFF - b)) - 1 + carry_in; // AB' minus 1
            break;
        case 8: 
            result = a + (a & b) + carry_in; // A plus AB
            break;
        case 9: 
            result = a + b + carry_in; // A plus B
            break;
        case 10: 
            result = (a | (0xFFFF - b)) + (a & b) + carry_in; // (A + B') plus AB
            break;
        case 11: 
            result = (a & b) - 1 + carry_in; // AB minus 1
            break;
        case 12: 
            result = a + a + carry_in; // A plus A
            break;
        case 13: 
            result = (a | b) + a + carry_in; // (A + B) plus A
            break;
        case 14: 
            result = (a | (0xFFFF - b)) + a + carry_in; // (A + B') plus A
            break;
        case 15: 
            result = a - 1 + carry_in; // A minus 1
            break;
        default: 
            result = 0;
            break;
    }

    // Calculate carry_out
    *carry_out = (result > 0xFFFF) ? 1 : 0; // Set carry_out if result exceeds 16 bits

    return result & 0xFFFF; // Return the lower 16 bits of the result
}

// Utility function for logic operations
uint16_t logicOperation(uint16_t a, uint16_t b, int select) {
    switch (select) {
        case 0: return ~a;         // NOT A
        case 1: return ~(a | b);   // NOR
        case 2: return ~a & b;     // ~A AND B
        case 3: return 0;          // Always 0
        case 4: return ~(a & b);   // NAND
        case 5: return ~b;         // NOT B
        case 6: return a ^ b;      // XOR
        case 7: return a & ~b;     // A AND ~B
        case 8: return ~a | b;     // ~A OR B
        case 9: return ~(a ^ b);   // XNOR
        case 10: return b;         // B
        case 11: return a & b;     // A AND B
        case 12: return 1;         // Always 1
        case 13: return a | ~b;    // A OR ~B
        case 14: return a | b;     // A OR B
        case 15: return a;         // A
        default: return 0;
    }
}

// Function to check arithmetic operations
void checkArithmetic(Valu* alu, int select) {
    for (int carry_in = 0; carry_in <= 1; ++carry_in) {
        alu->carry_in = carry_in;
        for (int t = 0; t < 1000; ++t) {
            uint16_t a = rand() & 0xFFFF;
            uint16_t b = rand() & 0xFFFF;

            alu->in_a = a;
            alu->in_b = b;
            alu->select = select;
            alu->mode = 0; // Set mode to arithmetic
            alu->eval();

            int expected_carry;
            uint16_t expected_out = arithmeticOperation(a, b, carry_in, select, &expected_carry);
            int expected_compare = (a == b);

            if ((uint16_t) alu->alu_out != expected_out || (int) alu->carry_out != expected_carry || (int) alu->compare != expected_compare) {
                printFailedTestCase(alu, expected_out, expected_carry, expected_compare);
            }
        }
    }
}

// Function to check logic operations
void checkLogic(Valu* alu, int select) {
    for (int t = 0; t < 1000; ++t) {
        uint16_t a = rand() & 0xFFFF;
        uint16_t b = rand() & 0xFFFF;

        alu->in_a = a;
        alu->in_b = b;
        alu->select = select;
        alu->mode = 1; // Set mode to logic
        alu->eval();

        uint16_t expected_out = logicOperation(a, b, select);

        if ((uint16_t) alu->alu_out != expected_out) {
            printFailedTestCase(alu, expected_out, 0, 0); // Carry and compare are not used for logic
        }
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    srand(time(0));

    Valu* alu = new Valu;

    // Testing Logic Operations
    cout << "Testing Logic Operations:\n";
    for (int select = 0; select < 16; ++select) {
        cout << "Testing logic operation with select = " << select << "\n";
        checkLogic(alu, select);
    }
    cout << "All logic tests passed!\n";

    // Testing Arithmetic Operations
    cout << "Testing Arithmetic Operations:\n";
    for (int select = 0; select < 16; ++select) {
        cout << "Testing arithmetic operation with select = " << select << "\n";
        checkArithmetic(alu, select);
    }
    cout << "All arithmetic tests passed!\n";

    delete alu;
    cout << "All tests completed successfully!\n";
    return 0;
}

