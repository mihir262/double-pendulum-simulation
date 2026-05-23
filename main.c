#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MASS_RADIUS 20
#define LINE_THICKNESS 4
#define L1 250
#define L2 200
#define g 9.81

float l1, l2, phi1, phi2, phi1_d, phi2_d, phi1_dd, phi2_dd, m1, m2;

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

void step(){
    phi1_dd =
    (
        -g * (2 * m1 + m2) * sin(phi1)
        - m2 * g * sin(phi1 - 2 * phi2)
        - 2 * sin(phi1 - phi2) * m2 *
          (
              phi2_d * phi2_d * L2 +
              phi1_d * phi1_d * L1 * cos(phi1 - phi2)
          )
    )
    /
    (
        L1 * (2 * m1 + m2 - m2 * cos(2 * phi1 - 2 * phi2))
    );
    
    phi2_dd =
    (
        2 * sin(phi1 - phi2) *
        (
            phi1_d * phi1_d * L1 * (m1 + m2)
            + g * (m1 + m2) * cos(phi1)
            + phi2_d * phi2_d * L2 * m2 * cos(phi1 - phi2)
        )
    )
    /
    (
        L2 * (2 * m1 + m2 - m2 * cos(2 * phi1 - 2 * phi2))
    ); 
}

void init_solver(){
    l1 = L1;
    l2 = L2;
    phi1 = GetRandomValue(-90,90)*DEG2RAD;
    phi2 = GetRandomValue(-90,90)*DEG2RAD;
    phi1_d = 0;
    phi2_d = 0;
    m1 = 1;
    m2 = 1;
}

int main(){
    InitWindow(WIDTH, HEIGHT, "Double Pendulum");

    Vector2 start = (Vector2){WIDTH/2, 0};
    init_solver();
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        draw_double_pendulum(start, phi1, phi2, l1, l2);
        EndDrawing();
    }
    return 0;
}
