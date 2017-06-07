#Find the Rabbitmq C library

INCLUDE(LibFindMacros)

# Find the include directories
FIND_PATH(cpprest_INCLUDE_DIR
	NAMES cpprest/http_listener.h
    HINTS ${cpprest_DIR}/include
	)

FIND_LIBRARY(cpprest_LIBRARY
	NAMES cpprest
    HINTS ${cpprest_DIR}/lib
	)

SET(cpprest_PROCESS_INCLUDES cpprest_INCLUDE_DIR)
SET(cpprest_PROCESS_LIBS cpprest_LIBRARY)

LIBFIND_PROCESS(cpprest)
