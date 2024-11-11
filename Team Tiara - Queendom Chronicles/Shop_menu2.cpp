#include "Shop_menu2.h"
#include "Engine.h"
#include "GameManager.h"
#include "Shop_menu.h"
#include "Building_list.h"

#include <iostream>
#include <doodle/environment.hpp>

Shop_menu2::Shop_menu2(Engine& game_engine) : Scene(game_engine) ,
	structure(doodle::Width / 6.5, doodle::Height * 0.5 / 4.5, 300, 50, "Building"),
	trade(doodle::Width / 6.5 + doodle::Width / 3.5, doodle::Height * 0.5 / 4.5, 300, 50, "Housing"),
	option(doodle::Width / 6.5 + doodle::Width / 3.5 + doodle::Width / 2.5, doodle::Height * 0.5 / 4.5, 300, 50, "Decoration"),
	escapeKey(InputKey::Keyboard::Escape),
	blue_button(doodle::Width * 1.0 / 24.0, doodle::Height * 1.5 / 5.0, 1320, 120, Building_list::Blue_House),
	green_button(doodle::Width * 1.0 / 24.0, doodle::Height * 2.5 / 5.0, 1320, 120, Building_list::Green_House),
	yellow_button(doodle::Width * 1.0 / 24.0, doodle::Height * 3.5 / 5.0, 1320, 120, Building_list::Yellow_House)
{
}

void Shop_menu2::Update()
{
	if (escapeKey.IsKeyDown())
	{
		engine().Queue_next_scene(GameScenes::GAME_SCREEN);
		engine().Get_Music().play_BGM(BGM_list::background);
	}

	// Building Button
	if (blue_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Building Blue House!\n";

		Engine::Get_game_manager().Set_current_building_type(Building_list::Blue_House);
	}
	if (green_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Building Green House!\n";

		Engine::Get_game_manager().Set_current_building_type(Building_list::Green_House);
	}
	if (yellow_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Building Yellow House!\n";

		Engine::Get_game_manager().Set_current_building_type(Building_list::Yellow_House);
	}

	// Category Button
	if (structure.Did_click_button()) {
		std::cout << "Structure mode!\n";
		engine().Queue_next_scene(GameScenes::SHOP_MENU);
	}
	if (trade.Did_click_button())
	{
		std::cout << "Shop_menu2!\n";
		engine().Queue_next_scene(GameScenes::SHOP_MENU2);
	}
	if (option.Did_click_button())
	{
		std::cout << "Shop_menu3!\n";
		engine().Queue_next_scene(GameScenes::SHOP_MENU3);
	}
}

void Shop_menu2::Draw() const
{
	clear_background(150);
	push_settings();
	no_outline();
	set_fill_color(HexColor{ 0xffd400ff });
	draw_rectangle(doodle::Width * 10.0 / 32.0, doodle::Height * 6.5 / 8.0, 360, 100);
	draw_rectangle(doodle::Width * 1.0 / 32.0, doodle::Height * 0.5 / 8.0, doodle::Width * 30.0 / 32.0, doodle::Height * 6.22 / 8.0);
	set_font_size(20);
	draw_text("~ Press 'ESC' to go back ~", doodle::Width * 18.0 / 24.0, doodle::Height * 4.65 / 5.0);
	pop_settings();

	// Building Button
	blue_button.Draw();
	green_button.Draw();
	yellow_button.Draw();

	// Category Button
	structure.Draw();
	trade.Draw();
	option.Draw();
}
