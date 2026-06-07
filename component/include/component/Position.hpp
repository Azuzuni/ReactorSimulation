#pragma once
#include "utils/Configuration.hpp"
namespace component {

struct Position {
  constexpr Position(util::PosType x, util::PosType y) : x{x}, y{y} {}
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
