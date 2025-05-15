set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED TARGET)
    set(TARGET linux)  # Default to Linux
endif()

if(${TARGET} STREQUAL "stm32")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/stm32_gcc.cmake)
elseif(${TARGET} STREQUAL "linux")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

project(sockets C CXX ASM)

include_directories(
    inc
)

#### BasicServer ####

set(SRC_FILES
    src/BasicServer_main.cpp
)
add_executable(basic_server ${SRC_FILES})

#### BasicClient ####

set(SRC_FILES
    src/BasicClient_main.cpp
)
add_executable(basic_client ${SRC_FILES})

#### Server ####

set(SRC_FILES
    src/Server_main.cpp
    src/Server.cpp
)

add_executable(server ${SRC_FILES})
target_link_libraries(server
    pthread
)

#### Client ####

set(SRC_FILES
    src/Client_main.cpp
    src/Client.cpp
)

add_executable(client ${SRC_FILES})
target_link_libraries(client
    pthread
)