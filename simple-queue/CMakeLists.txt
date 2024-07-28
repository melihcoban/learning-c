cmake_minimum_required(VERSION 3.10)

project(
  LinkedListC
  VERSION 0.1
  LANGUAGES C)

set(SOURCES src/main.c)

add_executable(queue.exe ${SOURCES})