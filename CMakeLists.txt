cmake_minimum_required(VERSION 3.6)
project(recognizer)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

link_directories(/usr/local/lib)

set(SOURCE_FILES src/Unitex.cpp src/Annotation.cpp src/Annotation.h src/Environment.cpp src/Environment.h src/Configuration.h src/Configuration.cpp src/Configuration.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3")

add_executable(recognizer ${SOURCE_FILES} src/Configuration.cpp src/Configuration.h)
target_link_libraries(recognizer unitex)