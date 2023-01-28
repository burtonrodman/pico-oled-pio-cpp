add_library(lib_pico_i2c
    I2C.h
    HardwareI2C.cpp
    HardwareI2C.h
    PioI2C.cpp
    SoftI2C.cpp
)

target_link_libraries(lib_pico_i2c
    pico_stdlib
    hardware_i2c
)
