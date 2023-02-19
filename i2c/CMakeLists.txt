add_library(i2c
    I2C.h
    HardwareI2C.h
    HardwareI2C.cpp
    pio_i2c.c
    pio_i2c.h
    PioI2C.cpp
    PioI2C.h
)

pico_generate_pio_header(i2c ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

set_source_files_properties(pio_i2c.h  PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.h PROPERTIES COMPILE_FLAGS -fpermissive)
set_source_files_properties(PioI2C.cpp PROPERTIES COMPILE_FLAGS -fpermissive)

target_link_libraries(i2c PRIVATE
    pico_stdlib
    hardware_i2c
    hardware_pio
)

target_include_directories(i2c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})