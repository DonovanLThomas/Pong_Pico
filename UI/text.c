#include "text.h"
#include "font5x7.h"


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
                draw_pixel(x + col, y + row, font_size, color);
            }
        }
    }
}

