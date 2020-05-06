#pragma once

void init_lua();
void run_lua();
void push_lua(const char* file);
void close_lua();
void tick_lua(float deltaTime, float time);
void quit_lua();


