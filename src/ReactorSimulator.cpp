#include "ReactorSimulator.hpp"
#include "elements/Particle.hpp"
#include "utils/Configuration.hpp"
#include <atomic>
#include <chrono>
#include <cstddef>
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

void ReactorSimulator::Logic() {
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
      auto &backParticleBuffer{
          mParticles[(mFrontBuffer.load(std::memory_order_acquire) + 1) %
                     kBufferCount]};
      const auto &frontParticleBuffer{
          mParticles[mFrontBuffer.load(std::memory_order_acquire)]};

      for (size_t i{}; i < frontParticleBuffer.size(); ++i) {
        const auto &frontParticle{frontParticleBuffer.at(i)};
        backParticleBuffer[i].x =
            frontParticle.x + frontParticle.momentumX * dt;
        backParticleBuffer[i].y =
            frontParticle.y + frontParticle.momentumY * dt;
      }

      accumulator -= dt;
      mFrameReady.store(true, std::memory_order_release);
      mFrameReady.notify_all();
      if (mWorkerRunning.load())
        mFrameReady.wait(true);
    }
  }
}

// ---------------------------------------------------

void ReactorSimulator::Render() {
  while (!mRenderer.ShouldClose()) {
    mRenderer.StartFrame();

    mRenderer.Clear(cnf::kBackgroundColor);
    const auto &particles{
        mParticles[mFrontBuffer.load(std::memory_order_acquire)]};
    for (const auto &particle : particles)
      mRenderer.Circle(particle.x, particle.y, particle.r, particle.color);

    mRenderer.EndFrame();

    if (mFrameReady.load(std::memory_order_acquire)) {
      mFrontBuffer.store((mFrontBuffer + 1) % kBufferCount,
                         std::memory_order_release);
      mFrameReady.store(false, std::memory_order_release);
      mFrameReady.notify_one();
    }
  }

  // just in case to ensure Logc() closes;
  if (mFrameReady.load(std::memory_order_acquire)) {
    mFrameReady.store(false, std::memory_order_release);
    mFrameReady.notify_one();
  }
}

// ---------------------------------------------------

void ReactorSimulator::Run() {
  // auto width{mRenderer.GetWidthOfWindow()};
  auto height{mRenderer.GetHeightOfWindow()};
  mParticles[0].push_back(Particle(10,
                                   static_cast<cnf::PosType>(height * 0.5 - 20),
                                   20, cnf::Color{0xFFFFFFAA}, 300, 0));

  mParticles[1].push_back(Particle(10,
                                   static_cast<cnf::PosType>(height * 0.5 - 20),
                                   20, cnf::Color{0xFFFFFFAA}, 300, 0));

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

  std::thread worker(&ReactorSimulator::Logic, this);
  Render();

  mWorkerRunning.store(false, std::memory_order_relaxed);
  worker.join();
}
