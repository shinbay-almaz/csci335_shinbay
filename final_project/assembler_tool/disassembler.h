#include <string>

class Disassembler {
 private:
 public:
  Disassembler() = default;
  int disassemble(std::string program_file);
  int disassemble_and_save(std::string input_file, std::string output_file);
};
