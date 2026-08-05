#include "menu.h"

void ButtonUpdate(Button button, Screen& screen);

void Menu(Screen& screen)
{
	SetExitKey(KEY_ESCAPE);

	float middleX = GetScreenWidth() / 2;
	float middleY = GetScreenHeight() / 2;

	Button buttons[3] =
	{
		{ middleX - middleX / 4, middleY, middleX / 2, 50.0f},
		{ middleX - middleX / 4, middleY * 1.2, middleX / 2, 50.0f },
		{ middleX - middleX / 4, middleY * 1.4, middleX / 2, 50.0f }
	};
	buttons[0].screento = Screen::game;
	buttons[1].screento = Screen::credits;
	buttons[2].screento = Screen::exit;

	buttons[0].text = "Play";
	buttons[1].text = "Credits";
	buttons[2].text = "Quit";

	while (screen == Screen::mainMenu)
	{
		for (int i = 0; i < 3; i++)
		{
			ButtonUpdate(buttons[i], screen);
		}

		BeginDrawing();

		ClearBackground(LIGHTGRAY);

		DrawText("JUMP GAME", middleX - 100, 120, 40, WHITE);
		
		for (int i = 0; i < 3; i++)
		{
			DrawRectangleRec(buttons[i].rect, GRAY);
			DrawText(buttons[i].text, buttons[i].rect.x + 20, buttons[i].rect.y + 20, 20, BLACK);
		}

		EndDrawing();

		if (WindowShouldClose())
		{
			screen = Screen::exit;
		}
	}
}

void ButtonUpdate(Button button, Screen& screen)
{
	if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(GetMousePosition(), button.rect))
		{
			screen = button.screento;
		}
	}
}