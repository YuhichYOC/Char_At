cmake_minimum_required(VERSION 3.13)
project(Char_At C)

set(CMAKE_C_STANDARD 99)

add_library(Char_At SHARED Char_At.h Char_At.c)