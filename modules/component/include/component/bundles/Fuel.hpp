#pragma once

#include "component/Decay.hpp"
#include "component/Position.hpp"
#include "component/shape/Circle.hpp"
#include "ecs/EcsImpl.hpp"
#include <cstdint>

// =============================
// MACROS
// =============================

// macro for use with ecs::Impl::Each<BUNDLE>()
#ifndef COMPONENT_FUEL_BUNDLE
#define COMPONENT_FUEL_BUNDLE                                                  \
  component::Position, component::Decay, component::shape::Circle,             \
      component::Fuel
#else
#error "Redefinition of COMPONENT_FUEL_BUNDLE"
#endif

// macro for use with ecs::Impl::Each<>(BUNDLE_VARS)
#ifndef COMPONENT_FUEL_BUNDLE_VARS
#define COMPONENT_FUEL_BUNDLE_VARS(pos, decay, circle, fuel)                   \
  component::Position &position, component::Decay &decay,                      \
      component::shape::Circle &circle, component::Fuel &fuel
#else
#error "Redefinition of COMPONENT_FUEL_BUNDLE_VARS"
#endif

// =============================
// COMPONENT
// =============================

namespace component {

//! @TODO fix consistency of default values across components
constexpr float FUEL_RADIUS{10.f};
constexpr uint32_t FUEL_COLOR{0x6666FFFF};
constexpr uint32_t FUEL_COLOR_DECAY{0x6666FF55};

//! @brief component bundle and tag containing methods for Fuel logic
struct Fuel {
  //-----------------------------------
  // Constructors
  //-----------------------------------
  Fuel() = default;
  Fuel(Fuel &&) = default;
  Fuel(const Fuel &) = default;
  Fuel &operator=(Fuel &&) = default;
  Fuel &operator=(const Fuel &) = default;
  ~Fuel() = default;

  //-----------------------------------
  // Methods
  //-----------------------------------

  //! @brief method to handle fuel's decay
  //!
  //! this method handles logic that is responsible
  //! for creating new particles based on rng
  //! it returns component::Position(-1,-1)
  //!   when no particle should be spawned
  //! returns current fuel Position
  //!   when particles should spawn
  //!
  //! @return component::Position
  static component::Position DecayUpdate(ecs::Impl &buffer,
                                         component::Position &position,
                                         component::Decay &decay,
                                         float deltaTime);

  //! @brief checks collision with Particles
  //!
  //! @TODO create universal Collider component and optimize collision check
  //!
  //! returns true if collided with something
  //! false if there is no collision
  //! @return bool
  static bool CollisionCheck(ecs::Impl &buffer, component::Position &position,
                             component::shape::Circle &circle);

  //! @brief Creates new entity and adds Bundle components to it
  //!
  //! @param position starting position of the entity
  //! @param circle shape of the entity and collider
  static void Create(ecs::Impl &buffer, const component::Position &position,
                     const component::shape::Circle &circle = {FUEL_RADIUS,
                                                               FUEL_COLOR});

private:
  // since this class contains only static methods
  // this "cheapCheat" is a dirty solution to make this class copyable
  bool cheapCheat{};
};

}; // namespace component
