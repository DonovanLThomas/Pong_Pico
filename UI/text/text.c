#include "text.h"
#include "font5x7.h"

int screen_x = 0;
int screen_y = 0;

int base_advance = 6;
int base_space_advance = 3;
//Top of binary is top of function so to do shift have to do bits >> 6-row
//changed to bool to handle cases where trying to draw a letter is off screen
bool draw_char(char letter, int x, int y, int font_size, int color){
    //lowercase conversion
    if (letter >= 97 && letter <= 122){
        letter = letter - 32;
    }

    if (letter < 32 || letter > 127){
        return false;
    }

    int position = letter - 32;

    for(int col = 0; col <= 4; col++){
        for(int row = 0; row <= 6; row++){
            if ((font[position][col] >> (6 - row)) & 1){
                screen_x = x + col * font_size;
                screen_y = y + row * font_size;
                //checking for off screen
                if (screen_x >= LCD_W || screen_y >= LCD_H){
                    return false;
                }
                fill_rect(screen_x, screen_y, font_size, font_size, color);
            }
        

    
        }

    }
    return true;
}

void erase_char(int x, int y, int font_size, int bg_color){
    fill_rect(x,y, 5 * font_size, 7* font_size, bg_color);
}

int word_length(char *word, int start){
    int length = 0;
    while(word[start] != '\0' && word[start] != ' '){
        length++;
        start++;
    }
    return length;
}

int word_width(char *word, int start, int font_size){
    int w_length = word_length(word, start);
    int advance = base_advance * font_size;

    return w_length * advance;
}

void draw_string(char *letter, int x, int y, int font_size, int color, bool typing){
    int advance = base_advance * font_size;
    int space_advance = base_space_advance * font_size;
    int line_height = 8 * font_size;


    int starting_x = x;
    int current_x = x;
    int current_y = y;
    for (int i = 0; letter[i] != '\0'; i ++){
        if(typing){
            sleep_ms(250);
        }

        if (letter[i] == ' '){
            if (current_x + space_advance > LCD_W){
                current_x = starting_x;
                current_y += line_height;
            }
            else{
                current_x += space_advance;
            }
        }
        else{
            int whole_word_width = word_width(letter, i, font_size);

            if (current_x + whole_word_width > LCD_W){
                current_x = starting_x;
                current_y += line_height;
            }

            while (letter[i] != '\0' && letter[i] != ' '){
                if (typing){
                    sleep_ms(250);
                }

                draw_char(letter[i], current_x, current_y, font_size, color);
                current_x += advance;
                i++;
            }

            if (letter[i] == '\0'){
                break;
            }

            if (current_x + space_advance > LCD_W){
                current_x = starting_x;
                current_y += line_height;
            }
            else{
                current_x += space_advance;
            }
        }
    }
}

