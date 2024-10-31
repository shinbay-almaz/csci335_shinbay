#include <string>

class Assembler {
 private:
 public:
  Assembler() = default;
  int assemble(std::string program_file);
  int assemble_and_save(std::string input_file, std::string output_file);
};
