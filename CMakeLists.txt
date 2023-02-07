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

add_executable(${target_project})

pico_generate_pio_header(${target_project} ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

target_sources(${target_project} PUBLIC
    main.cpp
    OLED.cpp
    OLED.h
    pio_i2c.c
    pio_i2c.h
    PioI2C.cpp
    PioI2C.h
)

set_source_files_properties(pio_i2c.h  PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.h PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.cpp PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS -fpermissive)

add_subdirectory(i2c)

target_link_libraries(${target_project} PRIVATE
    pico_stdlib
    hardware_i2c
    hardware_pio
    pico_cyw43_arch_none
    i2c
)

pico_add_extra_outputs(${target_project})

add_compile_options(
    -Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
    -Wconversion
)