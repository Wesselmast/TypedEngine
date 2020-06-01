#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string.h>
#include <tuple>

typedef void(*fptr_Command)(char**);

struct ConsoleCommand {
  fptr_Command command;
  const char* commandName;
  unsigned int argCountLow = 0;
  unsigned int argCountHigh = 0;
  const char* description = "No Description.";
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
      if(amt >= c.argCountLow && amt <= c.argCountHigh) {
	c.command(args);
	return;
      }
      else {
	bool plural = amt > 1;
	if(c.argCountLow == c.argCountHigh) {
	  printf("ERROR: Command '%s' wants %d arguments, %d %s given\n",
		 firstCommand,
		 c.argCountLow,
		 amt,
		 plural ? "were" : "was");
	  return;
	}
	printf("ERROR: Command '%s' wants between %d and %d arguments, %d %s given\n",
	       firstCommand,
	       c.argCountLow,
	       c.argCountHigh,
	       amt,
	       plural ? "were" : "was");
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
    printf("  %s : %s\n", c.commandName, c.description);
  }
}

static void listCommand(const char* command) {
  for(auto& c : commands) {
    if(!strcmp(c.commandName, command)) {
      printf("\nCommand %s:\n", c.commandName);
      printf("  args(%d, %d)\n", c.argCountLow, c.argCountHigh);
      printf("  %s\n",c.description);
      return;
    }
  }
  printf("ERROR: Command %s is unknown\n", command);
}

#define NUM_ARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value
#define CONSOLE_COMMANDS(...) (enterCommands(NUM_ARGS(__VA_ARGS__), __VA_ARGS__))
