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
          library/neomatrix.h
          )
# Generate the header file 
pico_generate_pio_header(level ${PROJECT_PATH}/library/neopixel.pio OUTPUT_DIR ${PROJECT_PATH}/library/generated)


# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(level PRIVATE hardware_i2c hardware_pio pico_stdlib)

# Enable USB and UART output
pico_enable_stdio_usb(level 1) 
pico_enable_stdio_uart(level 0)

pico_add_extra_outputs(level)