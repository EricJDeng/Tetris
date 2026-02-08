#ifndef TETRIS_PIECES_H
#define TETRIS_PIECES_H

class Pieces {
public:
  static constexpr int kPieceCount = 7;
  static constexpr int kRotations = 4;
  static constexpr int kSize = 4; // 4x4 matrix

  static int Block(int piece, int rotation, int x, int y);
};

#endif
