add_library(lib_pico_oled
    OLED.h
    OLED.cpp
)

if (NOT TARGET lib_pico_i2c)
    add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lib_pico_i2c build)
endif()

target_link_libraries(lib_pico_oled
    pico_stdlib
    lib_pico_i2c
)
