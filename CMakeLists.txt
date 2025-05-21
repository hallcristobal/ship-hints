cmake_minimum_required(VERSION 3.5)
project(test_server)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES 
  "${CMAKE_SOURCE_DIR}/src/*.c"
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(test_server ${SOURCE_FILES})
target_include_directories(test_server PUBLIC "${CMAKE_SOURCE_DIR}/src/soh/include")
