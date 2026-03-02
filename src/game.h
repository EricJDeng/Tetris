#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "board.h"


// logic
class Game {
public:
  Game();

  void Reset();
  bool IsGameOver() const;

  void MoveLeft();
  void MoveRight();
  void MoveDown();
  void Rotate();
  void HardDrop();

  void UpdateDrop();

  int CurrentPiece() const { return mPiece; }
  int CurrentRotation() const { return mRotation; }
  int CurrentX() const { return mX; }
  int CurrentY() const { return mY; }

  int NextPiece() const { return mNextPiece; }
  int NextRotation() const { return mNextRotation; }

  const Board& GetBoard() const { return mBoard; }

private:
  Board mBoard;
  int mPiece = 0;
  int mRotation = 0;
  int mX = 3;
  int mY = -2;

  int mNextPiece = 0;
  int mNextRotation = 0;

  bool mGameOver = false;

  bool IsValidPosition(int x, int y, int piece, int rotation) const;
  void SpawnPiece();
  void LockAndClear();
};

#endif
