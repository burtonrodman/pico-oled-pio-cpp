add_library(lib_pico_i2c
    I2C.h
    hardware/HardwareI2C.cpp
    hardware/HardwareI2C.h
    pio/PioI2C.cpp
    pio/PioI2C.h
    SoftI2C.cpp
)

target_link_libraries(lib_pico_i2c
    pico_stdlib
    hardware_i2c
)
