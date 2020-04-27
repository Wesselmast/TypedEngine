#pragma once

class Sprite;
class Transform;

struct vec2 {
  float x = 0.0f;
  float y = 0.0f;
};

struct TETransform {
  TETransform();
  TETransform(vec2 position, float rotation, vec2 scale);

  ~TETransform();

  vec2 position;
  float rotation;
  vec2 scale;
private:
  Transform* ref;
};

class TESprite {
public:
  void init();
  void init(TETransform* transform);
  void init(const char* texture);
  void init(TETransform* transform, const char* texture);

  void setTransform(TETransform* transform);
  TETransform* getTransform();

  // CleanUp: These sprites should self-destruct once left play-state
  
private:
  Sprite* ref;
};


// class TEText {
// public:
//   TEText();
// };

// class TEQuad {
// public:
//   TEQuad();
// };
