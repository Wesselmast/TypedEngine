#include "PCH.h"

#include "Entity.h"

#include <stdio.h>

Entity::Entity() {
  entityCount++;
}

Entity::~Entity() {
  entityCount--;
}

void Entity::setName(const std::string& name) {
  this->name = name + std::to_string(entityCount);
}

int Entity::entityCount = 0;
