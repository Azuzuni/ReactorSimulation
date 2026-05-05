/**
 * @file
 * @brief entry point
 */

#include "ReactorSimulator.hpp"

int main() {
  ReactorSimulator simulation{1720, 900, "Test"};
  simulation.Run();
  return 0;
}
