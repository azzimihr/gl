#include "window.h"
#include "shorthands.h"
#include "data.h"
#include "returns.h"
#include <print>

#include "enum.h"

void processInput(){
  key(GLFW_KEY_ESCAPE, []{
    glfwSetWindowShouldClose(window, true);
  });
  key(GLFW_KEY_F11, []{
    
  });
}

int main(){
  initGL(3, 3);
  winGL(800, 600, "GL");
  gen(VAO, VBO);
  
  // bindData(EBO, INDEX, indices, sizeof(indices));
  
  ui p1 = Program(vs1, fs1);
  ui p2 = Program(vs1, fs2);
  ui p3 = Program(vs2, fs3);
  
  setup<3> (0, 0, vertices);
  setup<3, 3> (1, 1, vertices2);
  
  int fps = 0;
  while(!glfwWindowShouldClose(window)){
    processInput();

    fps=(++fps)%120;

    color(0.4f, f(fps)/150, 0.4f);

    uniform4(p2, "color", randF()/2+0.499, randF()/4.0+0.749, randF()/2, std::abs(f(60-fps))/60.0);
    

    glBindVertexArray(VAO[1]);
    tri(0, 3, p3);
    glBindVertexArray(VAO[0]);
    if (randF()<fps/60.0)
      tri(0, 3, p1);
    tri(3, 3, p2);
    
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  glfwTerminate();
}