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

target_sources(${target_project} PUBLIC
    main.cpp
    MixerModel.h
    tusb_config.h
)

set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS -fpermissive)

target_include_directories(${target_project} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(i2c)
add_subdirectory(oled)

target_link_libraries(${target_project} PRIVATE
    pico_stdlib
    pico_util
    hardware_i2c
    hardware_pio
    hardware_rtc
    pico_cyw43_arch_none
    i2c
    oled
    tinyusb_host
    tinyusb_board
)

pico_add_extra_outputs(${target_project})

add_compile_options(
    -Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
    -Wconversion
)