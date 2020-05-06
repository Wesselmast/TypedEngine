#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string.h>

typedef void(*fptr_Command)(char**);

struct ConsoleCommand {
  fptr_Command command;
  const char* commandName;
  unsigned int argCount = 0;
};

static std::vector<ConsoleCommand> commands;
const unsigned int MAX_ARGUMENTS = 10;

static void parseCommand(const char* command) {
  char cmd[256] = {};
  strcpy(cmd, command);
  char* args[MAX_ARGUMENTS + 1] = {};

  unsigned int amt = 0;
  args[amt] = strtok(cmd, " ");
  if(!args[amt]) return;
  
  while(args[amt]) {
    if(amt >= MAX_ARGUMENTS) {
      	printf("ERROR: Cannot insert more than %d arguments!\n", MAX_ARGUMENTS);
	return;
    }
    args[++amt] = strtok(NULL, " ");
    args[amt-1] = args[amt];
  }
  amt--;
  
  char* firstCommand = strtok(cmd, " "); 
  
  for(auto& c : commands) {
    if(!strcmp(c.commandName, firstCommand)) {
      if(c.argCount == amt) {
	c.command(args);
	return;
      }
      else {
	printf("ERROR: Command '%s' wants %d arguments, %d were given\n", firstCommand, c.argCount, amt);
	return;
      }
    }
  }
  printf("ERROR: Command '%s' is unknown\n", firstCommand);
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
    printf("  %s\n", c.commandName);
  }
}

#define NUM_ARGS(...) (sizeof((ConsoleCommand[]){__VA_ARGS__})/sizeof(ConsoleCommand))
#define CONSOLE_COMMANDS(...) (enterCommands(NUM_ARGS(__VA_ARGS__), __VA_ARGS__))
