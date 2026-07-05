#include "core/ReactorSimulator.hpp"
int main() {
  ReactorSimulator simulation{1920, 1080, "ReactorSimulator"};
  simulation.Run();
  return 0;
}
