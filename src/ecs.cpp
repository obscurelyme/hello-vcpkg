#include "ecs/ecs.h"

#include "ecs/entity.h"


Zero::EntityManager* Zero::EntityManager::instance = nullptr;

void Zero::ProcessInits() {
  entitiesCommittedToInit.swap(entitiesToInit);

  for (auto it = entitiesCommittedToInit.begin(); it != entitiesCommittedToInit.end(); ++it) {
    it->second->init();
  }

  entitiesCommittedToInit.clear();
}

void Zero::ProcessReadies() {
  entitiesCommittedToReady.swap(entitiesToMakeReady);

  for (auto it = entitiesCommittedToReady.begin(); it != entitiesCommittedToReady.end(); ++it) {
    it->second->ready();
  }

  entitiesCommittedToReady.clear();
}