#include <vector>
#include <cstdint>

class BittyEmulator {
public:
  BittyEmulator();
  void Evaluate(uint16_t instruction);
  uint16_t GetRegisterValue(uint16_t reg_num);

private:
  std::vector<uint16_t> registers_;

};
