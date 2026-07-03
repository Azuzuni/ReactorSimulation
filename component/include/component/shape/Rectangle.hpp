#pragma once
#include "core/Color.hpp"
#include "utils/Configuration.hpp"
#include <cstdint>
namespace component {
namespace shape {

struct Rectangle {
  constexpr Rectangle(util::PosType width, util::PosType height, uint32_t color,
                      bool trigger = false)
      : width{width}, height{height}, color{color}, trigger(trigger) {}
  Rectangle() = default;
  Rectangle(Rectangle &&) = default;
  Rectangle(const Rectangle &) = default;
  Rectangle &operator=(Rectangle &&) = default;
  Rectangle &operator=(const Rectangle &) = default;
  ~Rectangle() = default;

  bool trigger{};
  util::PosType width{};
  util::PosType height{};
  color::Color color{color::BUTTON};
};

}; // namespace shape
}; // namespace component
