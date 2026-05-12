#pragma once
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"

/**
 * @class Fuel
 * @brief struct containing data for fuel
 * needed for simulation
 *
 * @param x -> x PosType coordinate
 * @param y -> y PosType coordinate
 */
struct Fuel {
  util::PosType x{};
  util::PosType y{};
  float r{};
  util::Color color{0x0000BBFF};
  bool triggered{false};
};
