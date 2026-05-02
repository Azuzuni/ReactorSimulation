#include "ChernobylSimulator.hpp"
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "physics/Collision.hpp"
#include "utils/Configuration.hpp"

// ===================================================
// 1. Constructor / Destructor
// ===================================================

// ===================================================
// 2. Implementations
// ===================================================

void ChernobylSimulator::Logic() {
  for (auto &particle : mParticles) {
    particle.y += particle.momentumY;
    if (particle.y <= 0)
      particle.momentumY *= -1;

    for (auto &fuel : mFuels) {
      fuel.color = {0x0000FFFF};
      if(!Collision::OnEnter(fuel, particle)) continue;

      particle.momentumY *= -1;

      fuel.color = {0x000000FF};
    }

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
  // auto height{mRenderer.GetHeightOfWindow()};
  mParticles.push_back(Particle(550, 10, 10, cnf::Color{0xFF0000FF}, 0, 3));
  mFuels.push_back(Fuel(450, 700, 100, cnf::Color{0x0000FFFF}));

  while (!mRenderer.ShouldClose()) {
    Logic();
    Render();
  }
}
