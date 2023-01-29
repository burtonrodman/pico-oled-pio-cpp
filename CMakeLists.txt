cmake_minimum_required(VERSION 3.18.4)

# CHECK THESE PROPERTIES
set(PICO_BOARD pico_w CACHE STRING "Board type")
set(target_project pico_oled_pio_cpp)


include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(${target_project} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

if (NOT TARGET lib_pico_i2c)
    add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lib_pico_i2c)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lib_pico_oled)

add_executable(${target_project}
    main.cpp
)

target_link_libraries(${target_project} 
    pico_stdlib
    pico_cyw43_arch_none
    hardware_i2c
    hardware_pio
    lib_pico_i2c
    lib_pico_oled
)

pico_add_extra_outputs(${target_project})