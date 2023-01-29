add_library(lib_pico_i2c
    I2C.h
    HardwareI2C.cpp
    HardwareI2C.h
    PioI2C.cpp
    PioI2C.h
    pio_i2c.c
    pio_i2c.h
    SoftI2C.cpp
)

pico_generate_pio_header(lib_pico_i2c
    ${CMAKE_CURRENT_LIST_DIR}/i2c.pio
)

target_link_libraries(lib_pico_i2c
    pico_stdlib
    hardware_i2c
    hardware_pio
)
