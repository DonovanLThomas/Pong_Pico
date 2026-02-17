# 🕹️ Raspberry Pi Pico Pong

A fully functional Pong game built from scratch in C for the Raspberry
Pi Pico 2 using an SPI-driven LCD display.

This project was developed to strengthen my understanding of:

-   Embedded C programming
-   SPI communication at the hardware level
-   Real-time game loop design
-   Manual graphics rendering (no framebuffer)
-   Collision detection and object state management
-   Low-level debugging on microcontrollers

------------------------------------------------------------------------

## 🎮 Features

-   Real-time paddle movement
-   Ball physics and wall collision handling
-   Paddle collision detection
-   Score tracking (0--9)
-   Manual erase-and-redraw rendering system
-   Custom SPI-based LCD driver implementation

------------------------------------------------------------------------

## 🧠 Graphics & Rendering Implementation

All drawing operations are performed **without a framebuffer**.

Key components include:

-   Custom `fill_rect()` implementation for efficient rectangle
    rendering
-   Chunk-based SPI buffer transmission for fast pixel writes
-   Manual draw logic to erase previous object positions before
    redrawing
-   Optimized redraw strategy to reduce flicker
-   Selective screen updates instead of full-screen clearing

This approach simulates a lightweight real-time rendering engine on
constrained hardware.

------------------------------------------------------------------------

## ⚙️ Performance Considerations

-   Used chunk-based pixel transfer to improve screen refresh rate
-   Avoided unnecessary full-screen clears
-   Minimized SPI traffic by only redrawing changed regions
-   Structured game loop for deterministic update behavior

------------------------------------------------------------------------

## 🔧 Hardware Used

-   Raspberry Pi Pico 2 (RP2350)
-   SPI LCD Display (ST7789 / ILI9341 driver)
-   Breadboard and jumper wires
-   Push buttons for paddle control

------------------------------------------------------------------------

## 🛠️ Build Instructions

### Prerequisites

-   Raspberry Pi Pico SDK installed
-   CMake
-   ARM GCC toolchain

Make sure your `PICO_SDK_PATH` environment variable is set correctly.

### Build Steps

``` bash
mkdir build
cd build
cmake ..
make
```

After building, drag the generated `.uf2` file onto the Pico while in
BOOTSEL mode.

------------------------------------------------------------------------

## 📂 Project Structure

    Pong/
        Pong.c
        CMakeLists.txt
        pico_sdk_import.cmake

    Displaying_pixels/
        Displaying_pixels.c
        Displaying_pixels.h
        CMakeLists.txt
        pico_sdk_import.cmake

------------------------------------------------------------------------

## 🚀 What I Learned

-   How SPI communication works at a register and protocol level
-   How to design a real-time embedded game loop
-   How to implement collision logic using structured state tracking
-   How to optimize rendering on resource-constrained hardware
-   Proper Git workflow for embedded systems projects

------------------------------------------------------------------------

## 📌 Future Improvements

-   AI opponent mode
-   Sound effects using PWM
-   Menu screen and game states
-   Frame timing control for smoother motion
-   Sprite-based graphics instead of primitive shapes

------------------------------------------------------------------------

## 👨‍💻 Author
DONOVAN THOMAS

Built as part of ongoing embedded systems development and low-level C
practice.
