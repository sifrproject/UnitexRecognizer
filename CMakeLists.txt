cmake_minimum_required(VERSION 3.6)
project(recognizer)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(./include)

link_directories(./lib)

FIND_PACKAGE(Boost 1.63.0 COMPONENTS random system thread filesystem chrono atomic date_time regex REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

find_package(OpenSSL 1.0.0 REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${OpenSSL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenSSL_LIBRARY_DIRS})


SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
#FIND_PACKAGE(Rabbitmqc REQUIRED)
#INCLUDE_DIRECTORIES(SYSTEM ${Rabbitmqc_INCLUDE_DIRS})
#
#FIND_PACKAGE(Simpleamqpclient REQUIRED)
#INCLUDE_DIRECTORIES(SYSTEM ${Simpleamqpclient_INCLUDE_DIRS})

find_package(cpprest REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${cpprest_INCLUDE_DIRS})
#LINK_DIRECTORIES(${cpprest_LIBRARY})

set( CMAKE_VERBOSE_MAKEFILE on )
set(SOURCE_FILES src/Unitex.cpp src/Annotation.cpp src/Annotation.h src/Environment.cpp src/Environment.h src/Configuration.h src/Configuration.cpp src/Configuration.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(recognizer ${SOURCE_FILES} src/Configuration.cpp src/Configuration.h)
target_link_libraries(recognizer
        cpprest
        ssl
        crypto
        Boost::boost
        Boost::random
        Boost::system
        Boost::thread
        Boost::filesystem
        Boost::chrono
        Boost::atomic
        Boost::date_time
        Boost::regex
        OpenSSL::SSL
        pthread
        unitex)
