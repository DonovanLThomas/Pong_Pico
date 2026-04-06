#include "home.h"
#include "pong.h"

void boot_screen(void){
    display_init();
    input_init();
    display_fill(BLACK);
    draw_string("RADON", 85, 103, 5, ORANGE, true);

    sleep_ms(2000);
}
/*
Home Screen Index
0 - Games
1 - MP3
2 - Reminders
*/
void home_screen(void){
    int selected_index = 0;
    int updated_y = 80;
    int previous_y = 80;

    display_fill(BLACK);
    draw_string("RADON MENU", 85, 0, 3, ORANGE, false);
    draw_string("PONG", 15, 80, 2, ORANGE, false);
    draw_string("MP3", 15, 115, 2, ORANGE, false);
    draw_string("REMINDERS", 15, 150, 2, ORANGE, false);
    draw_char('>', 0, updated_y, 2, WHITE);

    while(true){
        input_update();

        if (input_just_pressed(INPUT_BUTTON_DOWN)){
            previous_y = updated_y;
            selected_index = (selected_index + 1) % 3;
            updated_y = 80 + (35 * selected_index);
            draw_char('>', 0, updated_y, 2, WHITE);
            erase_char(0, previous_y, 2, BLACK);
            sleep_ms(150);
        }

        if (input_just_pressed(INPUT_BUTTON_UP)){
            previous_y = updated_y;
            selected_index = (selected_index + 2) % 3;
            updated_y = 80 + (35 * selected_index);
            draw_char('>', 0, updated_y, 2, WHITE);
            erase_char(0, previous_y, 2, BLACK);
            sleep_ms(150);
        }

        if (input_just_pressed(INPUT_BUTTON_SELECT)) {
            if (selected_index == 0) {
                run_pong();
                display_fill(BLACK);
                draw_string("RADON MENU", 85, 0, 3, ORANGE, false);
                draw_string("PONG", 15, 80, 2, ORANGE, false);
                draw_string("MP3", 15, 115, 2, ORANGE, false);
                draw_string("REMINDERS", 15, 150, 2, ORANGE, false);
                draw_char('>', 0, updated_y, 2, WHITE);
            }
        }
    }
}

int main(void){
    boot_screen();
    home_screen();
}
