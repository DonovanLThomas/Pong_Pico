#include "text.h"
#include "font5x7.h"

int screen_x = 0;
int screen_y = 0;

int default_spacing = 6;
//Top of binary is top of function so to do shift have to do bits >> 6-row
void draw_char(char letter, int x, int y, int font_size, int color){
    //lowercase conversion
    if (letter >= 97 && letter <= 122){
        letter = letter - 32;
    }

    if (letter < 32 || letter > 127){
        return;
    }
    int position = letter - 32;

    for(int col = 0; col <= 4; col++){
        for(int row = 0; row <= 6; row++){
            if ((font[position][col] >> (6 - row)) & 1){
                screen_x = x + col * font_size;
                screen_y = y + row * font_size;
                fill_rect(screen_x, screen_y, font_size, font_size, color);
            }
        }
    }
}

void draw_string(char *letter, int length, int x, int y, int font_size, int color){
    default_spacing = default_spacing * font_size;
    for (int i = 0; i <= length; i ++){
        draw_char(letter[i], x + default_spacing * i, y, font_size, color);
    }
}

