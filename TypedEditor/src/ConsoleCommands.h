#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

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

  // std::string s = "HELLO CAKE YES";
  // std::vector<std::string> args;
  // std::istringstream iss(s);
  // for(std::string a; iss >> s; ) {
  //   args.push_back(a);
  // }
  
  char cmd[256];
  strcpy(cmd, command);
  char* args[MAX_ARGUMENTS];

  unsigned int amt = 0;
  args[amt] = strtok(cmd, " ");
  if(!args[0]) return;
  while(args[amt]) {
    if(amt >= MAX_ARGUMENTS) {
      	printf("ERROR: Cannot insert more than %d arguments!\n", MAX_ARGUMENTS);
	return;
    }
    args[++amt] = strtok(NULL, " ");
  }
  amt--;
  
  char* firstCommand = args[0];
  
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
