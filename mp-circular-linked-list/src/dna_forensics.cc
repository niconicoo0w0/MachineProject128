#include <iostream>
#include <fstream>
#include "functions.hpp"
#include <vector>
#include "utilities.hpp"

std::vector<std::string> filebyline;
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::ifstream ifs{argv[1]};
  for (std::string line; std::getline(ifs, line); line ="") {
    filebyline.push_back(line);
  }
  const std::string& word = argv[2];
  std::cout << RESULT(word, filebyline) << std::endl;
}