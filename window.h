#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <print>

#include "enum.h"

GLFWwindow* window;

void initGL(int maj, int min){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  println("OpenGL {}.{}", maj, min);
}

void winGL(int w, int h, const char* title){
  window = glfwCreateWindow(w, h, title, NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
    (void)win;
    glViewport(0, 0, w, h);
  });

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  println("Window: {}x{}", w, h);
}

template<typename Fn> void key(int k, Fn&& action) {
  if (glfwGetKey(window, k) == GLFW_PRESS)
  std::forward<Fn>(action)();
}