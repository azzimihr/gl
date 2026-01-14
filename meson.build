project('app', 'cpp', 'c',
  version : '1.0',
  default_options : ['cpp_std=c++26', 'buildtype=release'])

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
  link_args : [],
  cpp_args : [
    '-std=c++2b',
    '-march=native',
    '-O3',
    '-ffast-math',
    '-flto=auto',
    '-fno-signed-zeros',
    '-fno-trapping-math',
    '-Wall', '-Wextra', '-Wpedantic', '-Werror'
  ],
  c_args : [
    '-std=c23',
    '-march=native',
    '-Oz',
    '-flto=auto',
    '-fno-signed-zeros',
    '-fno-trapping-math',
    '-Wall', '-Wextra', '-Werror'
  ])
