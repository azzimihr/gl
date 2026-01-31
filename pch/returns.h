#pragma once

#include "window.h"

f32 randF(){
  static thread_local mt19937 gen(random_device{}());;
  static uniform_real_distribution<f32> dist{0.0, 1.0};
  return dist(gen);
}

void error(void(*getiv)(u32, u32, int*), void(*infologger)(u32, int, int*, char*), int status_type, u32 arg){
  int success;
  getiv(arg, status_type, &success);
  if (!success) {
    char infoLog[512];
    infologger(arg, 512, 0, infoLog);
    println("{}", infoLog);
  }
}

u32 Shader(u32 type, S *source, u32 program){
  u32 shader = glCreateShader(type);

  glShaderSource(shader, 1, source, NULL);
  glCompileShader(shader);
  glAttachShader(program, shader);

  error(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, shader);

  return shader;
}

u32 Program(S &vs, S &fs){
  u32 program = glCreateProgram();
  u32 vert = Shader(GL_VERTEX_SHADER, &vs, program);
  u32 frag = Shader(GL_FRAGMENT_SHADER, &fs, program);

  glLinkProgram(program);
  glDeleteShader(frag);
  glDeleteShader(vert);
  
  error(glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS, program);

  return program;
}