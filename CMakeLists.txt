cmake_minimum_required (VERSION 3.1)

set(CMAKE_VERBOSE_MAKEFILE ON)

project (NetApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( Threads )

include_directories(
    ${PROJECT_SOURCE_DIR}
    )

set(SOURCE_FILES_LIST
    NetApp.cpp
    TcpConnection.cpp
    ArgsParser.cpp
    Log.cpp
    )
   
set(HEADER_FILES_LIST
    TcpConnection.h
    ArgsParser.h
    Log.h
    )

message(${HEADER_FILES_LIST})
message(${SOURCE_FILES_LIST})
 
 add_executable(${PROJECT_NAME}
    ${SOURCE_FILES_LIST}
    ${HEADER_FILES_LIST}
    )
    
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
    