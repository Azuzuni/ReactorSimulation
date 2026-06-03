#include "core/ReactorSimulator.h"
#include "ecs/System.h"
#include "raylib.h"
#include "scene/MainMenu.h"
#include "scene/SceneIF.h"
#include "scene/Simulation.h"
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>

// ===================================================
// 1. Constructor / Destructor
// ===================================================

ReactorSimulator::ReactorSimulator(int width, int height, const char *title)
    : mRenderer{width, height, title} {
  mScenes[scene::MAIN_MENU] = std::make_unique<scene::MainMenu>();
  mScenes[scene::SIMULATION] = std::make_unique<scene::Simulation>();

  Run();
}

// ===================================================
// 2. Implementations
// ===================================================

void ReactorSimulator::Logic() {
  if (IsKeyPressed(KEY_A)) {
    mScenes[scene::MAIN_MENU]->LoadScene(mEcs);
  } else if (IsKeyPressed(KEY_S)) {
    mScenes[scene::SIMULATION]->LoadScene(mEcs);
  } else {
    ecs::System::Update(mEcs, kDt);
  }
}

// ---------------------------------------------------

void ReactorSimulator::Render() {

  // render data
  const auto &frontEcs{mEcs};
  mRenderer.Update(frontEcs);
}

// ---------------------------------------------------

void ReactorSimulator::Run() {
  mScenes[scene::MAIN_MENU]->LoadScene(mEcs);

  using clock = std::chrono::high_resolution_clock;
  using seconds = std::chrono::duration<float>;

  auto previous{clock::now()};
  float accumulator{};

  while (!mRenderer.ShouldClose()) {
    auto now{clock::now()};
    seconds frameTime{now - previous};
    previous = now;
    accumulator += frameTime.count();
    while (accumulator >= kDt) {
      Logic();
      accumulator -= kDt;
    }
    Render();
  }
}
