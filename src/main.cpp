/**
 * @file
 * @brief entry point
 */

#include "ChernobylSimulator.hpp"

int main() {
  ChernobylSimulator simulation{1720, 900, "Test"};
  simulation.Run();
  return 0;
}
