#include "functions.hpp"


int main()
{
    InitWindow(screenWidth, screenHeight, "WOW - Abdullah Akkaya");
    background = LoadTexture("/Users/abdullah/Desktop/210229042_Abdullah_Akkaya/src/background.png");
    boxImage = LoadTexture("/Users/abdullah/Desktop/210229042_Abdullah_Akkaya/src/Boxx.png");
    boxImagePink = LoadTexture("/Users/abdullah/Desktop/210229042_Abdullah_Akkaya/src/BoxPink.png");
    SetTargetFPS(60);
    InitLevel(1); // İlk seviye başlatılıyor

    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();

    }
    UnloadTexture(background);
    UnloadTexture(boxImage);
    UnloadTexture(boxImagePink);
    CloseWindow();

    return 0;
}
