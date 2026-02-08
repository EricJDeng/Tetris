#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <array>

class Board {
public:
  static constexpr int kWidth = 10;
  static constexpr int kHeight = 20;
  static constexpr int kHidden = 2;
  static constexpr int kTotalHeight = kHeight + kHidden;

  Board();

  void Clear();
  bool IsEmpty(int x, int y) const;
  bool IsInside(int x, int y) const;
  void SetCell(int x, int y, int value);
  int GetCell(int x, int y) const;

  void LockPiece(int x, int y, int piece, int rotation);
  int ClearLines();

private:
  std::array<std::array<int, kTotalHeight>, kWidth> mGrid;
};

#endif
