#pragma once
#include "utils/Configuration.h"
namespace component {

struct Position {
  Position(util::PosType x, util::PosType y) : x{x}, y{y} {}
  Position() = default;
  Position(Position &&) = default;
  Position(const Position &) = default;
  Position &operator=(Position &&) = default;
  Position &operator=(const Position &) = default;
  ~Position() = default;

  util::PosType x{};
  util::PosType y{};
};

}; // namespace component
