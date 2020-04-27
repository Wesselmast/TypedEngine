#include "TEcore.h"

#include "Rendering/Sprite.h"
#include "Core/Transform.h"
#include <stdio.h>

Transform* toTransform(TETransform* t) {
  return new Transform({{t->position.x, t->position.y}, t->rotation, {t->scale.x, t->scale.y}});
}

TETransform* toTETransform(Transform* t) {
  return new TETransform({{t->position.x, t->position.y}, t->rotation, {t->scale.x, t->scale.y}});
}

TETransform::TETransform() {
  ref = new Transform();
  this->position = { ref->position.x, ref->position.y };
  this->rotation = ref->rotation;
  this->scale = { ref->scale.x, ref->scale.y };
}

TETransform::TETransform(vec2 position, float rotation, vec2 scale) {
  ref = new Transform({{position.x, position.y}, rotation, {scale.x, scale.y}});
  this->position = { ref->position.x, ref->position.y };
  this->rotation = ref->rotation;
  this->scale = { ref->scale.x, ref->scale.y };
}

TETransform::~TETransform() {
  delete ref;
}

void TESprite::init() {
  ref = new Sprite();
}

void TESprite::init(TETransform* transform) {
  ref = new Sprite(*toTransform(transform));
}

void TESprite::init(const char* texture) {
  ref = new Sprite(texture);
}

void TESprite::init(TETransform* transform, const char* texture) {
  ref = new Sprite(*toTransform(transform), texture);
}

void TESprite::setTransform(TETransform* transform) {
  ref->transform = *toTransform(transform);
}

TETransform* TESprite::getTransform() {
  return toTETransform(&ref->transform);
}
