#include <cstdint>

class BittyInstructionGenerator {
 public:
  BittyInstructionGenerator() = default;
  uint16_t Generate(int N);

 private:
  bool can_be_branch = false;
};
