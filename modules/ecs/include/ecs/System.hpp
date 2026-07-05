#pragma once

#include "ecs/EcsImpl.hpp"
#include "utils/InputData.hpp"
namespace ecs {

//! @brief static Class responsible for handling logic of entities
class System {
  //-----------------------------------
  // Constructors
  //-----------------------------------
  System() = delete;
  System(System &&) = delete;
  System(const System &) = delete;
  System &operator=(System &&) = delete;
  System &operator=(const System &) = delete;
  ~System() = delete;

  //-----------------------------------
  // Methods
  //-----------------------------------

  //! @brief destroys entities with expired lifetime
  //!
  //! @param buffer is ecs buffer containting all entities
  static void Flush(ecs::Impl &buffer);

  //! @brief handles particle logic changes
  //!
  //! ParticleUpdate makes calls to methods from component::Particle
  //! those methods contain informations how components should behave
  //! for this kind of entity
  //!
  //! @param buffer is ecs buffer containing all entities
  //! @param deltaTime fixed timestep value between frames
  static void ParticleUpdate(ecs::Impl &buffer, float deltaTime);

  //! @brief handles fuel logic changes
  //!
  //! FuelUpdate makes calls to methods from component::Fuel
  //! those methods contain informations how components should behave
  //! for this kind of entity
  //!
  //! @param buffer is ecs buffer containing all entities
  //! @param deltaTime fixed timestep value between frames
  static void FuelUpdate(ecs::Impl &buffer, float deltaTime);

  //! @brief handles ControlRod logic changes
  //!
  //! ControlRodUpdate makes calls to methods from component::ControlRod
  //! those methods contain informations how components should behave
  //! for this kind of entity
  //!
  //! @param buffer is ecs buffer containing all entities
  //! @param inputData is a struct containing input information,
  //!        needed for moving control rods (up and down)
  //! @param deltaTime fixed timestep value between frames
  static void ControlRodUpdate(ecs::Impl &buffer, InputData &inputData,
                               float deltaTime);

public:
  //! @brief wrapping function that makes call to each type of update method
  //!
  //! @param buffer is ecs buffer containing all entities
  //! @param inputData a struct containing input information.
  //! @param deltaTime fixed timestep value between frames
  static void Update(ecs::Impl &buffer, InputData &InputData, float deltaTime);
};

}; // namespace ecs
