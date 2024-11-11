
#include "Shop_menu.h"
#include "Engine.h"
#include "GameManager.h"
#include "Game_status.h"
#include "Building_list.h"
#include "Window.h"

#include <iostream>
#include <doodle/environment.hpp>

Shop_menu::Shop_menu(Engine& game_engine) : Scene(game_engine),
	structure(doodle::Width / 6.5, doodle::Height * 0.5 / 4.5, 300, 50, "Building"),
	trade(doodle::Width / 6.5 + doodle::Width / 3.5, doodle::Height * 0.5 / 4.5, 300, 50, "Housing"),
	option(doodle::Width / 6.5 + doodle::Width / 3.5 + doodle::Width / 2.5, doodle::Height * 0.5 / 4.5, 300, 50, "Decoration"),
	escapeKey(InputKey::Keyboard::Escape),
	lumber_camp_button(window_width * 1.0 / 24.0, window_height * 1.5 / 5.0, 1320, 120, Building_list::Lumber_Camp),
	quarry_button(window_width * 1.0 / 24.0, window_height * 2.5 / 5.0, 1320, 120, Building_list::Quarry),
	farm_button(window_width * 1.0 / 24.0, window_height * 3.5 / 5.0, 1320, 120, Building_list::Farm)
{
}

void Shop_menu::Update()
{	
	if (escapeKey.IsKeyDown())
	{
		engine().Queue_next_scene(GameScenes::GAME_SCREEN);
		engine().Get_Music().play_BGM(BGM_list::background);
	}


	// Building button
	if (lumber_camp_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Building Lumber Camp!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Lumber_Camp);
	}
	if (quarry_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Building Quarry!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Quarry);
	}
	if (farm_button.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\nBuilding Farm!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Farm);
	}

	// Category button
	if (structure.Did_click_button())
	{
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

void Shop_menu::Draw() const
{
	clear_background(150);
	push_settings();
	no_outline();
	set_fill_color(HexColor{ 0xffc0cbff });
	draw_rectangle(doodle::Width * 1.0 / 32.0, doodle::Height * 6.5 / 8.0,360,100);
	draw_rectangle(doodle::Width * 1.0 / 32.0, doodle::Height * 0.5 / 8.0, doodle::Width * 30.0/32.0, doodle::Height*6.22/8.0);
	set_font_size(20);
	draw_text("~ Press 'ESC' to go back ~", doodle::Width * 18.0 / 24.0, doodle::Height * 4.65 / 5.0);
	pop_settings();
	
	// Building Button
	lumber_camp_button.Draw();
	quarry_button.Draw();
	farm_button.Draw();
	
	// Category Button
	structure.Draw();
	trade.Draw();
	option.Draw();
}