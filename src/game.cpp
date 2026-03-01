#include "game.h"
#include "pieces.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
  Reset();
}

void Game::Reset() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  mBoard.Clear();
  mNextPiece = std::rand() % Pieces::kPieceCount;
  mNextRotation = std::rand() % Pieces::kRotations;
  SpawnPiece();
  mGameOver = false;
}

bool Game::IsGameOver() const {
  return mGameOver;
}

bool Game::IsValidPosition(int x, int y, int piece, int rotation) const {
  for (int py = 0; py < Pieces::kSize; ++py) {
    for (int px = 0; px < Pieces::kSize; ++px) {
      if (Pieces::Block(piece, rotation, px, py) == 0) continue;
      int bx = x + px;
      int by = y + py;

      if (bx < 0 || bx >= Board::kWidth || by >= Board::kTotalHeight) {
        return false;
      }
      if (by >= 0 && !mBoard.IsEmpty(bx, by)) {
        return false;
      }
    }
  }
  return true;
}

void Game::SpawnPiece() {
  mPiece = mNextPiece;
  mRotation = mNextRotation;
  mX = 3;
  mY = -2;

  mNextPiece = std::rand() % Pieces::kPieceCount;
  mNextRotation = std::rand() % Pieces::kRotations;

  if (!IsValidPosition(mX, mY, mPiece, mRotation)) {
    mGameOver = true;
  }
}

void Game::LockAndClear() {
  mBoard.LockPiece(mX, mY, mPiece, mRotation);
  mBoard.ClearLines();
  SpawnPiece();
}

void Game::MoveLeft() {
  if (IsValidPosition(mX - 1, mY, mPiece, mRotation)) {
    --mX;
  }
}

void Game::MoveRight() {
  if (IsValidPosition(mX + 1, mY, mPiece, mRotation)) {
    ++mX;
  }
}

void Game::MoveDown() {
  if (IsValidPosition(mX, mY + 1, mPiece, mRotation)) {
    ++mY;
  } else {
    LockAndClear();
  }
}

void Game::Rotate() {
  int next = (mRotation + 1) % Pieces::kRotations;
  if (IsValidPosition(mX, mY, mPiece, next)) {
    mRotation = next;
  }
}

void Game::HardDrop() {
  while (IsValidPosition(mX, mY + 1, mPiece, mRotation)) {
    ++mY;
  }
  LockAndClear();
}

void Game::UpdateDrop() {
  if (!mGameOver) {
    MoveDown();
  }
}
