cmake_minimum_required(VERSION 3.6)
project(recognizer)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(./include)

link_directories(./lib)


SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
#FIND_PACKAGE(Rabbitmqc REQUIRED)
#INCLUDE_DIRECTORIES(SYSTEM ${Rabbitmqc_INCLUDE_DIRS})
#
#FIND_PACKAGE(Simpleamqpclient REQUIRED)
#INCLUDE_DIRECTORIES(SYSTEM ${Simpleamqpclient_INCLUDE_DIRS})

FIND_PACKAGE(Boost 1.63.0 COMPONENTS random system thread filesystem chrono atomic date_time regex REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


set(CMAKE_VERBOSE_MAKEFILE on )
set(SOURCE_FILES src/unitex/Unitex.cpp
        src/unitex/Annotation.cpp src/unitex/Annotation.h src/unitex/Environment.cpp
        src/unitex/Environment.h src/unitex/Configuration.h src/unitex/Configuration.cpp
        src/unitex/Configuration.h src/server/server.h src/unitex_recognizer.cpp)

add_executable(recognizer ${SOURCE_FILES} src/unitex/Configuration.cpp src/unitex/Configuration.h)
target_link_libraries(recognizer
        Boost::boost
        pthread
        unitex)
