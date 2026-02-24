#include "text.h"
#include "font5x7.h"

int screen_x = 0;
int screen_y = 0;

int base_advance = 6;
int base_space_advance = 3;
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
    int advnace = base_advance * font_size;
    int space_advance = base_space_advance * font_size;
    int current_x = x;
    for (int i = 0; i < length; i ++){
        draw_char(letter[i], current_x, y, font_size, color);
        if (letter[i] == ' '){
            current_x += space_advance;
        }
        else{
            current_x += advnace;
        }
    }
}

