#pragma once

#include "utils/Configuration.hpp"
#include <utility>
namespace ecs {

// ===================================================
// 1. Declarations
// ===================================================

//! @brief CRTP Interface for ECS system
//!
//! @tparam Impl selected child class containing implementations
template <typename Impl> class EcsIF {
protected:
  EcsIF() = default;
  ~EcsIF() = default;

  //! @brief derived() is used to call children methods through parent (CRTP)
  constexpr inline Impl &derived() { return static_cast<Impl &>(*this); }
  constexpr const inline Impl &derived() const {
    return static_cast<const Impl &>(*this);
  }

public:
  //-----------------------------------
  // Constructors
  //-----------------------------------
  EcsIF(EcsIF &&) = default;
  EcsIF(const EcsIF &) = default;
  EcsIF &operator=(EcsIF &&) = default;
  EcsIF &operator=(const EcsIF &) = default;

  //-----------------------------------
  // Methods
  //-----------------------------------

  //! @brief creates new Entity entry in registry
  [[nodiscard]]
  util::Entity Create() noexcept;

  //! @brief remove all of ECS entities
  void DestroyAll() noexcept;

  //! @brief remove entity of matching ID
  //!
  //! @param entity ID of entity to destroy
  void Destroy(util::Entity entity) noexcept;

  //! @brief adds a component to selected entity
  //!
  //! @param entity selected entity that is supposed to acquire new component
  //! @tparam Component a component from component module such as
  //!        component::Position
  //! @tparam Args arguments needed for Component construction
  template <typename Component, typename... Args>
  void Add(util::Entity entity, Args &&...args) noexcept;

  //! @brief Returns ptr to selected components of searched entity (const)
  //!
  //! @param entity selected entity that has components we look for
  //! @tparam Components components from component module that we look for
  template <typename Components>
  [[nodiscard]] const Components *Get(util::Entity entity) const noexcept;

  //! @brief Returns selected components of searched entity
  //!
  //! @TODO fix this Get to match const version
  //!
  //! @param entity selected entity that has components we look for
  //! @tparam Components components from component module that we look for
  template <typename... Components>
  [[nodiscard]] auto Get(util::Entity entity) noexcept;

  //! @brief Access Iterates over all entities matching the given components.
  //!        (const)
  //!
  //! @tparam Components components from component module that we wish to access
  //!        and iterate over
  //! @tparam Lambda function to execute during iteration
  template <typename... Components, typename Lambda>
  void Each(Lambda &&function) const noexcept;

  //! @brief Iterates over all entities matching the given components.
  //!
  //! @tparam Components components from component module that we wish to access
  //!        and iterate over
  //! @tparam Lambda function to execute during iteration
  template <typename... Components, typename Lambda>
  void Each(Lambda &&function) noexcept;
};

// ===================================================
// 2. Implementations
// ===================================================

// Create
template <typename Impl> util::Entity EcsIF<Impl>::Create() noexcept {
  return derived().CreateImpl();
}

// DestroyAll
template <typename Impl> void EcsIF<Impl>::DestroyAll() noexcept {
  derived().DestroyAllImpl();
}

// Destroy
template <typename Impl>
void EcsIF<Impl>::Destroy(util::Entity entity) noexcept {
  derived().DestroyImpl(entity);
}

// Add
template <typename Impl>
template <typename Component, typename... Args>
void EcsIF<Impl>::Add(util::Entity entity, Args &&...args) noexcept {
  derived().template AddImpl<Component>(entity, std::forward<Args>(args)...);
}

// Get (const)
template <typename Impl>
template <typename Components>
const Components *EcsIF<Impl>::Get(util::Entity entity) const noexcept {
  return derived().template GetImpl<Components>(
      std::forward<util::Entity>(entity));
}

// Get
template <typename Impl>
template <typename... Components>
auto EcsIF<Impl>::Get(util::Entity entity) noexcept {
  return derived().template GetImpl<Components...>(
      std::forward<util::Entity>(entity));
}

// Each (const)
template <typename Impl>
template <typename... Components, typename Lambda>
void EcsIF<Impl>::Each(Lambda &&function) const noexcept {
  derived().template EachImpl<Components...>(std::forward<Lambda>(function));
}

// Each
template <typename Impl>
template <typename... Components, typename Lambda>
void EcsIF<Impl>::Each(Lambda &&function) noexcept {
  derived().template EachImpl<Components...>(std::forward<Lambda>(function));
}
}; // namespace ecs
