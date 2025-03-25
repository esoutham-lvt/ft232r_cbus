cmake_minimum_required(VERSION 3.12)
set(PROG "ft232r_cbus")

project(${PROG})
set(COMPILE_DEFINITIONS -02 -Wall)
include_directories(
        /usr/local/include              # linux include folder
        /opt/homebrew/include/libftdi1  # homebrew include for macOS (symlinks)
)
link_directories(
        /usr/local/lib                  # linux lib folder
        /opt/homebrew/lib               # homebrew lib for macOS (symlinks)
)

add_executable(${PROG} main.c)
#ORIGINAL FTDI-Library and libusb (won't build for macOS)
target_link_libraries(${PROG} /lib/aarch64-linux-gnu/libftdi.so)        # linux, ftdi original library
target_link_libraries(${PROG} /usr/lib/aarch64-linux-gnu/libusb.so)     # linux, libusb original library

# UPDATE for Newer version of libftdi1 (required for macOS)
#target_link_libraries(${PROG} libftdi1.so.2)      # ftdi1 updated library
