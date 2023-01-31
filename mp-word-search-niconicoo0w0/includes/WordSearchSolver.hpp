#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  bool Horizontal (const std::vector<std::vector<char>>& puzzle, const std::string& word) const;
  bool Vertical(const std::vector<std::vector<char>>& puzzle, const std::string& word) const;
  bool Right(const std::vector<std::vector<char>>& puzzle, const std::string& word) const;
  bool Left(const std::vector<std::vector<char>>& puzzle, const std::string& word) const;

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif