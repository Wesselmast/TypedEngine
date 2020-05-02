#include "ConsoleCommands.h"

#undef NUM_ARGS
#define NUM_ARGS(...) (sizeof((ConsoleCommand[]){__VA_ARGS__})/sizeof(ConsoleCommand))
#undef CONSOLE_COMMANDS
#define CONSOLE_COMMANDS(...) (enterCommands(NUM_ARGS(__VA_ARGS__), __VA_ARGS__))
