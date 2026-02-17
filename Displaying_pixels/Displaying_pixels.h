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

//Screen Size
#define LCD_W 320
#define LCD_H 240

void display_init(void);
void display_fill(int color);
void fill_rect(int x, int y, int w, int h, int color);
void net_line(int rectangle_width, int rectangle_height, int color);
void erase_left_score();
void erase_right_score();

void A1(int color);
void B1(int color);
void C1(int color);
void D1(int color);
void E1(int color);
void F1(int color);
void G1(int color);

void A2(int color);
void B2(int color);
void C2(int color);
void D2(int color);
void E2(int color);
void F2(int color);
void G2(int color);

void Left0(int color);
void Left1(int color);
void Left2(int color);
void Left3(int color);
void Left4(int color);
void Left5(int color);
void Left6(int color);
void Left7(int color);
void Left8(int color);
void Left9(int color);

void draw_left_digit(int score, int color);
void draw_right_digit(int score, int color);
void Right0(int color);
void Right1(int color);
void Right2(int color);
void Right3(int color);
void Right4(int color);
void Right5(int color);
void Right6(int color);
void Right7(int color);
void Right8(int color);
void Right9(int color);