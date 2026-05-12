/**
 * @file
 * @brief entry point
 */

#include "ReactorSimulator.hpp"
#include "ecs/EcsImpl.h"
int main() {
  ecs::Impl ecsImpl{};
  ReactorSimulator simulation{1720, 900, "Test"};
  simulation.Run();
  return 0;
}
