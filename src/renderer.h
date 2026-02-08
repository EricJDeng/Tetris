#ifndef TETRIS_RENDERER_H
#define TETRIS_RENDERER_H

#include <SDL.h>
#include <array>

class Renderer {
public:
  Renderer(int screenWidth, int screenHeight, int blockSize);
  ~Renderer();

  bool IsReady() const;
  void Clear();
  void Present();

  void DrawBlock(int x, int y, int colorIndex);
  void DrawOutline(int x, int y, int w, int h);

  int BlockSize() const { return mBlockSize; }

private:
  SDL_Window* mWindow = nullptr;
  SDL_Renderer* mRenderer = nullptr;
  int mBlockSize = 0;
  std::array<SDL_Color, 8> mColors;
};

#endif
