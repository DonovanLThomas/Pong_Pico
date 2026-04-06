#pragma once
#include "pico/stdlib.h"
#include "hardware/spi.h"


//GPIO Pins used on RASP PI PICO
#define CS_PIN  17
#define DC_PIN  16
#define RST_PIN 20
#define LEFT_A_PIN 14
#define LEFT_B_PIN 15
#define RIGHT_A_PIN 12
#define RIGHT_B_PIN 13

#define BLACK  0x0000
#define WHITE  0xFFFF
#define ORANGE 0xFD20


//Screen Size
#define LCD_W 320
#define LCD_H 240

void display_init(void);
void draw_pixel(int x, int y, int color);
void display_fill(int color);
void fill_rect(int x, int y, int w, int h, int color);
void net_line(int rectangle_width, int rectangle_height, int color);
