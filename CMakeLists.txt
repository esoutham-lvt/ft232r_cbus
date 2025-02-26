cmake_minimum_required(VERSION 3.12)
set(PROG "ft232r_cbus")

project(${PROG})
set(COMPILE_DEFINITIONS -02 -Wall)
add_executable(${PROG} main.c)
target_link_libraries(${PROG} /lib/aarch64-linux-gnu/libftdi1.so.2)
target_link_libraries(${PROG} /usr/lib/aarch64-linux-gnu/libusb.so)
