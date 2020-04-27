#include "Wrappers.h"

#include "Rendering/Quad.h"
#include <stdio.h>

class Popz {
public:
  Popz() {
    new Quad();
  }
};

TESprite::TESprite() {
  //new Popz();
  init();
  new Quad();
}

void TESprite::init() {
}

// TESprite::TESprite(Transform transform) {
//  new Sprite(transform);
// }

// TESprite::TESprite(const char* texture) {
//  new Sprite(texture);
// }

// TESprite::TESprite(Transform transform, const char* texture) {
//  new Sprite(transform, texture);
// }

// void TESprite::setTransform(Transform transform) {
//   ref->transform = transform;
// }

// Transform TESprite::getTransform() {
//   return ref->transform;
// }


// TEText::TEText() {
//   new Text();
// }

// TEQuad::TEQuad() {
//   new Quad();
// }
