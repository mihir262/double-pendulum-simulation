#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MASS_RADIUS 20
#define LINE_THICKNESS 4
#define L1 250
#define L2 200

Vector2 get_end(Vector2 start, float length, float angle){
    return (Vector2){start.x + length * sinf(angle), start.y + length * cosf(angle)};
}

void draw_pendulum(float length, Vector2 start, float angle){
    Vector2 end = get_end(start, length, angle);
    DrawLineEx(start, end, LINE_THICKNESS, WHITE);
    DrawCircleV(end, MASS_RADIUS, RED);
}

void draw_double_pendulum(Vector2 start, float phi1, float phi2, float l1, float l2){
    Vector2 end = get_end(start, l1, phi1);
    draw_pendulum(l2, end, phi2);
    draw_pendulum(l1, start, phi1);
}

int main(){
    InitWindow(WIDTH, HEIGHT, "Double Pendulum");

    Vector2 start = (Vector2){WIDTH/2, 0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        draw_double_pendulum(start, 50*DEG2RAD, -30*DEG2RAD, L1, L2);
        EndDrawing();
    }
    return 0;
}
