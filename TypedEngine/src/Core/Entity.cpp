#include "Entity.h"

#include <stdio.h>
#include "Scripting/LuaCommand.h"

Entity::Entity() {
  entityCount++;
}

Entity::~Entity() {
  entityCount--;
}

void Entity::addScript(const char* fileName) {
  LuaCommand::push((char*)fileName);
}

void Entity::setName(const std::string& name) {
  this->name = name + std::to_string(entityCount);
}

int Entity::entityCount = 0;
