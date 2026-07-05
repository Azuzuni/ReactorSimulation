#pragma once

#include <chrono>
namespace component {

struct Lifetime {
  std::chrono::milliseconds lifeTime{1000};
  Lifetime(const std::chrono::milliseconds &lifeTime) : lifeTime(lifeTime) {}
};

}; // namespace component
