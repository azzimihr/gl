#pragma once

#include "enum.h"

GLFWwindow* window;


void initGL(int maj, int min){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  println("\nOpenGL {}.{}", maj, min);
}

void winGL(int w, int h, S title){
  constexpr f32 aspect = 4.0 / 3.0;
  window = glfwCreateWindow(w, h, title, NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) { (void)win;
    f32 current = (f32)w / (f32)h;
    f32 val = current/aspect;
    if (val > 1)
      glViewport(w*(1-1/val)/2, 0, w/val, h);
    else
      glViewport(0, h*(1-val)/2, w, h*val);
    println("Window: {}x{}", w, h);
  });

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  println("Window: {}x{}", w, h);
}

void swapBuffs(){
  glfwSwapBuffers(window);
  glfwPollEvents();   
}

template<typename Fn> void key(int k, Fn&& action) {
  if (glfwGetKey(window, k) == GLFW_PRESS)
  std::forward<Fn>(action)();
}