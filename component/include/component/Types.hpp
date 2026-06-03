#pragma once

namespace component {

struct Particle {
  Particle() = default;
  Particle(Particle &&) = default;
  Particle(const Particle &) = default;
  Particle &operator=(Particle &&) = default;
  Particle &operator=(const Particle &) = default;
  ~Particle() = default;
};

struct Button {
  Button() = default;
  Button(Button &&) = default;
  Button(const Button &) = default;
  Button &operator=(Button &&) = default;
  Button &operator=(const Button &) = default;
  ~Button() = default;
};

}; // namespace component
