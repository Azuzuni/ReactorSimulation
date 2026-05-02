#pragma once
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"
struct Particle {
  cnf::PosType x{};
  cnf::PosType y{};
  float r{};
  cnf::Color color{cnf::kParticleColor};
  float momentumX{};
  float momentumY{};
  bool collided{false};
};
