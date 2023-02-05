add_library(lib_pico_i2c
    pio_i2c.h
    pio_i2c.c
    I2C.h
    HardwareI2C.h
    PioI2C.h
    HardwareI2C.cpp
    PioI2C.cpp
    SoftI2C.cpp
)

pico_generate_pio_header(lib_pico_i2c
    ${CMAKE_CURRENT_LIST_DIR}/i2c.pio
)

set_source_files_properties(pio_i2c.h  PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.h PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.cpp PROPERTIES COMPILE_FLAGS -fpermissive)

target_link_libraries(lib_pico_i2c
    pico_stdlib
    hardware_i2c
    hardware_pio
)
