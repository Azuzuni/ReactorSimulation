#pragma once

#include <chrono>
#include <random>
namespace component {

struct Decay {
  std::chrono::milliseconds lifeTime{1000};
  Decay(const std::chrono::milliseconds &lifeTime) : lifeTime(lifeTime) {}
  Decay() {
    static std::mt19937::result_type seed =
        static_cast<std::mt19937::result_type>(
            std::chrono::high_resolution_clock::now()
                .time_since_epoch()
                .count());
    static std::mt19937 gen(seed);
    static std::uniform_real_distribution<float> range(1, 5);
    lifeTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::duration<float>(range(gen)));
  }
  ~Decay() = default;
};

}; // namespace component
