#include "TEcore.h"

#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include <stdio.h>

#include <string>

// TRANSFORM

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

// ENTITY

void TEEntity::setTransform(TETransform* transform) {
  ref->transform = *toTransform(transform);
}

TETransform* TEEntity::getTransform() {
  return toTETransform(&ref->transform);
}

// SPRITES

TESprite* TESprite::init() {
  ref = new Sprite();
  ref->tag = Tag::PLAY_MODE;
  return (TESprite*)ref;
}

TESprite* TESprite::init(TETransform* transform) {
  ref = new Sprite(*toTransform(transform));
  ref->tag = Tag::PLAY_MODE;
  return (TESprite*)ref;
}

TESprite* TESprite::init(const char* texture) {
  ref = new Sprite(texture);
  ref->tag = Tag::PLAY_MODE;
  return (TESprite*)ref;
}

TESprite* TESprite::init(TETransform* transform, const char* texture) {
  ref = new Sprite(*toTransform(transform), texture);
  ref->tag = Tag::PLAY_MODE;
  return (TESprite*)ref;
}

//  TEXT

TEText* TEText::init() {
  ref = new Text();
  ref->tag = Tag::PLAY_MODE;
  return (TEText*)ref;
}

TEText* TEText::init(TETransform* transform) {
  ref = new Text(*toTransform(transform));
  ref->tag = Tag::PLAY_MODE;
  return (TEText*)ref;
}

TEText* TEText::init(const char* text) {
  std::string s_text = text;
  ref = new Text(s_text);
  ref->tag = Tag::PLAY_MODE;
  return (TEText*)ref;
}

TEText* TEText::init(TETransform* transform, const char* text) {
  std::string s_text = text;
  ref = new Text(*toTransform(transform), s_text);
  ref->tag = Tag::PLAY_MODE;
  return (TEText*)ref;
}


// QUADS

TEQuad* TEQuad::init() {
  ref = new Quad();
  ref->tag = Tag::PLAY_MODE;
  return (TEQuad*)ref;
}

TEQuad* TEQuad::init(TETransform* transform) {
  ref = new Quad(*toTransform(transform));  
  ref->tag = Tag::PLAY_MODE;
  return (TEQuad*)ref;
}

TEQuad* TEQuad::init(const color& color) {
  ref = new Quad({color.r, color.g, color.b, color.a});
  ref->tag = Tag::PLAY_MODE;
  return (TEQuad*)ref;
}

TEQuad* TEQuad::init(TETransform* transform, const color& color) {
  ref = new Quad(*toTransform(transform), {color.r, color.g, color.b, color.a});
  ref->tag = Tag::PLAY_MODE;
  return (TEQuad*)ref;
}
