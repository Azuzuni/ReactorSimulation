#pragma once
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"
struct Particle {
  cnf::PosType x{};
  cnf::PosType y{};
  float r{};
  cnf::Color color{cnf::kParticleColor};
  cnf::PosType momentumX{0};
  cnf::PosType momentumY{0};
  bool collided{false};
};
