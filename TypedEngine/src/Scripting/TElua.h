#pragma once

void init_lua();
void run_lua();
void push_lua(char* file);
void print_lua_files();
void close_lua();
void tick_lua(float deltaTime, float time);
void quit_lua();


