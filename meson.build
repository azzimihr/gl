project(
  'app',
  ['cpp', 'c'],
  version : '1.0',
  default_options : [
    'cpp_std=c++26',
    'c_std=c23',
    'buildtype=release',
    'optimization=3',
    'b_lto=true',
    'warning_level=3',
    'werror=true',  
  ]
)

common_args = [
  '-march=native',
  '-ffast-math',
]

executable(
  'app',
  files('main.cpp', 'glad/glad.c'),
  cpp_pch : 'pch/returns.h',
  dependencies : [
    dependency('glfw3'),
    dependency('gl'),
  ],
  cpp_args : common_args,
  c_args   : common_args,
)
