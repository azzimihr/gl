#include "funcs.hpp"
#include "data.hpp"

ui VAO, VBO, EBO;

void processInput(){
  key(GLFW_KEY_ESCAPE, []{
    glfwSetWindowShouldClose(window, true);
  });
}

int main(){
  int fps = 0;
  initGL(3, 3);
  winGL(800, 600, "GL");
  
  genBuffers(VAO, VBO, VBO);
  
  bindData(VBO, VERTEX, vertices, sizeof(vertices));
  bindData(EBO, INDEX, indices, sizeof(indices));

  ui p1 = Program(&vs1, &fs1);
  ui p2 = Program(&vs1, &fs2);
  
  instruct(3, (void*)0);
  glEnableVertexAttribArray(0);
  
  while(!glfwWindowShouldClose(window)){
    processInput();

    fps=(++fps)%120;
    if (fps==0) println("{}",fps);

    color(0.4f, f(fps)/150, 0.4f, 1.0f);

    uniform4(p2, "color", randF()/2+0.499, randF()/4.0+0.749, randF()/2, std::abs(f(60-fps))/60.0);
    
    if (randF()<fps/60.0)
      tri(0, 3, p1);
    tri(3, 3, p2);
    

    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  glfwTerminate();
}