#include "components/EntityManager.hpp"
#include <assert.h>

// ===================================================
// 1. Constructor / Destructor
// ===================================================

// ===================================================
// 2. Implementations
// ===================================================
namespace component {

Entity EntityManager::CreateEntity() {
  assert(mActiveEntitiesCount < kEntitiesCap &&
         "Too many entities in existence");

  Entity id{mAvailableEntities.front()};
  mAvailableEntities.pop();
  ++mActiveEntitiesCount;

  return id;
}

void EntityManager::RemoveEntity(Entity entity) {
  assert(entity < kEntitiesCap && "Entity out of range.");
  mSignatures[entity].reset();

  mAvailableEntities.push(entity);
  --mActiveEntitiesCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < kEntitiesCap && "Entity out of range.");
  mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < kEntitiesCap && "Entity out of range.");
  return mSignatures[entity];
}

}; // namespace component
