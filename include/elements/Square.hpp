#pragma once
#include "utils/Configuration.hpp"

/**
 * @class Fuel
 * @brief struct containing data for fuel
 * needed for simulation
 *
 * @param x -> x PosType coordinate
 * @param y -> y PosType coordinate
 */
struct Fuel {
  cnf::PosType x{};
  cnf::PosType y{};
  float r{};
  cnf::Color color{0x0000BBFF};
};
