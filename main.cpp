#include "data.h"

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
  // glfwSwapInterval(0); // vsync disable
  gen(VAO, VBO);

  // bindData(EBO, _EBO, indices, sizeof(indices));

  u32 p1 = Program(vs1, fs1);
  u32 p2 = Program(vs1, fs2);;
  u32 p3 = Program(vs2, fs3);
  
  setup<vap{2, HALF}               > (vertices, 0, 0);
  setup<vap{2, SHORT}, vap{4, BYTE}> (vertices2, 1, 1);
  
  int fps = 0;;
  auto lastTime = chrono::high_resolution_clock::now();
  int frameCount = 0;
  while(!glfwWindowShouldClose(window)){
    processInput();
    
    auto currentTime = chrono::high_resolution_clock::now();
    frameCount++;
    if(chrono::duration<double>(currentTime - lastTime).count() >= 1.0){
      println("FPS: {}", frameCount);
      frameCount = 0;
      lastTime = currentTime;
    }

    fps = (fps + 1) % 120;
    auto nes = sin(fps/M_PI/15);
    color(0.4f, nes*nes/1.5, 0.4f);

    uni(p2, "color",
      randF()/2+0.499,
      randF()/4.0+0.749,
      randF()/2,
      std::abs(f32(60-fps))/60.0/4.5+0.2
    );

    glBindVertexArray(VAO[1]);
    glUseProgram(p3);
    tri(0, 3);
    glBindVertexArray(VAO[0]);
    if (randF()<fps/60.0){
      glUseProgram(p1);
      tri(0, 3);
    }
    glUseProgram(p2);
    tri(3, 3);
    
    swapBuffs();
  }

  glfwTerminate();
}
