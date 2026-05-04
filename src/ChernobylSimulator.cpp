#include "ChernobylSimulator.hpp"
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "physics/Collision.hpp"
#include "utils/Configuration.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <random>
#include <thread>

// ===================================================
// 1. Constructor / Destructor
// ===================================================

// ===================================================
// 2. Implementations
// ===================================================

std::mt19937 gen(static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()));
std::uniform_real_distribution<float> dist(0, 1);

void ChernobylSimulator::Logic() {
  using clock = std::chrono::high_resolution_clock;
  using seconds = std::chrono::duration<float>;

  const float tickRate = 120.0f;
  const float dt = 1.0f / tickRate;

  auto previous = clock::now();
  float accumulator = 0.0f;

  while (mWorkerRunning.load(std::memory_order_relaxed)) {
    auto now = clock::now();
    seconds frameTime = now - previous;
    previous = now;

    accumulator += frameTime.count();

    while (accumulator >= dt) {
      uint8_t current{mActiveBuffer.load(std::memory_order_acquire)};
      uint8_t next = (current + 1) % kBufferCount;

      auto &particles{mParticles[current]};

      for (auto &particle : particles) {
        particle.x += particle.momentumX;
        particle.y += particle.momentumY;
      }
      mActiveBuffer.store(next, std::memory_order_release);
      accumulator -= dt;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

// ---------------------------------------------------

void ChernobylSimulator::Render() {
  while (!mRenderer.ShouldClose()) {
    mRenderer.StartFrame();
    mRenderer.Clear(cnf::kBackgroundColor);

    uint8_t current = mActiveBuffer.load(std::memory_order_acquire);
    const auto &fuels{mFuels[current]};
    const auto &particles{mParticles[current]};

    for (const auto &fuel : fuels)
      mRenderer.Circle(fuel.x, fuel.y, fuel.r, fuel.color);

    for (const auto &particle : particles)
      mRenderer.Circle(particle.x, particle.y, particle.r, particle.color);

    mRenderer.EndFrame();
  }
}

// ---------------------------------------------------

void ChernobylSimulator::Run() {
  // auto width{mRenderer.GetWidthOfWindow()};
  auto height{mRenderer.GetHeightOfWindow()};
  mParticles[0].push_back(Particle(10,
                                   static_cast<cnf::PosType>(height * 0.5 - 20),
                                   20, cnf::Color{0xFFFFFFAA}, 3, 0));

  mParticles[1].push_back(Particle(10,
                                   static_cast<cnf::PosType>(height * 0.5 - 20),
                                   20, cnf::Color{0xFFFFFFAA}, 3, 0));

  mParticles[2].push_back(Particle(10,
                                   static_cast<cnf::PosType>(height * 0.5 - 20),
                                   20, cnf::Color{0xFFFFFFAA}, 3, 0));

  // mFuels[mInputId].push_back(Fuel(300, static_cast<cnf::PosType>(height * 0.5
  // - 20), 40,
  //                       cnf::Color{0x3333FFFF}));
  // mFuels[mInputId].push_back(Fuel(600, static_cast<cnf::PosType>(height * 0.5
  // - 20), 40,
  //                       cnf::Color{0x3333FFFF}));
  // mFuels[mInputId].push_back(Fuel(900, static_cast<cnf::PosType>(height * 0.5
  // - 20), 40,
  //                       cnf::Color{0x3333FFFF}));
  // mFuels[mInputId].push_back(Fuel(1200, static_cast<cnf::PosType>(height *
  // 0.5 - 20), 40,
  //                       cnf::Color{0x3333FFFF}));
  // mFuels[mInputId].push_back(Fuel(1500, static_cast<cnf::PosType>(height *
  // 0.5 - 20), 40,
  //                       cnf::Color{0x3333FFFF}));
  // mFuels[mInputId].push_back(Fuel(1800, static_cast<cnf::PosType>(height *
  // 0.5 - 20), 40,
  //                       cnf::Color{0x3333FFFF}));

  std::thread worker(&ChernobylSimulator::Logic, this);
  Render();

  mWorkerRunning.store(false, std::memory_order_relaxed);
  worker.join();
}
