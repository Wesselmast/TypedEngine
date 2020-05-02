#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string>

typedef void(*fptr_Command)(const std::string&);

struct ConsoleCommand {
  fptr_Command command;
  std::string commandName;
};

static std::vector<ConsoleCommand> commands;

static void parseCommand(const std::string& command) {
  for(auto& c : commands) {
    if(c.commandName == command) {
      c.command(command);
      return;
    }
  }
  printf("ERROR: Command '%s' is unknown\n", command.c_str());
}

static void enterCommands(int numargs, ...) {
  va_list list;

  va_start(list, numargs);
  while(numargs--) {
    commands.push_back(va_arg(list, ConsoleCommand));
  }
  va_end(list);
}

static void listCommands() {
  printf("\nCommands: \n");
  for(auto& c : commands) {
    printf("  %s\n", c.commandName.c_str());
  }
}

#define NUM_ARGS(...) (sizeof((ConsoleCommand[]){__VA_ARGS__})/sizeof(ConsoleCommand))
#define CONSOLE_COMMANDS(...) (enterCommands(NUM_ARGS(__VA_ARGS__), __VA_ARGS__))
