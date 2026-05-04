#pragma once


#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include <variant>


class Collision {
  using Collider = std::variant<Particle,Fuel>;
  Collision() = delete;
  Collision(Collision &&) = delete;
  Collision(const Collision &) = delete;
  Collision &operator=(Collision &&) = delete;
  Collision &operator=(const Collision &) = delete;
  ~Collision() = delete;

  static bool FuelParticle(const Fuel&, const Particle&);
public:
  static bool OnEnter(const Collider&, const Collider&);
};


