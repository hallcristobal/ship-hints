cmake_minimum_required(VERSION 3.5)
project(test_server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES 
  "${CMAKE_SOURCE_DIR}/src/*.c"
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(test_server ${SOURCE_FILES})

# Include nlohmann_json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(external/json)
target_link_libraries(test_server PRIVATE nlohmann_json::nlohmann_json)

# Includes
target_include_directories(test_server PRIVATE
  "${CMAKE_SOURCE_DIR}/src/soh/include"
  "${CMAKE_SOURCE_DIR}/external/json/include"
)
