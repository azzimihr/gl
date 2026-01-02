const char *vs1 =
#include "vs/1"
;const char *fs1 =
#include "fs/1"
;const char *fs2 =
#include "fs/2"
;

f vertices[] = {
  // first triangle
  -0.9f, -0.5f, 0.0f, //color...
  -0.0f, -0.5f, 0.0f,
  -0.45f, 0.5f, 0.0f,

   0.0f, -0.5f, 0.0f,
   0.9f, -0.5f, 0.0f,
   0.45f, 0.5f, 0.0f
}; 
unsigned int indices[] = {
  0, 1, 3,
  1, 2, 3
};