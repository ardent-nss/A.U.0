cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")

project(au0 C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Oz -mcpu=cortex-m0plus -mtune=cortex-m0plus -static-libstdc++")

set(PICO_BOARD pico_w) # Project A.M.0 is based on the Pico W.

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(au0
  main.cpp
)

pico_enable_stdio_uart(au0 0) # both UARTS are used by the program for the built-in traffic monitor
pico_enable_stdio_usb(au0 1)  #

pico_add_extra_outputs(au0)

target_link_libraries(au0 pico_stdlib pico_multicore hardware_gpio hardware_uart)
