#include "Credit.h"

Credit_screen::Credit_screen(Engine& game_engine) 
	: Scene(game_engine),
	escape_key(InputKey::Keyboard::Escape),
	chat_key(InputKey::Keyboard::Space),
	rotate_key(InputKey::Keyboard::R)
{
}

void Credit_screen::Update()
{
	credit_y += down_scoll * doodle::DeltaTime * 5;
	if (credit_y >= 0)
	{
		engine().Queue_next_scene(GameScenes::MAIN_MENU);
	}
	if (escape_key.IsKeyDown() == true)
	{
		engine().Queue_next_scene(GameScenes::MAIN_MENU);
	}
}

void Credit_screen::Draw() const
{
	const Image credit{ "Assets/CREDIT.png" };
	doodle::draw_image(credit, 0, credit_y);
}
