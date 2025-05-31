

#include "include/raylib.h"
#include <stdio.h>
const int screenWidth = 1200;
const int screenHeight = 600;

int player_left_score = 0;
int player_right_score = 0;

typedef struct Circle
{
    Vector2 position;
    Vector2 delta;
    int radius;
} Circle;

typedef struct Paddle
{
    Rectangle rectangle;
    float delta;
} Paddle; 

void update_circle_coordinates(Circle *circle)
{

    circle->position.x += circle->delta.x;
    circle->position.y += circle->delta.y;

    if(circle->position.y + circle->radius >= screenHeight || circle->position.y - circle->radius <= 0)
    {
        circle->delta.y *= -1;
    }


    if(circle->position.x - circle->radius <= 0) {
        circle->position.x = screenWidth / 2;
        circle->position.y = screenHeight / 2;
        circle->delta.x *= -1;

        player_right_score++;
    }

    if(circle->position.x + circle->radius >= screenWidth) {
        circle->position.x = screenWidth / 2;
        circle->position.y = screenHeight / 2;
        circle->delta.x *= -1;
        player_left_score++;
    }
}


void update_paddles_coordinate(Paddle *left_paddle, Paddle *right_paddle, Circle *circle)
{

    if(IsKeyDown(KEY_W) && left_paddle->rectangle.y - left_paddle->delta >= 0)
    {
        left_paddle->rectangle.y -= left_paddle->delta;
    }

        if(IsKeyDown(KEY_S) && left_paddle->rectangle.y + left_paddle->rectangle.height + left_paddle->delta <= screenHeight)
        {
        left_paddle->rectangle.y += left_paddle->delta;
    }

    if(IsKeyDown(KEY_UP) && right_paddle->rectangle.y - right_paddle->delta >= 0)
    {
        right_paddle->rectangle.y -= right_paddle->delta;
    }

    if(IsKeyDown(KEY_DOWN) && right_paddle->rectangle.y + right_paddle->rectangle.height + right_paddle->delta <= screenHeight)
    {
        right_paddle->rectangle.y += right_paddle->delta;
    }


    // simple ai
    int paddle_center = right_paddle->rectangle.y + (right_paddle->rectangle.height / 2);

    if(circle->position.y > paddle_center) {
        right_paddle->rectangle.y += right_paddle->delta;
    }

    if(circle->position.y < paddle_center) {
        right_paddle->rectangle.y -= right_paddle->delta;
    }
}

void check_colision(Paddle *paddle, Circle *circle)
{
    
    int paddle_left = paddle->rectangle.x;
    int paddle_right = paddle->rectangle.x + paddle->rectangle.width;

    int paddle_top = paddle->rectangle.y;
    int paddle_bottom = paddle->rectangle.y + paddle->rectangle.height;



    int circle_left = circle->position.x - circle->radius;
    int circle_top = circle->position.y - circle->radius;
    int circle_right = circle->position.x + circle->radius;
    int circle_bottom = circle->position.y + circle->radius;

    if(circle_right >= paddle_left && circle_left <= paddle_right && circle_top <= paddle_bottom && circle_bottom >= paddle_top)
    {
        circle->delta.x *= -1;
    }

}

int main(void)
{

    int circle_speed = 10;
    Circle circle = {
        { screenWidth / 2 ,screenHeight / 2},
        {-circle_speed,-circle_speed},
        10,
    };

    
    int paddle_width = 10;
    int paddle_height = 150;
    int paddle_x_position = 25;
    int paddle_y_position = screenHeight / 2  - (paddle_height / 2);
    Paddle left_paddle = {
        {
            paddle_x_position,
            paddle_y_position,
            paddle_width,
            paddle_height,
        },
        5
    };

    
    Paddle right_paddle = {
        {
            screenWidth - paddle_x_position - paddle_width,
            paddle_y_position,
            paddle_width,
            paddle_height
        },
        5
    };

    InitWindow(screenWidth, screenHeight, "raylib pong game");

    SetTargetFPS(60); 

    while (!WindowShouldClose())        
    {

        update_circle_coordinates(&circle);
        update_paddles_coordinate(&left_paddle, &right_paddle, &circle);
        check_colision(&left_paddle, &circle);
        check_colision(&right_paddle, &circle);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(circle.position, circle.radius, PINK);

            DrawRectangleRec(left_paddle.rectangle, WHITE);
            DrawRectangleRec(right_paddle.rectangle, WHITE);

            DrawText(TextFormat("%i", player_left_score),  screenWidth / 2  - 100, 20, 32, WHITE );

            DrawText(TextFormat("%i", player_right_score),  screenWidth / 2  + 100, 20, 32, WHITE );
        EndDrawing();
    }

    CloseWindow();

    return 0;
}