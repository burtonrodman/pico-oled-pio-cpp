add_library(oled
    OLED.h
    OLED.cpp
)

target_link_libraries(oled PRIVATE
    pico_stdlib
    hardware_i2c
    i2c
)

target_include_directories(oled PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})