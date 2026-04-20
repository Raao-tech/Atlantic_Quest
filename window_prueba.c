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

    float scrollingBack = 0.0f;
    
    InitWindow(ancho, alto, "Ventana de prueba para la resolucion");
     Texture2D background = LoadTexture("n1_96.png");

    x = y = 0;
    ancho_cuadrado = alto_cuadrado = 5;
    speed = ancho_cuadrado;
      SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1f;


        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
      
        //----------------------------------------------------------------------------------



        if(x < ancho_cuadrado || y < alto_cuadrado){
            x += speed;
            y +=speed;
        }else {x = y = 0;}

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            // Draw background image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);


            ClearBackground(RAYWHITE);
            DrawRectangle(x,y,ancho_cuadrado,alto_cuadrado, RED);
            DrawText("HOLAA, ESTO ES UNA PRUEBA DE RESOLUCIÓN DE PANTALLITASS", 100, 100,10, BLACK);
        EndDrawing();
    }
    UnloadTexture(background);  // Unload background texture
    CloseWindow();
}
