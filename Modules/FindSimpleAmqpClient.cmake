#Find the Rabbitmq C library

INCLUDE(LibFindMacros)

# Find the include directories
FIND_PATH(Simpleamqpclient_INCLUDE_DIR
	NAMES SimpleAmqpClient/SimpleAmqpClient.h
    HINTS ${Simpleamqpclient_DIR}/include
	)

FIND_LIBRARY(Simpleamqpclient_LIBRARY
	NAMES SimpleAmqpClient
    HINTS ${Simpleamqpclient_DIR}/lib
	)

SET(Simpleamqpclient_PROCESS_INCLUDES Simpleamqpclient_INCLUDE_DIR)
SET(Simpleamqpclient_PROCESS_LIBS Simpleamqpclient_LIBRARY)

LIBFIND_PROCESS(Simpleamqpclient)
