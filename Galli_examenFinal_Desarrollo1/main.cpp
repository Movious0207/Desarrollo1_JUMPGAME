#include <iostream>
#include <ctime>
#include "raylib.h"
#include "game.h"
#include "menu.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Infinite Jumper");
    SetTargetFPS(60);

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

        default:
            isPlaying = false;
            break;
        }
    }

    CloseWindow();

    return 0;
}
