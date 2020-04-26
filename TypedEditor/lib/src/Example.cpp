#include "example.h"
#include <stdio.h>

#include "rendering/text.h"
#include "rendering/quad.h"

static int myamt = 0;

void Test::say_hello(int amt) {
  for (int i = myamt; i < myamt + amt; i++) {
    // @CleanUp: Transforms are still weird right now. Positions have to follow scale
    new Quad({{ (512.0f + 250.0f) * i, 0.0f }, 0.0f, { 1.0f, 1.0f}}, {1 - i/50.0f, 1 - i/50.0f, 1 - i/50.0f, 1.0f});
    new Text({{ ((512.0f + 250.0f)/4 * i), 128.0f / 3.0f }, 0.0f, { 3.0f, 3.0f}}, std::to_string(i + 1));   //@CleanUp: Add setting color of the text
  }
  myamt += amt;
}
