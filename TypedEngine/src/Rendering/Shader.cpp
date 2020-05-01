
#include "Shader.h"

#include <iostream>
#include <cstring>

void Shader::parseShader(const char * path, ShaderProgramSource * source) {
  FILE* shaderFile;
  fopen_s(&shaderFile, path, "r");
  
  if (shaderFile == NULL) {
    fprintf(stderr, "Error: Shader file was not found.");
    std::cin.get();
  }
  
  char* buffer = nullptr;
  fseek(shaderFile, 0, SEEK_END);
  long length = ftell(shaderFile);
  fseek(shaderFile, 0, SEEK_SET);
  
  buffer = (char*)malloc(length + 1);
  if (buffer) {
    fread(buffer, 1, length, shaderFile);
  }
  fclose(shaderFile);
  buffer[length] = '\0';
  
  if (buffer) {
    source->vertex = filterShaderCommands("#shader vertex", "#endshader vertex", buffer);
    source->fragment = filterShaderCommands("#shader fragment", "#endshader fragment", buffer);
  }
  
  fclose(shaderFile);
  delete buffer;
}

char * Shader::filterShaderCommands(const char * createCommand, const char * deleteCommand, char * buffer) {
  char* result = nullptr;
  
  const char* start = std::strstr(std::strstr(buffer, createCommand), "\n");
  if (start) {
    const char* end = std::strstr(start, deleteCommand);
    if (end) {
      size_t len = end - start;
      result = (char*)malloc(len + 1);
      if (result) {
	memcpy(result, start, len);
	result[len] = 0;
      }
    }
  }
  if (!result) {
    fprintf(stderr, "Error: Was not able to filter given shader commands");
  }
  return result;
}
