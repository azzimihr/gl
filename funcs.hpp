#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <print>
#include <random>
#include <cstdlib>
#define INDEX GL_ELEMENT_ARRAY_BUFFER
#define VERTEX GL_ARRAY_BUFFER
using namespace std;

typedef unsigned int ui;
typedef float f;
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

f randF(){
  thread_local mt19937 gen(random_device{}());;
  static uniform_real_distribution<f> dist{0.0, 1.0};
  return dist(gen);
}

template<typename... Args>
void genBuffers(GLuint& VAO, Args&... args) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    (glGenBuffers(1, &args), ...);
}

template<typename Fn> void key(int k, Fn&& action) {
  if (glfwGetKey(window, k) == GLFW_PRESS)
  std::forward<Fn>(action)();
}
  
ui Shader(ui type, const char **source, ui program){
  ui shader = glCreateShader(type);
  glShaderSource(shader, 1, source, NULL);
  glCompileShader(shader);
  glAttachShader(program, shader);
  return shader;
}

ui Program(const char **vs, const char **fs){
  ui program = glCreateProgram();
  ui vert = Shader(GL_VERTEX_SHADER, vs, program);
  ui frag = Shader(GL_FRAGMENT_SHADER, fs, program);
  
  glLinkProgram(program);
  glDeleteShader(frag);
  glDeleteShader(vert);
  return program;
}

void tri(ui offset, ui count, ui prog){
  glUseProgram(prog);
  glDrawArrays(GL_TRIANGLES, offset,count);
}


void bindData(ui BO, ui type, const void* data, long len){
  glBindBuffer(type, BO);
  glBufferData(type, len, data, GL_STATIC_DRAW);
}

void instruct(ui vec, const void * offset){
  glVertexAttribPointer(0, vec, GL_FLOAT, GL_FALSE, vec * sizeof(f), offset);
}

void uniform4(ui prog, const char* str, f x, f y, f z, f w){
  glUseProgram(prog);
  glUniform4f(glGetUniformLocation(prog, str), x, y, z, w);
}

void color(f x, f y, f z, f w){
  glClearColor(x, y, z, w);
  glClear(GL_COLOR_BUFFER_BIT);
}