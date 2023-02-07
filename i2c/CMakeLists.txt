add_library(i2c
    I2C.h
    HardwareI2C.h
    HardwareI2C.cpp
    SoftI2C.cpp
)

target_link_libraries(i2c PRIVATE
    pico_stdlib
    hardware_i2c
    hardware_pio
)

target_include_directories(i2c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})