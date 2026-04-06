#pragma once

#include "display.h"
#include <stdint.h>

bool draw_char(char letter, int x, int y, int font_size, int color);
void erase_char(int x, int y, int font_size, int bg_col);
void draw_string(char *letter, int x, int y, int font_size, int color, bool typing);
