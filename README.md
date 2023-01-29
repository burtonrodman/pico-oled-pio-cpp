# Raspberry Pi Pico I2C abstractions
This repo contains a proof-of-concept to abstract i2c implementations (hardware, pio and software) behind a C++ interface, and rework the ssd1306 oled library to accept this abstraction.

The abstraction currently only defines `init` and `write_blocking` operations -- as these are the only necessary for ssd1306 oled display.

# Status
- *Hardware* - working
- *PIO* - partial, blocked on compiler errors in PIO code
- *Software* - not-started