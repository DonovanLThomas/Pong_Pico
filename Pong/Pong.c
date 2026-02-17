#include "Displaying_pixels.h"

//Structs for the Paddle and the Ball
typedef struct{
    int x;
    int y;
    int w;
    int h;
    int prev_y;
} Paddle;

typedef struct{
    int x;
    int y;
    int w;
    int h;
    int prev_x;
    int prev_y;
    int vx;
    int vy;
} Ball;

Paddle Left_paddle;
Paddle Right_paddle;
Ball Pong_ball;



int main()
{
    //Display initialization making screen black
    display_init();
    display_fill(0x0000);
    // net_line(5,10,0xFFFF);

    //Starting Scores
    int Left_player_score = 0;
    int Right_player_score = 0;

    //distance from wall
    int margin = 6;

    int paddle_center;
    int max_vy = 15;
    int movement_speed = 10;
    int win_score = 5;

    //Left paddle initial values
    Left_paddle.w = 6;
    Left_paddle.h = 40;
    Left_paddle.x = margin;
    Left_paddle.y = (LCD_H - Left_paddle.h) / 2;
    Left_paddle.prev_y = Left_paddle.y;
    
    fill_rect(Left_paddle.x, Left_paddle.y, Left_paddle.w, Left_paddle.h, 0xFFFF);

    //Right paddle initial values
    Right_paddle.w = 6;
    Right_paddle.h = 40;
    Right_paddle.x = LCD_W - margin - Right_paddle.w;
    Right_paddle.y = (LCD_H - Right_paddle.h) / 2;
    Right_paddle.prev_y = Right_paddle.y;

    fill_rect(Right_paddle.x, Right_paddle.y, Right_paddle.w, Right_paddle.h, 0xFFFF);

    //Ball initial values
    Pong_ball.w = 6;
    Pong_ball.h = 6;
    Pong_ball.x = ((LCD_W - Pong_ball.w) / 2 )+ 20;
    Pong_ball.y = ((LCD_H - Pong_ball.h) / 2 )+ 20;
    Pong_ball.prev_x = Pong_ball.x;
    Pong_ball.prev_y = Pong_ball.y;
    Pong_ball.vx = 7;
    Pong_ball.vy = 5;

    fill_rect(Pong_ball.x, Pong_ball.y, Pong_ball.w, Pong_ball.h, 0xFFFF);

    while(true){
        //Score Board
        draw_left_digit(Left_player_score, 0xFFFF);
        draw_right_digit(Right_player_score, 0xFFFF);

        
        //Making ball move
        Pong_ball.prev_x = Pong_ball.x;
        Pong_ball.prev_y = Pong_ball.y;
        Pong_ball.x += Pong_ball.vx;
        Pong_ball.y += Pong_ball.vy;

        //ball borders
        int bx = Pong_ball.x, by = Pong_ball.y, bw = Pong_ball.w, bh = Pong_ball.h;
        int ball_center = (by + (bh / 2));
        
        //left_paddle borders
        int lpx = Left_paddle.x, lpy = Left_paddle.y, lpw = Left_paddle.w, lph = Left_paddle.h;
   
        //right_paddle borders
        int rpx = Right_paddle.x, rpy = Right_paddle.y, rpw = Right_paddle.w, rph = Right_paddle.h;

        //Button Movement of Paddles
        if (gpio_get(LEFT_A_PIN) == 0){

            Left_paddle.prev_y = Left_paddle.y;
            Left_paddle.y += movement_speed;
            if (lpy + lph >= LCD_H) {Left_paddle.y = LCD_H - lph;}

            fill_rect(Left_paddle.x, Left_paddle.prev_y, Left_paddle.w, Left_paddle.h, 0x0000);
            fill_rect(Left_paddle.x, Left_paddle.y, Left_paddle.w, Left_paddle.h, 0xFFFF);
        }

        if (gpio_get(LEFT_B_PIN) == 0){

            Left_paddle.prev_y = Left_paddle.y;
            Left_paddle.y -= movement_speed;
            if (Left_paddle.y <= 0) {Left_paddle.y = 0;}

            fill_rect(Left_paddle.x, Left_paddle.prev_y, Left_paddle.w, Left_paddle.h, 0x0000);
            fill_rect(Left_paddle.x, Left_paddle.y, Left_paddle.w, Left_paddle.h, 0xFFFF);
        }

        if (gpio_get(RIGHT_A_PIN) == 0){

            Right_paddle.prev_y = Right_paddle.y;
            Right_paddle.y += movement_speed;
            if (Right_paddle.y + Right_paddle.h >= LCD_H) {
                Right_paddle.y = LCD_H - Right_paddle.h;
            }

            fill_rect(Right_paddle.x, Right_paddle.prev_y, Right_paddle.w, Right_paddle.h, 0x0000);
            fill_rect(Right_paddle.x, Right_paddle.y, Right_paddle.w, Right_paddle.h, 0xFFFF);
        }

        if (gpio_get(RIGHT_B_PIN) == 0){

            Right_paddle.prev_y = Right_paddle.y;
            Right_paddle.y -= movement_speed;
            if (Right_paddle.y < 0) {Right_paddle.y = 0;}
            
            fill_rect(Right_paddle.x, Right_paddle.prev_y, Right_paddle.w, Right_paddle.h, 0x0000);
            fill_rect(Right_paddle.x, Right_paddle.y, Right_paddle.w, Right_paddle.h, 0xFFFF);
        }

        //When pong ball goes past paddle

        //Left Player Scores
        if (Pong_ball.x + Pong_ball.w >= LCD_W){
            Pong_ball.x = (LCD_W - Pong_ball.w) / 2;
            Pong_ball.y = (LCD_H - Pong_ball.h) / 2;
            Pong_ball.vy = 1;
            Left_player_score += 1;
            draw_left_digit(Left_player_score, 0xFFFF);
        }

        //Right Player Scores
        if (Pong_ball.x <= 0){
            Pong_ball.x = (LCD_W - Pong_ball.w) / 2;
            Pong_ball.y = (LCD_H - Pong_ball.h) / 2;
            Pong_ball.vx = 5;
            Pong_ball.vy = 1;
            Right_player_score += 1;
            draw_right_digit(Right_player_score, 0xFFFF);

        }

        //Hitting Top and Bottom of Screen
        if (Pong_ball.y + Pong_ball.h >= LCD_H){
            Pong_ball.y = LCD_H - Pong_ball.h;
            Pong_ball.vy = -Pong_ball.vy;
        }
        if (Pong_ball.y <= 0){
            Pong_ball.y = 0;
            Pong_ball.vy = -Pong_ball.vy;
        }

        //Win Condition
        if ((Left_player_score >= win_score) ||(Right_player_score >= win_score)){
            break;
        }
        
        //Collision for right paddle
        if (Pong_ball.vx > 0) {

            //Angle calculator for bouncing off of Paddle
            paddle_center = Right_paddle.y + (Right_paddle.h / 2);
            int delta = ball_center - paddle_center;

            if ((bx + bw >= rpx) && (by + bh >=rpy) && (by <= Right_paddle.y + Right_paddle.h)){
                Pong_ball.x = rpx - Pong_ball.w;
                Pong_ball.vy = delta * max_vy / (rph/2);
                if (Pong_ball.vy == 0){
                    if (delta > 0) Pong_ball.vy = 1;
                    else if (delta < 0) Pong_ball.vy = -1;
                }
                Pong_ball.vx = -Pong_ball.vx;
            }
        }

        //Collision for left paddle
        if (Pong_ball.vx < 0) {

            //Angle calculator for bouncing off of Paddle
            paddle_center = Left_paddle.y + (Left_paddle.h / 2);
            int delta = ball_center - paddle_center;

            if ((bx < lpx + lpw) && (by + bh >=lpy) && (by <= Left_paddle.y + Left_paddle.h)){
                Pong_ball.x = lpx + lpw;
                Pong_ball.vy = delta * max_vy / (lph/2);
                if (Pong_ball.vy == 0){1 * (delta/delta);}
                Pong_ball.vx = -Pong_ball.vx;
            }
        }

        fill_rect(Pong_ball.prev_x, Pong_ball.prev_y, Pong_ball.w, Pong_ball.h, 0x0000);
        fill_rect(Pong_ball.x, Pong_ball.y, Pong_ball.w, Pong_ball.h, 0xFFFF);
        net_line(4, 12, 0xFFFF);


        sleep_ms(20);
    }

    display_fill(0x07E0);
}
