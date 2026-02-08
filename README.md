# Tetris (C++ / SDL2)

Minimal Tetris clone focused on game logic with SDL2 rendering.

**Controls**
1. `Left` / `Right`: move
2. `Down`: soft drop
3. `Z` or `Up`: rotate
4. `Space` or `X`: hard drop
5. `R`: reset
6. `Esc`: quit

**macOS Build (Homebrew + CMake)**
1. Install SDL2:
```
brew install sdl2
```
2. Build:
```
cmake -S . -B build
cmake --build build
```
3. Run:
```
./build/tetris
```
