#pragma once
#include "utils/Configuration.h"

namespace component {

struct Velocity {
  Velocity(util::PosType dX, util::PosType dY) : dX{dX}, dY{dY} {}
  Velocity() = default;
  Velocity(Velocity &&) = default;
  Velocity(const Velocity &) = default;
  Velocity &operator=(Velocity &&) = default;
  Velocity &operator=(const Velocity &) = default;
  ~Velocity() = default;

  util::PosType dX{};
  util::PosType dY{};
};

}; // namespace component
