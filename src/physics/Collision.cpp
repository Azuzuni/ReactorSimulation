#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "physics/Collision.hpp"
#include "utils/Configuration.hpp"
#include <cstdlib>
#include <type_traits>
#include <variant>

constexpr bool Collision::FuelParticle(const Fuel &fuel,
                                       const Particle &particle) {
  cnf::PosType dX{std::abs(fuel.x - particle.x)};
  cnf::PosType dY{std::abs(fuel.y - particle.y)};
  float radiusSum{fuel.r + particle.r};
  return (dX * dX + dY * dY) <= (radiusSum * radiusSum);
}

// ---------------------------------------------------

bool Collision::OnEnter(const Collider &a, const Collider &b) {
  return std::visit(
      [](auto &&c1, auto &&c2) -> bool {
        using Type1 = std::decay_t<decltype(c1)>;
        using Type2 = std::decay_t<decltype(c2)>;
        if constexpr (std::is_same_v<Type1, Fuel> &&
                      std::is_same_v<Type2, Particle>)
          return FuelParticle(c1, c2);

        if constexpr (std::is_same_v<Type2, Fuel> &&
                      std::is_same_v<Type1, Particle>)
          return FuelParticle(c2, c1);

        return false;
      },
      a, b);
}
