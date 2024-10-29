#include <vector>
#include <cstdint>

class BittyEmulator {
public:
  BittyEmulator();
  void Evaluate(uint16_t instruction);
  uint16_t GetRegisterValue(uint16_t reg_num);
  uint16_t RunOneInstruction();

private:
  std::vector<uint16_t> registers_;
  std::vector<uint16_t> memory_;
  uint8_t PC;
};
