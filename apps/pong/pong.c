#include "pong.h"

typedef struct {
    int x;
    int y;
    int w;
    int h;
    int prev_y;
} Paddle;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    int prev_x;
    int prev_y;
    int vx;
    int vy;
} Ball;

static int int_sqrt(int x) {
    int r = 0;
    while (r * r <= x) {
        r++;
    }
    return r - 1;
}

static void draw_score(int score, int x, int y) {
    erase_char(x, y, 2, BLACK);
    draw_char((char)('0' + score), x, y, 2, WHITE);
}

static void reset_ball(Ball *ball, int vx, int vy) {
    ball->x = (LCD_W - ball->w) / 2;
    ball->y = (LCD_H - ball->h) / 2;
    ball->prev_x = ball->x;
    ball->prev_y = ball->y;
    ball->vx = vx;
    ball->vy = vy;
}

void run_pong(void) {
    Paddle left_paddle;
    Paddle right_paddle;
    Ball pong_ball;

    int left_player_score = 0;
    int right_player_score = 0;
    int paddle_center;

    const int margin = 6;
    const int max_vy = 10;
    const int movement_speed = 6;
    const int win_score = 5;
    int ball_speed = 6;

    display_init();
    input_init();
    display_fill(BLACK);

    left_paddle.w = 6;
    left_paddle.h = 40;
    left_paddle.x = margin;
    left_paddle.y = (LCD_H - left_paddle.h) / 2;
    left_paddle.prev_y = left_paddle.y;

    right_paddle.w = 6;
    right_paddle.h = 40;
    right_paddle.x = LCD_W - margin - right_paddle.w;
    right_paddle.y = (LCD_H - right_paddle.h) / 2;
    right_paddle.prev_y = right_paddle.y;

    pong_ball.w = 6;
    pong_ball.h = 6;
    reset_ball(&pong_ball, 4, 3);

    draw_score(left_player_score, 75, 10);
    draw_score(right_player_score, 235, 10);
    fill_rect(left_paddle.x, left_paddle.y, left_paddle.w, left_paddle.h, WHITE);
    fill_rect(right_paddle.x, right_paddle.y, right_paddle.w, right_paddle.h, WHITE);
    fill_rect(pong_ball.x, pong_ball.y, pong_ball.w, pong_ball.h, WHITE);
    net_line(4, 12, WHITE);

    while (true) {
        input_update();

        pong_ball.prev_x = pong_ball.x;
        pong_ball.prev_y = pong_ball.y;

        pong_ball.x += pong_ball.vx;
        pong_ball.y += pong_ball.vy;

        if (input_is_pressed(INPUT_BUTTON_DOWN)) {
            left_paddle.prev_y = left_paddle.y;
            left_paddle.y += movement_speed;
            if (left_paddle.y + left_paddle.h >= LCD_H) {
                left_paddle.y = LCD_H - left_paddle.h;
            }

            fill_rect(left_paddle.x, left_paddle.prev_y, left_paddle.w, left_paddle.h, BLACK);
            fill_rect(left_paddle.x, left_paddle.y, left_paddle.w, left_paddle.h, WHITE);
        }

        if (input_is_pressed(INPUT_BUTTON_UP)) {
            left_paddle.prev_y = left_paddle.y;
            left_paddle.y -= movement_speed;
            if (left_paddle.y <= 0) {
                left_paddle.y = 0;
            }

            fill_rect(left_paddle.x, left_paddle.prev_y, left_paddle.w, left_paddle.h, BLACK);
            fill_rect(left_paddle.x, left_paddle.y, left_paddle.w, left_paddle.h, WHITE);
        }

        if (gpio_get(RIGHT_A_PIN) == 0) {
            right_paddle.prev_y = right_paddle.y;
            right_paddle.y += movement_speed;
            if (right_paddle.y + right_paddle.h >= LCD_H) {
                right_paddle.y = LCD_H - right_paddle.h;
            }

            fill_rect(right_paddle.x, right_paddle.prev_y, right_paddle.w, right_paddle.h, BLACK);
            fill_rect(right_paddle.x, right_paddle.y, right_paddle.w, right_paddle.h, WHITE);
        }

        if (gpio_get(RIGHT_B_PIN) == 0) {
            right_paddle.prev_y = right_paddle.y;
            right_paddle.y -= movement_speed;
            if (right_paddle.y < 0) {
                right_paddle.y = 0;
            }

            fill_rect(right_paddle.x, right_paddle.prev_y, right_paddle.w, right_paddle.h, BLACK);
            fill_rect(right_paddle.x, right_paddle.y, right_paddle.w, right_paddle.h, WHITE);
        }

        if (pong_ball.x + pong_ball.w >= LCD_W) {
            fill_rect(pong_ball.prev_x, pong_ball.prev_y, pong_ball.w, pong_ball.h, BLACK);
            left_player_score += 1;
            draw_score(left_player_score, 75, 10);
            ball_speed = 6;
            reset_ball(&pong_ball, -3, 1);
        }

        if (pong_ball.x <= 0) {
            fill_rect(pong_ball.prev_x, pong_ball.prev_y, pong_ball.w, pong_ball.h, BLACK);
            right_player_score += 1;
            draw_score(right_player_score, 235, 10);
            ball_speed = 6;
            reset_ball(&pong_ball, 3, 1);
        }

        if (pong_ball.y + pong_ball.h >= LCD_H) {
            pong_ball.y = LCD_H - pong_ball.h;
            pong_ball.vy = -pong_ball.vy;
        }

        if (pong_ball.y <= 0) {
            pong_ball.y = 0;
            pong_ball.vy = -pong_ball.vy;
        }

        if ((left_player_score >= win_score) || (right_player_score >= win_score)) {
            break;
        }

        if (pong_ball.vx > 0) {
            int ball_center = pong_ball.y + (pong_ball.h / 2);
            paddle_center = right_paddle.y + (right_paddle.h / 2);

            if ((pong_ball.x + pong_ball.w >= right_paddle.x) &&
                (pong_ball.y + pong_ball.h >= right_paddle.y) &&
                (pong_ball.y <= right_paddle.y + right_paddle.h)) {
                int delta = ball_center - paddle_center;
                int vx_mag;

                pong_ball.x = right_paddle.x - pong_ball.w;
                pong_ball.vy = delta * max_vy / (right_paddle.h / 2);

                if (pong_ball.vy > ball_speed - 1) pong_ball.vy = ball_speed - 1;
                if (pong_ball.vy < -(ball_speed - 1)) pong_ball.vy = -(ball_speed - 1);

                vx_mag = int_sqrt(ball_speed * ball_speed - pong_ball.vy * pong_ball.vy);
                if (vx_mag < 1) vx_mag = 1;
                pong_ball.vx = -vx_mag;
            }
        }

        if (pong_ball.vx < 0) {
            int ball_center = pong_ball.y + (pong_ball.h / 2);
            paddle_center = left_paddle.y + (left_paddle.h / 2);

            if ((pong_ball.x < left_paddle.x + left_paddle.w) &&
                (pong_ball.y + pong_ball.h >= left_paddle.y) &&
                (pong_ball.y <= left_paddle.y + left_paddle.h)) {
                int delta = ball_center - paddle_center;
                int vx_mag;

                pong_ball.x = left_paddle.x + left_paddle.w;
                pong_ball.vy = delta * max_vy / (left_paddle.h / 2);

                if (pong_ball.vy > ball_speed - 1) pong_ball.vy = ball_speed - 1;
                if (pong_ball.vy < -(ball_speed - 1)) pong_ball.vy = -(ball_speed - 1);

                vx_mag = int_sqrt(ball_speed * ball_speed - pong_ball.vy * pong_ball.vy);
                if (vx_mag < 1) vx_mag = 1;
                pong_ball.vx = vx_mag;
            }
        }

        fill_rect(pong_ball.prev_x, pong_ball.prev_y, pong_ball.w, pong_ball.h, BLACK);
        fill_rect(pong_ball.x, pong_ball.y, pong_ball.w, pong_ball.h, WHITE);
        net_line(4, 12, WHITE);
        draw_score(left_player_score, 75, 10);
        draw_score(right_player_score, 235, 10);

        sleep_ms(20);
    }

    display_fill(BLACK);
}
