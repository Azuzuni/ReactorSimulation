#pragma once
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"
struct Particle {
  util::PosType x{};
  util::PosType y{};
  float r{};
  util::Color color{util::kParticleColor};
  util::PosType momentumX{0};
  util::PosType momentumY{0};
  bool collided{false};
};
