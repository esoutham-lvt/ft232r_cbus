cmake_minimum_required(VERSION 3.12)
set(PROG "ft232r_cbus")

project(${PROG})
set(COMPILE_DEFINITIONS -02 -Wall)
include_directories(
    /usr/local/include              # linux include folder
    /opt/homebrew/include           # homebrew include for macOS (symlinks)
)
link_directories(
        /usr/local/lib              # linux lib folder
        /opt/homebrew/lib           # homebrew lib for macOS (symlinks)
)

add_executable(${PROG} main.c)
target_link_libraries(${PROG} libftdi1.so.2)
target_link_libraries(${PROG} libusb.so)        # target for RasPi-OS
#target_link_libraries(${PROG} libusb-1.0.a)     # target for macOS
