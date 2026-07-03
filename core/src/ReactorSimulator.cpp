#include "core/ReactorSimulator.hpp"
#include "ecs/System.hpp"
#include "scene/MainMenu.hpp"
#include "scene/SceneIF.hpp"
#include "scene/Simulation.hpp"
#include <cassert>
#include <chrono>
#include <memory>

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

void ReactorSimulator::Logic() { ecs::System::Update(mEcs, mInputData, kDt); }

// ---------------------------------------------------

void ReactorSimulator::Render() {

  // render data
  const auto &frontEcs{mEcs};
  mInputData = mRenderer.Update(frontEcs);
}

// ---------------------------------------------------

void ReactorSimulator::Run() {
  mScenes[scene::SIMULATION]->LoadScene(mEcs);

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
