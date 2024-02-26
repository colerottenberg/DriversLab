cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(prj C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
message("PROJECT_PATH: ${PROJECT_PATH}")
# Initialize the SDK
pico_sdk_init()

add_executable(level
          src/level.cpp
          library/lis3dh.h
          library/lis3dh_i2c.c
  )

# target_sources(level PRIVATE src/level.cpp)
# target_sources(level PRIVATE library/lis3dh.h)

# target_include_directories(level PRIVATE ${PROJECT_PATH}/library/lis3dh)
# target_include_directories(lis3dh PRIVATE ${PROJECT_PATH}/library/lis3dh)

target_link_libraries(level PRIVATE hardware_i2c hardware_pio pico_stdlib)
pico_enable_stdio_usb(level 1) 
pico_enable_stdio_uart(level 0)
pico_add_extra_outputs(level)