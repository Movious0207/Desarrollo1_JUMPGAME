#include <iostream>
#include <ctime>
#include "raylib.h"
#include "screens/game/game.h"
#include "screens/menu/menu.h"
#include "screens/credits/credits.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Infinite Jumper");
    SetTargetFPS(60);
    InitAudioDevice();
    srand(time(NULL));

    bool isPlaying = true;

    Screen actualScreen = Screen::mainMenu;

    while (isPlaying)
    {

        switch (actualScreen)
        {
        case Screen::mainMenu:
            Menu(actualScreen);
            break;

        case Screen::game:
            Game(actualScreen);
            break;
        case Screen::credits:
            Credits(actualScreen);
            break;
        default:
            isPlaying = false;
            break;
        }
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
