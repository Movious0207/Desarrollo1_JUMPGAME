#include "credits.h"

void Credits(Screen& screen)
{
	const int screenWidth = 800;
	const int screenHeight = 800;

	Texture menuBack = LoadTexture("resources/Background/back.png");
	Texture menuFront = LoadTexture("resources/Background/menu.png");

	Texture ButtonTexture = LoadTexture("resources/Buttons/buttons.png");

	Button button;
	button.rect = { screenWidth / 4 * 1.5, screenHeight / 8 * 7, screenWidth / 4, 200.0f };
	button.screento = Screen::mainMenu;
	button.text = "Main Menu";

	Vector2 backgroundPos = { 0, 0 };

	while (screen == Screen::credits)
	{

		if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionPointRec(GetMousePosition(), button.rect))
			{
				screen = button.screento;
			}
		}

		BeginDrawing();
		DrawTextureEx(menuBack, backgroundPos, 0, 3, WHITE);
		DrawTextureEx(menuFront, backgroundPos, 0, 3, WHITE);

		DrawText("Credits", screenWidth / 2 - 100, 120, 40, WHITE);


		Vector2 position{ button.rect.x,button.rect.y };
		DrawTextureEx(ButtonTexture, position, 0, 3, WHITE);
		DrawText(button.text, button.rect.x + 20, button.rect.y + 20, 20, BLACK);

		EndDrawing();

		if (WindowShouldClose())
		{
			screen = Screen::exit;
		}
	}
	UnloadTexture(menuBack);
	UnloadTexture(menuFront);
	UnloadTexture(ButtonTexture);
}