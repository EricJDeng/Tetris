#include "renderer.h"

Renderer::Renderer(int screenWidth, int screenHeight, int blockSize)
  : mBlockSize(blockSize) {
  mColors = {
    SDL_Color{20, 20, 20, 255},  // 0 empty
    SDL_Color{0, 240, 240, 255}, // I
    SDL_Color{240, 240, 0, 255}, // O
    SDL_Color{160, 0, 240, 255}, // T
    SDL_Color{0, 240, 0, 255},   // S
    SDL_Color{240, 0, 0, 255},   // Z
    SDL_Color{0, 0, 240, 255},   // J
    SDL_Color{240, 160, 0, 255}  // L
  };

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return;
  }

  mWindow = SDL_CreateWindow(
    "Tetris",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    screenWidth,
    screenHeight,
    SDL_WINDOW_SHOWN
  );

  if (!mWindow) return;

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!mRenderer) return;
}

Renderer::~Renderer() {
  if (mRenderer) SDL_DestroyRenderer(mRenderer);
  if (mWindow) SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

bool Renderer::IsReady() const {
  return mWindow && mRenderer;
}

void Renderer::Clear() {
  SDL_SetRenderDrawColor(mRenderer, 18, 18, 18, 255);
  SDL_RenderClear(mRenderer);
}

void Renderer::Present() {
  SDL_RenderPresent(mRenderer);
}

void Renderer::DrawBlock(int x, int y, int colorIndex) {
  if (!mRenderer) return;
  if (colorIndex < 0 || colorIndex >= static_cast<int>(mColors.size())) colorIndex = 0;

  SDL_Color c = mColors[colorIndex];
  SDL_SetRenderDrawColor(mRenderer, c.r, c.g, c.b, 255);
  SDL_Rect rect{ x, y, mBlockSize - 1, mBlockSize - 1 };
  SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::DrawOutline(int x, int y, int w, int h) {
  SDL_SetRenderDrawColor(mRenderer, 80, 80, 80, 255);
  SDL_Rect rect{ x, y, w, h };
  SDL_RenderDrawRect(mRenderer, &rect);
}
