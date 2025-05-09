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

# Configure here which STM32 target(s) to build
option(HELLO_WORLD_LIN_EXAMPLE "Compile LINUX example" ON)
option(HELLO_WORLD_L4_EXAMPLE "Compile L4 example" OFF)

project(hello_world C CXX ASM)
set(MAIN_SOURCE_FILE main.cpp)

if(HELLO_WORLD_LIN_EXAMPLE)
    # TODO linux apppends
    # list(APPEND CMSIS_COMP_LIST STM32F1)
    # list(APPEND HAL_COMP_LIST STM32F1)
endif()

if(HELLO_WORLD_L4_EXAMPLE)
    list(APPEND CMSIS_COMP_LIST STM32L4)
    list(APPEND HAL_COMP_LIST STM32L4)
endif()

# Linux
if(HELLO_WORLD_LIN_EXAMPLE)

    # Collect source files
    set(SRC_FILES
        src/main.cpp
        src/HelloWorld.cpp
    )

    # Include directories
    include_directories(
        inc
    )

    add_executable(hello_world-lin ${SRC_FILES})
    target_link_libraries(hello_world-lin
        pthread
    )

endif()

# STM32L476RG
if(HELLO_WORLD_L4_EXAMPLE)
    add_executable(hello_world-l4 ${MAIN_SOURCE_FILE} stm32l4xx_hal_conf.h)
    target_link_libraries(hello_world-l4
        HAL::STM32::L4::RCC
        HAL::STM32::L4::GPIO
        HAL::STM32::L4::CORTEX
        CMSIS::STM32::L476RG
        STM32::NoSys
    )
    stm32_print_size_of_target(hello_world-l4)
    stm32_generate_binary_file(hello_world-l4)

endif()
