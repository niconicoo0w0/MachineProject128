// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("tied" "[board_init]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2} 
  };
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("vertical" "[vertical_winner]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("horizontal" "[horizonta_winner]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("left" "[left_winner]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}



TEST_CASE("right" "[right_winner]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("no winner 1" "[no_winner_test_1]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("no winner 2" "[no_winner_test_2]") {
  Board b;
  InitBoard(b);
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2} 
  };
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = solution[i][j];
    }
  }
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(!CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("out of range 1", "[out_of_range_1]") {
  for (size_t i = 0; i < kBoardHeight; i++) {
    for (size_t j = 0; j < kBoardWidth; j++) {
      REQUIRE(BoardLocationInBounds(i, j));
    }
  }
}

TEST_CASE("out of range 2", "[out_of_range_2]") {
  for (size_t i = -200; i < 0; i++) {
    for (size_t j = -200; j < 0; j++) {
      REQUIRE(!BoardLocationInBounds(i, j));
    }
  }
}

TEST_CASE("out of range 3", "[out_of_range_3]") {
  for (size_t i = 200; i > kBoardHeight; i--) {
    for (size_t j = 200; j > kBoardWidth; j--) {
      REQUIRE(!BoardLocationInBounds(i, j));
    }
  }
}

TEST_CASE("out of range 4", "[out_of_range_4]") {

  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));

  InitBoard(student);
  bool nice_catch = false;

  for (int i = -99; i < 0; i++) {
    try {
      DropDiskToBoard(student, DiskType::kEmpty, i);
    } catch (std::runtime_error& runtime) {
      nice_catch = true;
      REQUIRE(nice_catch);
    }
  }
}
