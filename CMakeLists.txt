cmake_minimum_required(VERSION 3.5)
project(test_server)
set(CMAKE_CXX_STANDARD 23)
set(SOURCE_FILES 
  src/hints.hpp
  src/text.hpp
  src/randomizerTypes.h
  src/static_data.h

  src/hints.cpp
  src/soh/hint_list_exclude_dungeon.cpp
  src/soh/hint_list_exclude_overworld.cpp
  src/soh/hint_list_item.cpp
  src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(test_server ${SOURCE_FILES})
