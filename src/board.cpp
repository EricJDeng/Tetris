#include "board.h"
#include "pieces.h"

Board::Board() {
  Clear();
}

void Board::Clear() {
  for (int x = 0; x < kWidth; ++x) {
    for (int y = 0; y < kTotalHeight; ++y) {
      mGrid[x][y] = 0;
    }
  }
}

bool Board::IsInside(int x, int y) const {
  return x >= 0 && x < kWidth && y >= 0 && y < kTotalHeight;
}

bool Board::IsEmpty(int x, int y) const {
  if (!IsInside(x, y)) return false;
  return mGrid[x][y] == 0;
}

void Board::SetCell(int x, int y, int value) {
  if (!IsInside(x, y)) return;
  mGrid[x][y] = value;
}

int Board::GetCell(int x, int y) const {
  if (!IsInside(x, y)) return 0;
  return mGrid[x][y];
}

void Board::LockPiece(int x, int y, int piece, int rotation) {
  for (int py = 0; py < Pieces::kSize; ++py) {
    for (int px = 0; px < Pieces::kSize; ++px) {
      if (Pieces::Block(piece, rotation, px, py) == 0) continue;
      int bx = x + px;
      int by = y + py;
      if (IsInside(bx, by)) {
        mGrid[bx][by] = piece + 1;
      }
    }
  }
}

int Board::ClearLines() {
  int cleared = 0;
  for (int y = kTotalHeight - 1; y >= 0; --y) {
    bool full = true;
    for (int x = 0; x < kWidth; ++x) {
      if (mGrid[x][y] == 0) {
        full = false;
        break;
      }
    }

    if (full) {
      ++cleared;
      for (int yy = y; yy > 0; --yy) {
        for (int x = 0; x < kWidth; ++x) {
          mGrid[x][yy] = mGrid[x][yy - 1];
        }
      }
      for (int x = 0; x < kWidth; ++x) {
        mGrid[x][0] = 0;
      }
      ++y; // re-check same row after collapsing
    }
  }
  return cleared;
}
