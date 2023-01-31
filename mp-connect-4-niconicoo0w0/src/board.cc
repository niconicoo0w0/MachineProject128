#include "board.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cassert>
//board.hpp" "cassert" "cctype" "iomanip" 
//"iostream" "sstream" "stdexcept" "string"
/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  bool success = false;
  if (col < 0 || col > Board::kBoardWidth - 1) {
    throw std::runtime_error("invalid column");
  }
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      success = true;
    } 
    if (success) {
      break;
    }
  }
  if (!success) {
    throw std::runtime_error("All column is filled!");
  }
}

bool CheckForWinner(Board& b, DiskType disk){
  return (SearchForWinner(b, disk, WinningDirection::kHorizontal) || SearchForWinner(b, disk, WinningDirection::kVertical) || SearchForWinner(b, disk, WinningDirection::kRightDiag) || SearchForWinner(b, disk, WinningDirection::kLeftDiag));
}

bool Horizontal(Board& b, DiskType disk) {
  for (size_t row = 0; row < Board::kBoardHeight; row++) { //loop through rows
    for (size_t col = 0; col < Board::kBoardWidth - 3; col++) {
      if (b.board[row][col] == disk) {
        if (b.board[row][col] == b.board[row][col + 1] && b.board[row][col + 1] == b.board[row][col + 2] && b.board[row][col + 2] == b.board[row][col + 3]) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Vertical(Board& b, DiskType disk) {
  for (size_t col = 0; col < Board::kBoardWidth; col++) { //loop through rows
    for (size_t row = 0; row < Board::kBoardHeight - 3; row++) {
      if (b.board[row][col] == disk) {
        if (b.board[row][col] == b.board[row + 1][col] && b.board[row + 1][col] == b.board[row + 2][col] && b.board[row + 2][col] == b.board[row + 3][col]) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Left(Board& b, DiskType disk) {
  for (size_t col = 3; col < Board::kBoardWidth; col++) { //loop through rows
    for (size_t row = 0; row < 3; row++) {
      if (b.board[row][col] == disk) {
        if (b.board[row][col] == b.board[row + 1][col - 1] && b.board[row + 1][col - 1] == b.board[row + 2][col - 2] && b.board[row + 2][col - 2] == b.board[row + 3][col - 3]) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Right(Board& b, DiskType disk) {
  for (size_t col = 0; col < Board::kBoardWidth - 3; col++) { //loop through rows
    for (size_t row = 0; row < Board::kBoardHeight - 3; row++) {
      if (b.board[row][col] == disk) {
        if (b.board[row][col] == b.board[row + 1][col + 1] && b.board[row + 1][col + 1] == b.board[row + 2][col + 2] && b.board[row + 2][col + 2] == b.board[row + 3][col + 3]) {
          return true;
        }
      }
    }
  }
  return false;
}


bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check){
  if (to_check == WinningDirection::kHorizontal) {
    return Horizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return Vertical(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return Left(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return Right(b, disk);
  }
  return false;
}

bool BoardLocationInBounds(int row, int col){
  return row < Board::kBoardHeight && col < Board::kBoardWidth && row > -1 && col > -1;
}
