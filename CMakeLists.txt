cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico2 CACHE STRING "Board type")

if (NOT PICO_SDK_PATH AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/pico-sdk")
    set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/external/pico-sdk")
endif()

include(pico_sdk_import.cmake)

project(Pong_Pico C CXX ASM)

pico_sdk_init()

add_executable(Pong_Pico
    apps/home/home.c
    apps/pong/pong.c
    core/input.c
    drivers/display/display.c
    UI/text/text.c
    UI/fonts/font5x7.c
)

pico_set_program_name(Pong_Pico "Pong_Pico")
pico_set_program_version(Pong_Pico "0.1")

pico_enable_stdio_uart(Pong_Pico 0)
pico_enable_stdio_usb(Pong_Pico 0)

target_link_libraries(Pong_Pico
    pico_stdlib
    hardware_spi
)

target_include_directories(Pong_Pico PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/apps/home
    ${CMAKE_CURRENT_LIST_DIR}/apps/pong
    ${CMAKE_CURRENT_LIST_DIR}/core
    ${CMAKE_CURRENT_LIST_DIR}/drivers/display
    ${CMAKE_CURRENT_LIST_DIR}/UI/text
    ${CMAKE_CURRENT_LIST_DIR}/UI/fonts
)

pico_add_extra_outputs(Pong_Pico)
