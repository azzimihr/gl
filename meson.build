project('app', 'cpp', 'c',
  version : '1.0',
  default_options : ['cpp_std=c++23', 'buildtype=release'])

executable('app',
  files('main.cpp', 'glad/glad.c'),
  cpp_pch : 'pch/returns.h',
  dependencies : [
    dependency('glfw3'),
    dependency('gl'),
    dependency('x11'),
    dependency('xrandr'),
    dependency('xi'),
    dependency('glm'),
  ],
  link_args : ['-ldl', '-lstdc++exp'],
  cpp_args : ['-march=native', '-Wall', '-Wextra', '-Wpedantic', '-Werror'],
  c_args : ['-march=native', '-Wall', '-Wextra', '-Werror'])
