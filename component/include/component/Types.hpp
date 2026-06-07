#pragma once

namespace component {

struct Button {
  Button() = default;
  Button(Button &&) = default;
  Button(const Button &) = default;
  Button &operator=(Button &&) = default;
  Button &operator=(const Button &) = default;
  ~Button() = default;
};

}; // namespace component
