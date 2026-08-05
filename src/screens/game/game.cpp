#include "game.h"

static Sound jumpSound;
static Music gameMusic;

void Game(Screen& screen) 
{
    SetExitKey(NULL);

    Texture gameBack = LoadTexture("resources/Background/back.png");
    Texture gameFront = LoadTexture("resources/Background/game.png");

    Texture ButtonTexture = LoadTexture("resources/Buttons/buttons.png");

    Texture PlayerTexture = LoadTexture("resources/Player/player_character.png");

    Texture PlatformTexture = LoadTexture("resources/Platform/platform.png");

    jumpSound = LoadSound("resources/Audio/Jump.mp3");
    gameMusic = LoadMusicStream("resources/Audio/GameMusic.mp3");

    Vector2 backGroundPos = { 0,0 };

    const int screenWidth = 800;
    const int screenHeight = 800;

    Rectangle player = { (float)screenWidth / 2 - 20, (float)screenHeight - 200, 40, 40 };
    Vector2 speed = { 400, 0 };
    
    bool canJump = false;
    float score = 0;
    
    bool gameStart = true;
    bool gameOver = false;
    bool paused = false;

    Button button[2]
    {
        { screenWidth / 2 - screenWidth / 8, screenHeight / 2, screenWidth / 4, 200.0f },
        { screenWidth / 2 - screenWidth / 8, screenHeight / 2 * 1.3, screenWidth / 4, 200.0f }
    };
    button[0].text = "Resume";
    button[1].text = "Main Menu";

    Rectangle platform[5] =
    {
        { (float)screenWidth / 2 - 50, 700.0f, 100.0f, 20.0f },
        { 100.0f, 550.0f, 100.0f, 20.0f },
        { 500.0f, 400.0f, 100.0f, 20.0f },
        { 250.0f, 250.0f, 100.0f, 20.0f },
        { 400.0f, 100.0f, 100.0f, 20.0f }
    };

    for (int i = 1; i < 5; i++)
    {
        platform[i].x = (float)(rand() % (screenWidth - (int)platform[i].width));
    }

    while (screen == Screen::game)
    {
        Vector2 playerPos = { player.x - player.width / 2,player.y - player.height / 2 };
        
        float deltatime = GetFrameTime();
        char drawScore[10];

        sprintf_s(drawScore, "%d", (int)score);
        if (!gameOver)
        {
            if (!gameStart)
            {
                if (IsKeyPressed(KEY_ESCAPE) && !paused)
                {
                    paused = true;
                }
                else if (IsKeyPressed(KEY_ESCAPE))
                {
                    paused = false;
                }
            }
            else
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    gameStart = false;
                }
            }

            if (!paused && !gameStart)
            {
                UpdatePlayer(player, speed, deltatime, canJump, gameOver);
                PlatformCheck(player, speed, deltatime, canJump, platform, 5, score);

                if (!IsMusicStreamPlaying(gameMusic))
                {
                    PlayMusicStream(gameMusic);
                }
                UpdateMusicStream(gameMusic);
            }
            else if (paused)
            {
                if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
                {
                    if (CheckCollisionPointRec(GetMousePosition(), button[0].rect))
                    {
                        paused = false;
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), button[1].rect))
                    {
                        screen = button[1].screento;
                    }
                }
            }

            BeginDrawing();

            DrawTextureEx(gameBack, backGroundPos, 0, 10, WHITE);
            DrawTextureEx(gameFront, backGroundPos, 0, 3, WHITE);

            for (int i = 0; i < 5; i++)
            {
                Vector2 platPos = { platform[i].x,platform[i].y };
                DrawTextureEx(PlatformTexture, platPos, 0, 1, WHITE);
            }

            DrawTextureEx(PlayerTexture, playerPos, 0, 1, WHITE);

            DrawText("Score:", screenWidth / 4 * 3, 40, 40, WHITE);
            DrawText(drawScore, screenWidth / 4 * 3 + 150, 40, 40, WHITE);

            if (paused)
            {
                DrawText("PAUSE", screenWidth / 2 - 80, 40, 40, WHITE);

                ClearBackground(GRAY);
                for (int i = 0; i < 2; i++)
                {
                    Vector2 position{ button[i].rect.x,button[i].rect.y };
                    DrawTextureEx(ButtonTexture, position, 0, 3, WHITE);
                    DrawText(button[i].text, button[i].rect.x + 20, button[i].rect.y + 20, 20, BLACK);
                }
            }
            if (gameStart)
            {
                ClearBackground(DARKGRAY);

                DrawText("Use A and D to move", screenWidth / 4, screenHeight / 4, 40, WHITE);
                DrawText("Get as high as possible!", screenWidth / 4 - 50, screenHeight / 3, 40, WHITE);
                DrawText("press SPACE to begin", screenWidth / 4 - 30, screenHeight / 2, 40, WHITE);
            }

            EndDrawing();
        }
        else
        {
            button[0].text = "Reset";

            if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionPointRec(GetMousePosition(), button[0].rect))
                {
                    player = { (float)screenWidth / 2 - 20, (float)screenHeight - 200, 40, 40 };

                    canJump = false;
                    score = 0;

                    gameStart = true;
                    gameOver = false;
                    paused = false;

                    platform[0] = { (float)screenWidth / 2 - 50, 700.0f, 100.0f, 20.0f };
                    platform[1] = { 100.0f, 550.0f, 100.0f, 20.0f };
                    platform[2] = { 500.0f, 400.0f, 100.0f, 20.0f };
                    platform[3] = { 250.0f, 250.0f, 100.0f, 20.0f };
                    platform[4] = { 400.0f, 100.0f, 100.0f, 20.0f };

                    button[0].text = "Resume";
                }
                if (CheckCollisionPointRec(GetMousePosition(), button[1].rect))
                {
                    screen = button[1].screento;
                }
            }

            BeginDrawing();

            for (int i = 0; i < 5; i++)
            {
                Vector2 platPos = { platform[i].x,platform[i].y };
                DrawTextureEx(PlatformTexture, platPos, 0, 1, WHITE);
            }

            DrawTextureEx(PlayerTexture, playerPos,0,1, WHITE);

            DrawTextureEx(gameBack, backGroundPos, 0, 10, WHITE);
            DrawTextureEx(gameFront, backGroundPos, 0, 3, WHITE);

            DrawText("GAME OVER", screenWidth / 4 + 80, screenHeight / 4, 60, WHITE);
            DrawText("Final Score:", screenWidth / 4 + 80, screenHeight / 3, 40, WHITE);
            DrawText(drawScore, screenWidth / 2 + 130, screenHeight / 3, 40, WHITE);

            for (int i = 0; i < 2; i++)
            {
                Vector2 position{ button[i].rect.x,button[i].rect.y };
                DrawTextureEx(ButtonTexture, position, 0, 3, WHITE);
                DrawText(button[i].text, button[i].rect.x + 20, button[i].rect.y + 20, 20, BLACK);
            }

            EndDrawing();
        }

        if (WindowShouldClose())
        {
            screen = Screen::exit;
        }
    }

    UnloadTexture(gameBack);
    UnloadTexture(gameFront);
    UnloadTexture(ButtonTexture);
    UnloadTexture(PlayerTexture);
    UnloadTexture(PlatformTexture);
}

void UpdatePlayer(Rectangle& player, Vector2& speed, float delta, bool& canJump, bool& gameOver)
{
    speed.y += 800.0f * delta;
    player.y += speed.y * delta;

    if (IsKeyDown(KEY_A)) player.x -= speed.x * delta;
    if (IsKeyDown(KEY_D)) player.x += speed.x * delta;

    if (player.x > GetScreenWidth())
    {
        player.x = 0 - player.width;
    }
    else if (player.x < 0 - player.width)
    {
        player.x = GetScreenWidth();
    }

    if (canJump)
    {
        speed.y = -600.0f;
        canJump = false;
        PlaySound(jumpSound);
    }

    if (player.y > GetScreenHeight())
    {
        gameOver = true;
    }
}

void PlatformCheck(Rectangle& player, Vector2& speed, float delta, bool& canJump, Rectangle platform[], int platformCount, float& score)
{
    float cameraThreshold = GetScreenHeight() / 2.0f;

    if (player.y < cameraThreshold && speed.y < 0)
    {
        float diff = cameraThreshold - player.y;

        player.y = cameraThreshold;

        for (int i = 0; i < platformCount; i++)
        {
            platform[i].y += diff;

            if (platform[i].y > GetScreenHeight())
            {
                platform[i].y = 0;
                platform[i].x = (float)(rand() % (GetScreenWidth() - (int)platform[i].width));

                score++;
            }
        }
    }

    if (speed.y > 0)
    {
        for (int i = 0; i < platformCount; i++)
        {
            if (CheckCollisionRecs(player, platform[i]))
            {
                if ((player.y + player.height) <= (platform[i].y + 15.0f))
                {
                    player.y = platform[i].y - player.height;
                    canJump = true;
                }
            }
        }
    }
}