#pragma once
#include <cstdint>

//! @brief namespace to group various colors together
//! @todo Components currently use their own color values.
//!       Unify them for consistency.
namespace color {
//! Color = uint32_t
//! represents colors as hex 0xRRGGBBAA
using Color = uint32_t;

constexpr Color BACKGROUND{0x444444FF};
constexpr Color PARTICLE{0x888888FF};
constexpr Color BUTTON{0x222222FF};
}; // namespace color
