#pragma once

class Entity;
class Transform;

struct vec2 {
  vec2() {
  }
  
  vec2(float x, float y) : x(x), y(y) {
  }

  float x = 0.0f;
  float y = 0.0f;
};

struct color {
  color() {
  }
  
  color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
  }

  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 1.0f;
};

struct TETransform {
  TETransform();
  TETransform(vec2 position, float rotation, vec2 scale);

  ~TETransform();

  vec2 position;
  float rotation;
  vec2 scale;
private:
  Transform* ref = nullptr;
};

// @CleanUp: CONSTRUCTORS ARE BROKEN! WE NEED THEM

class TEEntity {
public:
  void setTransform(TETransform* transform);
  TETransform* getTransform();
protected:
  Entity* ref;
};

class TESprite : public TEEntity {
public:
  TESprite* init();
  TESprite* init(TETransform* transform);
  TESprite* init(const char* texture);
  TESprite* init(TETransform* transform, const char* texture);
};

class TEText : public TEEntity {
public:
  TEText* init();
  TEText* init(TETransform* transform);
  TEText* init(const char* text);
  TEText* init(TETransform* transform, const char* text);
  void setText(const char* text);
  void setColor(const color& color);
};

class TEQuad : public TEEntity {
public:
  TEQuad* init();
  TEQuad* init(TETransform* transform);
  TEQuad* init(const color& color);
  TEQuad* init(TETransform* transform, const color& color);
  void setColor(const color& color);
};
