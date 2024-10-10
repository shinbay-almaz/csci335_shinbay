#include <iostream>
#include <cassert>
#include "BittyEmulator.h"


int main()
{
    BittyEmulator emulator;

    // Test instruction 0x1200 (replace with actual instruction value)
    uint16_t testInstruction1 = 0x1200;
    emulator.Evaluate(testInstruction1);

    // Check register values after execution
    // Assuming instruction 0x1200 modifies register 0
    uint16_t regValue = emulator.GetRegisterValue(0);

    // Manually pre-calculate expected value.
    uint16_t expected_value = 4;
    std::cout << "Register 0 value: " << regValue << std::endl;
    assert(regValue == expected_value);

    // Continue testing other instructions as needed
    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction2 = 0xE200;
    emulator.Evaluate(testInstruction2);

    // Check register values after execution
    // Assuming instruction 0xE200 modifies register 
    regValue = emulator.GetRegisterValue(7);

    // Manually pre-calculate expected value.
    expected_value = 11;
    std::cout << "Register 7 value: " << regValue << std::endl;
    assert(regValue == expected_value);

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction3 = 0xE204;
    emulator.Evaluate(testInstruction3);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(7);

    // Manually pre-calculate expected value.
    expected_value = 7;
    std::cout << "Register 7 value: " << regValue << std::endl;
    assert(regValue == expected_value);

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction4 = 0b0110100000001000;
    emulator.Evaluate(testInstruction4);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(3);

    // Manually pre-calculate expected value.
    expected_value = 2;
    std::cout << "Register 3 value: " << regValue << std::endl;
    assert(regValue == expected_value);

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction5 = 0b0101000000001100;
    emulator.Evaluate(testInstruction5);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(2);

    // Manually pre-calculate expected value.
    expected_value = 6;
    std::cout << "Register 2 value: " << regValue << std::endl;
    assert(regValue == expected_value);

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction6 = 0b1101010000010000;
    emulator.Evaluate(testInstruction6);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(6);

    // Manually pre-calculate expected value.
    expected_value = 3;
    std::cout << "Register 6 value: " << regValue << std::endl;
    assert(regValue == expected_value); 

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction7 = 0b1010010000010100;
    emulator.Evaluate(testInstruction7);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(5);

    // Manually pre-calculate expected value.
    expected_value = 10;
    std::cout << "Register 5 value: " << regValue << std::endl;
    assert(regValue == expected_value); 

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction8 = 0b1000110000011000;
    emulator.Evaluate(testInstruction8);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(4);

    // Manually pre-calculate expected value.
    expected_value = 1;
    std::cout << "Register 4 value: " << regValue << std::endl;
    assert(regValue == expected_value); 

    // Test instruction 0x1234 (replace with actual instruction value)
    uint16_t testInstruction9 = 0b0011010000011100;
    emulator.Evaluate(testInstruction9);

    // Check register values after execution
    // Assuming instruction 0x1234 modifies register 0
    regValue = emulator.GetRegisterValue(1);

    // Manually pre-calculate expected value.
    expected_value = 2;
    std::cout << "Register 1 value: " << regValue << std::endl;
    assert(regValue == expected_value); 
    return 0;
}
