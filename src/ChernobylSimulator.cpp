#include "ChernobylSimulator.hpp"
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "physics/Collision.hpp"
#include "utils/Configuration.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>

// ===================================================
// 1. Constructor / Destructor
// ===================================================

// ===================================================
// 2. Implementations
// ===================================================

std::mt19937
    gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> dist(0, 1);

void ChernobylSimulator::Logic() {
  Fuel last{};
  for (auto &particle : mParticles) {
    particle.y += particle.momentumY;
    particle.x += particle.momentumX;

    for (auto &fuel : mFuels) {
      if (fuel.triggered)
        continue;
      if (!Collision::OnEnter(fuel, particle))
        continue;
      particle.momentumY *= -1;

      fuel.triggered = true;
      particle.collided = true;
      fuel.color = {0x000000FF};

      last = fuel;
    }
  }

  mParticles.erase(
      std::remove_if(mParticles.begin(), mParticles.end(),
                     [](Particle &x) -> bool { return x.collided; }),
      mParticles.end());

  if (last.triggered) {
    mParticles.emplace_back(
        Particle{last.x, last.y, last.r, {0x777777FF}, 3, -3});
    mParticles.emplace_back(
        Particle{last.x, last.y, last.r, {0x777777FF}, 3, 0});
    mParticles.emplace_back(
        Particle{last.x, last.y, last.r, {0x777777FF}, 3, 3});
  }
}

// ---------------------------------------------------

void ChernobylSimulator::Render() {
  mRenderer.StartFrame();

  mRenderer.Clear(cnf::kBackgroundColor);

  for (const auto &fuel : mFuels)
    mRenderer.Circle(fuel.x, fuel.y, fuel.r, fuel.color);

  for (const auto &particle : mParticles)
    mRenderer.Circle(particle.x, particle.y, particle.r, particle.color);

  mRenderer.EndFrame();
}

// ---------------------------------------------------

void ChernobylSimulator::Run() {
  // auto width{mRenderer.GetWidthOfWindow()};
  auto height{mRenderer.GetHeightOfWindow()};
  mParticles.push_back(
      Particle(10, height * 0.5 - 20, 20, cnf::Color{0x777777FF}, 3, 0));

  mFuels.push_back(Fuel(300, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(600, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(900, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1200, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1500, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1800, height * 0.5 - 220, 40, cnf::Color{0x3333FFFF}));

  mFuels.push_back(Fuel(300, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(600, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(900, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1200, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1500, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1800, height * 0.5 - 20, 40, cnf::Color{0x3333FFFF}));

  mFuels.push_back(Fuel(300, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(600, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(900, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1200, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1500, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));
  mFuels.push_back(Fuel(1800, height * 0.5 + 180, 40, cnf::Color{0x3333FFFF}));

  while (!mRenderer.ShouldClose()) {
    Logic();
    Render();
  }
}
