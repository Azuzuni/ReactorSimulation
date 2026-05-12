#pragma once

#include <cstdint>
namespace util {

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  constexpr ~Color() = default;
  constexpr Color() = default;
  constexpr Color(Color &&) = default;
  constexpr Color(const Color &) = default;
  constexpr Color &operator=(Color &&) = default;
  constexpr Color &operator=(const Color &) = default;

  constexpr Color(const uint32_t rgba)
      : r{static_cast<uint8_t>((rgba >> 24) & 0xFF)},
        g{static_cast<uint8_t>((rgba >> 16) & 0xFF)},
        b{static_cast<uint8_t>((rgba >> 8) & 0xFF)},
        a{static_cast<uint8_t>((rgba) & 0xFF)} {}

  constexpr Color &operator=(const uint32_t &rgba) {
    r = {static_cast<uint8_t>((rgba >> 24) & 0xFF)};
    g = {static_cast<uint8_t>((rgba >> 16) & 0xFF)};
    b = {static_cast<uint8_t>((rgba >> 8) & 0xFF)};
    a = {static_cast<uint8_t>((rgba) & 0xFF)};
    return *this;
  }

  inline bool operator==(const uint32_t color) {
    return (static_cast<uint32_t>((a << 24) | (g << 16) | (b << 8) | (a)) == color);
  }
};

constexpr Color kBackgroundColor{0x444444FF};
constexpr Color kParticleColor{0xFF000044};

}; // namespace util 
