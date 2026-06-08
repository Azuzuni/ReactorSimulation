#pragma once
#include "core/Color.hpp"
#include <cstdint>
namespace component {
namespace shape {

struct Circle {
  constexpr Circle(float r, uint32_t color, bool trigger = false)
      : radius{r}, color{color}, trigger{trigger} {}
  Circle() = default;
  Circle(Circle &&) = default;
  Circle(const Circle &) = default;
  Circle &operator=(Circle &&) = default;
  Circle &operator=(const Circle &) = default;
  ~Circle() = default;

  float radius{};
  bool trigger{};
  color::Color color{color::PARTICLE};
};

}; // namespace shape
}; // namespace component
