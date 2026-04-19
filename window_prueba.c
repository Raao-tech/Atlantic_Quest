#include "./headers/raylib.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argn, char* argv[]){
    int ancho = 0;
    int alto = 0;
    int x, y, speed, ancho_cuadrado, alto_cuadrado;
    if(argn < 3 || !argv) return 1;
    if(!(argv+1) ||  !(argv+2)) return 1;

    ancho = atoi(*(argv+1));
    alto = atoi(*(argv+2));
    
    InitWindow(ancho, alto, "Ventana de prueba para la resolucion");
    x = y = 0;
    ancho_cuadrado = alto_cuadrado = 5;
    speed = ancho_cuadrado;
    while (!WindowShouldClose())
    {
        if(x < ancho_cuadrado || y < alto_cuadrado){
            x += speed;
            y +=speed;
        }else {x = y = 0;}

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(x,y,ancho_cuadrado,alto_cuadrado, RED);
            DrawText("HOLAA, ESTO ES UNA PRUEBA DE RESOLUCIÓN DE PANTALLITASS", 100, 100,10, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}
