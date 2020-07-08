#pragma once

#include "LuaManager.h"
#include "Input/Input.h"
#include <cstring>

class LuaCommand {
 public:
  inline static void init() {
    lua->initLua();
  }

  inline static int run() {
    return lua->runLua();
  }

  inline static void push(char* file) {
    lua->pushLua(file);
  }
    
  inline static void printfiles() {
    lua->printLuaFiles();
  }

  inline static void close() {
    lua->closeLua();
  }

  inline static void tick(float deltaTime, float time) {
    lua->tickLua(deltaTime, time);
  }

  inline static void quit() {
    lua->quitLua();
  }

  inline static const char* convertToLuaInput(Key input) {
    switch(input) {
    case Key::SPACE:           return "SPACE"             ;              
    case Key::APOSTROPHE:      return "APOSTROPHE"    	  ;
    case Key::COMMA:           return "COMMA"         	  ;
    case Key::MINUS:           return "MINUS"         	  ;
    case Key::PERIOD:          return "PERIOD"        	  ;
    case Key::SLASH:           return "SLASH"         	  ;
    case Key::ZERO:            return "ZERO"          	  ;
    case Key::ONE:             return "ONE"           	  ;
    case Key::TWO:             return "TWO"           	  ;
    case Key::THREE:           return "THREE"         	  ;
    case Key::FOUR:            return "FOUR"          	  ;
    case Key::FIVE:            return "FIVE"          	  ;
    case Key::SIX:             return "SIX"           	  ;
    case Key::SEVEN:           return "SEVEN"         	  ;
    case Key::EIGHT:           return "EIGHT"         	  ;
    case Key::NINE:            return "NINE"          	  ;
    case Key::SEMICOLON:       return "SEMICOLON"     	  ;
    case Key::EQUAL:           return "EQUAL"         	  ;
    case Key::A:               return "A"             	  ;
    case Key::B:               return "B"             	  ;
    case Key::C:               return "C"             	  ;
    case Key::D:               return "D"             	  ;
    case Key::E:               return "E"             	  ;
    case Key::F:               return "F"             	  ;
    case Key::G:               return "G"             	  ;
    case Key::H:               return "H"             	  ;
    case Key::I:               return "I"             	  ;
    case Key::J:               return "J"             	  ;
    case Key::K:               return "K"             	  ;
    case Key::L:               return "L"             	  ;
    case Key::M:               return "M"             	  ;
    case Key::N:               return "N"             	  ;
    case Key::O:               return "O"             	  ;
    case Key::P:               return "P"             	  ;
    case Key::Q:               return "Q"             	  ;
    case Key::R:               return "R"             	  ;
    case Key::S:               return "S"             	  ;
    case Key::T:               return "T"             	  ;
    case Key::U:               return "U"             	  ;
    case Key::V:               return "V"             	  ;
    case Key::W:               return "W"             	  ;
    case Key::X:               return "X"             	  ;
    case Key::Y:               return "Y"             	  ;
    case Key::Z:               return "Z"             	  ;
    case Key::LEFT_BRACKET:    return "LEFT_BRACKET"  	  ;
    case Key::BACKSLASH:       return "BACKSLASH"     	  ;
    case Key::RIGHT_BRACKET:   return "RIGHT_BRACKET" 	  ;
    case Key::GRAVE:           return "GRAVE"         	  ;
    case Key::ESCAPE:          return "ESCAPE"        	  ;
    case Key::ENTER:           return "ENTER"         	  ;
    case Key::TAB:             return "TAB"           	  ;
    case Key::BACKSPACE:       return "BACKSPACE"     	  ;
    case Key::INSERT:          return "INSERT"        	  ;
    case Key::DELETE:          return "DELETE"        	  ;
    case Key::RIGHT:           return "RIGHT"         	  ;
    case Key::LEFT:            return "LEFT"          	  ;
    case Key::DOWN:            return "DOWN"          	  ;
    case Key::UP:              return "UP"            	  ;
    case Key::PAGE_UP:         return "PAGE_UP"       	  ;
    case Key::PAGE_DOWN:       return "PAGE_DOWN"     	  ;
    case Key::HOME:            return "HOME"          	  ;
    case Key::END:             return "END"           	  ;
    case Key::SHIFT:           return "SHIFT"             ;           
    }
    return "NONE";
  }

  inline static Key convertFromLuaInput(const char* input) {
    if(!strcmp(input, "SPACE"            ))  return Key::SPACE          ; 
    if(!strcmp(input, "APOSTROPHE"       ))  return Key::APOSTROPHE     ; 
    if(!strcmp(input, "COMMA"            ))  return Key::COMMA          ; 
    if(!strcmp(input, "MINUS"            ))  return Key::MINUS          ; 
    if(!strcmp(input, "PERIOD"           ))  return Key::PERIOD         ; 
    if(!strcmp(input, "SLASH"            ))  return Key::SLASH          ; 
    if(!strcmp(input, "ZERO"             ))  return Key::ZERO           ; 
    if(!strcmp(input, "ONE"              ))  return Key::ONE            ; 
    if(!strcmp(input, "TWO"              ))  return Key::TWO            ; 
    if(!strcmp(input, "THREE"            ))  return Key::THREE          ; 
    if(!strcmp(input, "FOUR"             ))  return Key::FOUR           ; 
    if(!strcmp(input, "FIVE"             ))  return Key::FIVE           ; 
    if(!strcmp(input, "SIX"              ))  return Key::SIX            ; 
    if(!strcmp(input, "SEVEN"            ))  return Key::SEVEN          ; 
    if(!strcmp(input, "EIGHT"            ))  return Key::EIGHT          ; 
    if(!strcmp(input, "NINE"             ))  return Key::NINE           ; 
    if(!strcmp(input, "SEMICOLON"        ))  return Key::SEMICOLON      ; 
    if(!strcmp(input, "EQUAL"            ))  return Key::EQUAL          ; 
    if(!strcmp(input, "A"                ))  return Key::A              ; 
    if(!strcmp(input, "B"                ))  return Key::B              ; 
    if(!strcmp(input, "C"                ))  return Key::C              ; 
    if(!strcmp(input, "D"                ))  return Key::D              ; 
    if(!strcmp(input, "E"                ))  return Key::E              ; 
    if(!strcmp(input, "F"                ))  return Key::F              ; 
    if(!strcmp(input, "G"                ))  return Key::G              ; 
    if(!strcmp(input, "H"                ))  return Key::H              ; 
    if(!strcmp(input, "I"                ))  return Key::I              ; 
    if(!strcmp(input, "J"                ))  return Key::J              ; 
    if(!strcmp(input, "K"                ))  return Key::K              ; 
    if(!strcmp(input, "L"                ))  return Key::L              ; 
    if(!strcmp(input, "M"                ))  return Key::M              ; 
    if(!strcmp(input, "N"                ))  return Key::N              ; 
    if(!strcmp(input, "O"                ))  return Key::O              ; 
    if(!strcmp(input, "P"                ))  return Key::P              ; 
    if(!strcmp(input, "Q"                ))  return Key::Q              ; 
    if(!strcmp(input, "R"                ))  return Key::R              ; 
    if(!strcmp(input, "S"                ))  return Key::S              ; 
    if(!strcmp(input, "T"                ))  return Key::T              ; 
    if(!strcmp(input, "U"                ))  return Key::U              ; 
    if(!strcmp(input, "V"                ))  return Key::V              ; 
    if(!strcmp(input, "W"                ))  return Key::W              ; 
    if(!strcmp(input, "X"                ))  return Key::X              ; 
    if(!strcmp(input, "Y"                ))  return Key::Y              ; 
    if(!strcmp(input, "Z"                ))  return Key::Z              ; 
    if(!strcmp(input, "LEFT_BRACKET"     ))  return Key::LEFT_BRACKET   ; 
    if(!strcmp(input, "BACKSLASH"        ))  return Key::BACKSLASH      ; 
    if(!strcmp(input, "RIGHT_BRACKET"    ))  return Key::RIGHT_BRACKET  ; 
    if(!strcmp(input, "GRAVE"            ))  return Key::GRAVE          ; 
    if(!strcmp(input, "ESCAPE"           ))  return Key::ESCAPE         ; 
    if(!strcmp(input, "ENTER"            ))  return Key::ENTER          ; 
    if(!strcmp(input, "TAB"              ))  return Key::TAB            ; 
    if(!strcmp(input, "BACKSPACE"        ))  return Key::BACKSPACE      ; 
    if(!strcmp(input, "INSERT"           ))  return Key::INSERT         ; 
    if(!strcmp(input, "DELETE"           ))  return Key::DELETE         ; 
    if(!strcmp(input, "RIGHT"            ))  return Key::RIGHT          ; 
    if(!strcmp(input, "LEFT"             ))  return Key::LEFT           ; 
    if(!strcmp(input, "DOWN"             ))  return Key::DOWN           ; 
    if(!strcmp(input, "UP"               ))  return Key::UP             ; 
    if(!strcmp(input, "PAGE_UP"          ))  return Key::PAGE_UP        ; 
    if(!strcmp(input, "PAGE_DOWN"        ))  return Key::PAGE_DOWN      ; 
    if(!strcmp(input, "HOME"             ))  return Key::HOME           ; 
    if(!strcmp(input, "END"              ))  return Key::END            ; 
    if(!strcmp(input, "SHIFT"            ))  return Key::SHIFT          ;   
    return Key::NONE;
  }


  inline static void input(Key input) {
    lua->inputLua(convertToLuaInput(input));
  }

private:
  static LuaManager* lua;
};
