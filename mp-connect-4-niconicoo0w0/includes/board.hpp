#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

enum class WinningDirection { kHorizontal, kVertical, kRightDiag, kLeftDiag };
enum class DiskType { kPlayer1 = 82, kPlayer2 = 66, kEmpty = 32 };

struct Board {
  static constexpr int kBoardWidth = 7;
  static constexpr int kBoardHeight = 6;
  DiskType board[kBoardHeight][kBoardWidth];
};

bool Horizontal(Board& b, DiskType disk);
bool Vertical(Board& b, DiskType disk);
bool Left(Board& b, DiskType disk);
bool Right(Board& b, DiskType disk);

void InitBoard(Board& b);
void DropDiskToBoard(Board& b, DiskType disk, int col);
bool CheckForWinner(Board& b, DiskType disk);
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check);
bool BoardLocationInBounds(int row, int col);

// provided
std::string BoardToStr(const Board& b);
std::string CenterStr(const std::string& str, int col_width);

#endif