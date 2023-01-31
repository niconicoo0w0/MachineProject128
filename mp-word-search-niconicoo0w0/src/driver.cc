#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'h', 'l', 'l', 'o'},
                                        {'c', 'a', 'a', 'o', 'm'},
                                        {'a', 'e', 'a', 't', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);

  std::cout << wss.FindWord("haao", CheckDirection::kRightDiag);
  std::cout << wss.FindWord("cet", CheckDirection::kRightDiag);
  std::cout << wss.FindWord("alm", CheckDirection::kRightDiag);

}