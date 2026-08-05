#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "raylib.h"

enum class Screen
{
    mainMenu,
    game,
    credits,
    exit
};

struct Button
{
    Rectangle rect;
    const char* text;
    Screen screento;
};

void Game(Screen& screen);

void UpdatePlayer(Rectangle& player, Vector2& speed, float delta, bool& canJump, bool& gameOver);
void PlatformCheck(Rectangle& player, Vector2& speed, float delta, bool& canJump, Rectangle platform[], int platformCount, float& score);