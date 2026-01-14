#pragma once

#include "window.h"

f32 randF(){
  static thread_local mt19937 gen(random_device{}());;
  static uniform_real_distribution<f32> dist{0.0, 1.0};
  return dist(gen);
}

u32 Shader(u32 type, S *source, u32 program){
  u32 shader = glCreateShader(type);
  glShaderSource(shader, 1, source, NULL);
  glCompileShader(shader);
  glAttachShader(program, shader);
  return shader;
}

u32 Program(S &vs, S &fs){
  u32 program = glCreateProgram();
  u32 vert = Shader(GL_VERTEX_SHADER, &vs, program);
  u32 frag = Shader(GL_FRAGMENT_SHADER, &fs, program);

  glLinkProgram(program);
  glDeleteShader(frag);
  glDeleteShader(vert);
  
  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    println("shader error!: {}", infoLog);
  }
  
  return program;
}