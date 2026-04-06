#include "input.h"

#include "display.h"

static bool current_state[INPUT_BUTTON_COUNT];
static bool previous_state[INPUT_BUTTON_COUNT];

static uint button_pin(InputButton button) {
    switch (button) {
        case INPUT_BUTTON_UP:
            return LEFT_A_PIN;
        case INPUT_BUTTON_DOWN:
            return LEFT_B_PIN;
        case INPUT_BUTTON_SELECT:
            return RIGHT_A_PIN;
        case INPUT_BUTTON_COUNT:
        default:
            return LEFT_A_PIN;
    }
}

static bool read_button(InputButton button) {
    return gpio_get(button_pin(button)) == 0;
}

void input_init(void) {
    for (int i = 0; i < INPUT_BUTTON_COUNT; ++i) {
        current_state[i] = read_button((InputButton)i);
        previous_state[i] = current_state[i];
    }
}

void input_update(void) {
    for (int i = 0; i < INPUT_BUTTON_COUNT; ++i) {
        previous_state[i] = current_state[i];
        current_state[i] = read_button((InputButton)i);
    }
}

bool input_is_pressed(InputButton button) {
    return current_state[button];
}

bool input_just_pressed(InputButton button) {
    return current_state[button] && !previous_state[button];
}

bool input_just_released(InputButton button) {
    return !current_state[button] && previous_state[button];
}
