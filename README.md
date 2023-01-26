# Build Raspberry Pi Pico C++ SDK based projects in a Docker container

This repo contains an example project pre-configured to use a Docker container to make your Pico SDK C++ project.

See the [burtonrodman/pico-build-docker](https://github.com/burtonrodman/pico-build-docker) repository if you want to build your own container image.

# Why?

It is often a long and error prone process to get a machine (regardless of OS) setup to properly build any C++ project -- let alone the Raspberry Pi Pico SDK.
Using a Docker container preconfigure with the Pico SDK greatly increases the "it just works" factor -- and therefore the general approachability of using C++ for your Pico projects.

# Prerequisites
- Visual Studio Code
- PowerShell as your default shell within Visual Studio Code
- Docker Desktop

# Use
1. clone this repo and open the folder in Visual Studio Code
2. open CMakeLists.txt and confirm the PICO_BOARD variable matches your hardware.
3. Run the default build task (Ctrl+Shft+B)
4. copy the built uf2 to your device and enjoy the blinken lights
5. add your own dependencies and code, rinse and repeat

# Notes
This has been tested with the following configuration, but I see no reason it shouldn't work on any OS or shell (with minor adjustment)
- Windows 11 22H2
- Visual Studio Code 1.74.3
- PowerShell Code 7.3.1 as default shell in vscode
- Docker Desktop 4.2.0

The build command in `tasks.json` assumes your shell is PowerShell.  Adjust the command appropriately to work with your shell.  For example if using bash, you might replace `${pwd}` with `` `pwd` ``