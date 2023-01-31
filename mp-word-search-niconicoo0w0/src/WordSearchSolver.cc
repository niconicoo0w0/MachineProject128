#include "WordSearchSolver.hpp"
#include "CharPositions.hpp" 
#include "WordLocation.hpp" 
#include <cassert> 
#include <cctype> 
#include <cstddef> 
#include <iostream> 
#include <string> 
#include <vector>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle): puzzle_(puzzle) {
  //Initializes all of the object's data members with their respective values as derived from the puzzle argument.
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle[0].size();
}

WordLocation w1;
bool WordSearchSolver::Horizontal (const std::vector<std::vector<char>>& puzzle, const std::string& word) const {
  size_t match = 0;
  size_t i = 0;
  std::vector<CharPositions> char_positions;
  CharPositions charposition{};
  if (word.length() > puzzle_width_) {
    return false;
  }
  for (size_t row = 0; row < puzzle_height_; row++) {
    for (size_t column = 0; column < puzzle_width_; column++) {
      if (puzzle[row][column] == word[i]) {
        charposition.col = column;
        charposition.row = row;
        charposition.character = word[i];
        char_positions.push_back(charposition);
        match++;
        i++;
        if (match == word.length()) {
          w1 = WordLocation({word, char_positions});
          return true;
        }
      } else {
        char_positions.clear();
        match = 0;
        i = 0;
      }
    }
  }
  return false;
}

WordLocation w2;
bool WordSearchSolver::Vertical(const std::vector<std::vector<char>>& puzzle, const std::string& word) const {
  size_t match = 0;
  size_t i = 0;
  std::vector<CharPositions> char_positions;
  CharPositions charposition{};
  if (word.length() > puzzle_height_) {
    return false;
  }
  for (size_t column = 0; column < puzzle_width_; column++) {
    for (size_t row = 0; row < puzzle_height_; row++) {
      if (puzzle[row][column] == word[i]) {
        charposition.col = column;
        charposition.row = row;
        charposition.character = word[i];
        char_positions.push_back(charposition);
        match++;
        i++;
        if (match == word.length()) {
          w2 = WordLocation({word, char_positions});
          return true;
        }
      } else {
        char_positions.clear();
        match = 0;
        i = 0;
      }
    }
  }
  return false;
}

WordLocation w3;
bool WordSearchSolver::Left(const std::vector<std::vector<char>>& puzzle, const std::string& word) const {
  size_t match = 0;
  size_t i = 0;
  std::vector<CharPositions> char_positions;
  CharPositions charposition{};

  for (size_t column = puzzle_width_ - 1; column > word.length() - 2; column--) {
    for (size_t row = 0; row < puzzle_height_; row++) {
      if (puzzle[row][column] == word[i] && LocationInBounds(row, column)) {
        for (size_t c = column, r = row ; LocationInBounds(r, c); c--, r++) {
          if (puzzle[r][c] == word[i]) {
            charposition.col = c;
            charposition.row = r;
            charposition.character = word[i];
            char_positions.push_back(charposition);
            match++;
            i++;
            if (match == word.length()) {
              w3 = WordLocation({word, char_positions});
              return true;
            }
          } else {
            char_positions.clear();
            match = 0;
            i = 0;
          }
        }
      }
    }
  }
  return false;
}

WordLocation w4;
bool WordSearchSolver::Right (const std::vector<std::vector<char>>& puzzle, const std::string& word) const {
  size_t match = 0;
  size_t i = 0;
  std::vector<CharPositions> char_positions;
  CharPositions charposition{};
  if (word.length() > puzzle_height_) {
    return false;
  }
  for (size_t row = 0; row < puzzle_height_ - word.length() + 1; row++) {
    for (size_t column = 0; column < puzzle_width_; column++) {
      if (puzzle[row][column] == word[i] && LocationInBounds(row, column)) {
        for (size_t c = column, r = row ; LocationInBounds(r, c); c++, r++) {
          if (puzzle[r][c] == word[i]) {
            charposition.col = c;
            charposition.row = r;
            charposition.character = word[i];
            char_positions.push_back(charposition);
            match++;
            i++;
            if (match == word.length()) {
              w4 = WordLocation({word, char_positions});
              return true;
            }
          } else {
            char_positions.clear();
            match = 0;
            i = 0;
          }
        }
      }
    }
  }
  return false;
}


WordLocation WordSearchSolver::FindWord(const std::string& word){
  //This FindWord behavior searches for a given word inside this puzzle_ object for each member of the enum class CheckDirection. 
  //If the word is found, a non-empty WordLocation object is returned, the composition for which is described earlier. 
  //Otherwise, this FindWord behavior returns an empty WordLocation object (return WordLocation{};)
  if (WordSearchSolver::Horizontal(puzzle_, word)) {
    return w1;
  }
  if (WordSearchSolver::Vertical(puzzle_, word)) {
    return w2;
  }
  if (WordSearchSolver::Left(puzzle_, word)) {
    return w3;
  }
  if (WordSearchSolver::Right(puzzle_, word)) {
    return w4;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction){
  //This FindWord behavior searches for a given word inside this puzzle_ object. To invoke this behavior, two arguments are required: 
  //(1) an std::string object containing the word to find within the puzzle; 
  //(2) the CheckDirection (kHorizontal, kVertical, kLeftDiag, kRightDiag) to search for that word. FindWord returns a non-empty WordLocation 
  //if the word is found; an empty WordLocation object (return WordLocation{};) is returned otherwise.
  if (direction == CheckDirection::kHorizontal) {
    if (WordSearchSolver::Horizontal(puzzle_, word)) {
      return w1;
    }
  }

  if (direction == CheckDirection::kVertical) {
    if (WordSearchSolver::Vertical(puzzle_, word)) {
      return w2;
    }
  }

  if (direction == CheckDirection::kLeftDiag) {
    if (WordSearchSolver::Left(puzzle_, word)) {
      return w3;
    }
  }
  
  if (direction == CheckDirection::kRightDiag) {
    if (WordSearchSolver::Right(puzzle_, word)) {
      return w4;
    }
  }
  return WordLocation{};
}