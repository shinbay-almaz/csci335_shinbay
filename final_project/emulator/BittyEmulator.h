#include <cstdint>
#include <vector>

class BittyEmulator {
 public:
  BittyEmulator();
  void EvaluateALUOperation(uint16_t instruction);
  uint16_t GetRegisterValue(uint16_t reg_num);
  uint16_t GetMemoryValue(uint16_t mem_addr);
  uint16_t RunOneInstruction();
  void CheckConditionAndJump(uint16_t instruction);
  void ReadAndWriteMemory(utin16_t instruction);

 private:
  std::vector<uint16_t> registers_;
  std::vector<uint16_t> instructions_;
  std::vector<uint16_t> memory_;
  uint8_t PC;
  uint16_t last_ALU_result;
};
