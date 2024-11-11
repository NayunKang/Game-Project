#pragma once

#include "Engine.h"
#include "Button.h"
#include "Scene.h"
#include "Unit.h"
#include "Camera.h" 
#include "Game_status.h"

#include <doodle/drawing.hpp>

class Game_screen : public Scene
{
public:
	Game_screen(Engine& game_engine);
	void Update() override;
	void Draw() const override;

	Game_status Get_game_status() const;
	void Set_game_status(Game_status status);

private:
	const doodle::Image interface_box{ "Assets/grey_interface.png" };
	Button shop_button;
	Button edit_button;
	Button change_button;

	bool is_mouse_was_pressed{ false };
	bool is_clicked{ false };

	GameManager& game_manager = Engine::Get_game_manager();
	Field& field = Engine::Get_game_manager().Get_field();
	Camera& camera = field.Get_camera();
	Game_status current_game_status{};

	int mouse_x{ 0 };
	int mouse_y{ 0 };
	int mouse_tile_x{ 0 };
	int mouse_tile_y{ 0 };

	int& x_interval_ = Engine::Get_game_manager().Get_field().x_interval;
	int& y_interval_ = Engine::Get_game_manager().Get_field().y_interval;

	InputKey escape_key;
	InputKey chat_key;
	InputKey rotate_key;

	int chat_count{ 0 };
};
