#pragma once

#include <stdbool.h>

typedef enum {
    INPUT_BUTTON_UP = 0,
    INPUT_BUTTON_DOWN,
    INPUT_BUTTON_SELECT,
    INPUT_BUTTON_COUNT
} InputButton;

void input_init(void);
void input_update(void);
bool input_is_pressed(InputButton button);
bool input_just_pressed(InputButton button);
bool input_just_released(InputButton button);
