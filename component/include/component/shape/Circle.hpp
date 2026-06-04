#pragma once
#include "core/Color.hpp"
#include <cstdint>
namespace component {
namespace shape {

struct Circle {
  Circle(float r, uint32_t color) : radius{r}, color{color} {}
  Circle() = default;
  Circle(Circle &&) = default;
  Circle(const Circle &) = default;
  Circle &operator=(Circle &&) = default;
  Circle &operator=(const Circle &) = default;
  ~Circle() = default;

  float radius{};
  color::Color color{color::PARTICLE};
};

}; // namespace shape
}; // namespace component
