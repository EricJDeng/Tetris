#include "game.h"
#include "renderer.h"
#include "pieces.h"

#include <SDL.h>
#include <cstdint>

// Main documentation
static constexpr int kBlockSize = 30;
static constexpr int kMargin = 20;
static constexpr int kBoardWidthPx = Board::kWidth * kBlockSize;
static constexpr int kBoardHeightPx = Board::kHeight * kBlockSize;
static constexpr int kSidePanelWidth = 6 * kBlockSize;

static void DrawPiece(Renderer& renderer, int baseX, int baseY, int piece, int rotation) {
  for (int y = 0; y < Pieces::kSize; ++y) {
    for (int x = 0; x < Pieces::kSize; ++x) {
      if (Pieces::Block(piece, rotation, x, y) == 0) continue;
      renderer.DrawBlock(baseX + x * kBlockSize, baseY + y * kBlockSize, piece + 1);
    }
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  const int screenWidth = kMargin * 3 + kBoardWidthPx + kSidePanelWidth;
  const int screenHeight = kMargin * 2 + kBoardHeightPx;

  Renderer renderer(screenWidth, screenHeight, kBlockSize);
  if (!renderer.IsReady()) {
    return 1;
  }

  Game game;

  uint32_t lastDrop = SDL_GetTicks();
  const uint32_t dropIntervalMs = 700;

  bool running = true;
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = false;
            break;
          case SDLK_LEFT:
            if (!game.IsGameOver()) game.MoveLeft();
            break;
          case SDLK_RIGHT:
            if (!game.IsGameOver()) game.MoveRight();
            break;
          case SDLK_DOWN:
            if (!game.IsGameOver()) game.MoveDown();
            break;
          case SDLK_UP:
          case SDLK_z:
            if (!game.IsGameOver()) game.Rotate();
            break;
          case SDLK_SPACE:
          case SDLK_x:
            if (!game.IsGameOver()) game.HardDrop();
            break;
          case SDLK_r:
            game.Reset();
            break;
          default:
            break;
        }
      }
    }

    uint32_t now = SDL_GetTicks();
    if (!game.IsGameOver() && now - lastDrop >= dropIntervalMs) {
      game.UpdateDrop();
      lastDrop = now;
    }

    renderer.Clear();

    const int boardX = kMargin;
    const int boardY = kMargin;

    // Board outline
    renderer.DrawOutline(boardX - 1, boardY - 1, kBoardWidthPx + 2, kBoardHeightPx + 2);

    // Draw locked blocks
    const Board& board = game.GetBoard();
    for (int y = Board::kHidden; y < Board::kTotalHeight; ++y) {
      for (int x = 0; x < Board::kWidth; ++x) {
        int cell = board.GetCell(x, y);
        if (cell == 0) continue;
        int px = boardX + x * kBlockSize;
        int py = boardY + (y - Board::kHidden) * kBlockSize;
        renderer.DrawBlock(px, py, cell);
      }
    }

    // Draw current piece
    if (!game.IsGameOver()) {
      for (int py = 0; py < Pieces::kSize; ++py) {
        for (int px = 0; px < Pieces::kSize; ++px) {
          if (Pieces::Block(game.CurrentPiece(), game.CurrentRotation(), px, py) == 0) continue;
          int bx = game.CurrentX() + px;
          int by = game.CurrentY() + py;
          if (by < Board::kHidden) continue;
          int sx = boardX + bx * kBlockSize;
          int sy = boardY + (by - Board::kHidden) * kBlockSize;
          renderer.DrawBlock(sx, sy, game.CurrentPiece() + 1);
        }
      }
    }

    // Next piece preview
    const int previewX = boardX + kBoardWidthPx + kMargin;
    const int previewY = boardY + kBlockSize * 2;
    renderer.DrawOutline(previewX - 1, previewY - 1, kBlockSize * 4 + 2, kBlockSize * 4 + 2);
    DrawPiece(renderer, previewX, previewY, game.NextPiece(), game.NextRotation());

    renderer.Present();
  }

  return 0;
}
