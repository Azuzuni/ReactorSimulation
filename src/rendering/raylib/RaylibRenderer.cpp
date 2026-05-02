#include "raylib.h"
#include "rendering/raylib/RaylibRender.hpp"

// ===================================================
// 1. Constructor / Destructor
// ===================================================

RaylibRender::RaylibRender(int width, int height, const char *title) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
  InitWindow(width, height, title);
  SetTargetFPS(60);
}

RaylibRender::~RaylibRender() { CloseWindow(); }

// ===================================================
// 2. Implementations
// ===================================================

int RaylibRender::GetWidthOfWindowImpl() const noexcept {
  return GetScreenWidth();
}
int RaylibRender::GetHeightOfWindowImpl() const noexcept {
  return GetScreenHeight();
}
float RaylibRender::GetDeltaTimeImpl() const noexcept { return GetFrameTime(); }

// ---------------------------------------------------

bool RaylibRender::ShouldCloseImpl() const noexcept {
  return WindowShouldClose();
}
void RaylibRender::StartFrameImpl() const noexcept { BeginDrawing(); }
void RaylibRender::EndFrameImpl() const noexcept { EndDrawing(); }

// ---------------------------------------------------

void RaylibRender::ClearImpl(const cnf::Color &color) const noexcept {
  ClearBackground(Color(color.r, color.g, color.b, color.a));
}
void RaylibRender::CircleImpl(cnf::PosType x, cnf::PosType y, float r,
                              const cnf::Color &color) const noexcept {
  DrawCircle(x, y, r, Color(color.r, color.g, color.b, color.a));
}
void RaylibRender::RectImpl(cnf::PosType x, cnf::PosType y, cnf::PosType width,
                           cnf::PosType height,
                           const cnf::Color &color) const noexcept {
  DrawRectangle(x, y, width, height, Color(color.r, color.g, color.b, color.a));
}
