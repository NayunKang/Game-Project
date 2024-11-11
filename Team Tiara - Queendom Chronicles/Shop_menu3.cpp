#include "Shop_menu3.h"
#include "Engine.h"
#include "GameManager.h"
#include "Game_screen.h"
#include "Building_list.h"

#include <iostream>
#include <doodle/environment.hpp>

Shop_menu3::Shop_menu3(Engine& game_engine) : Scene(game_engine),
structure(doodle::Width / 6.5, doodle::Height * 0.5 / 4.5, 300, 50, "Building"),
trade(doodle::Width / 6.5 + doodle::Width / 3.5, doodle::Height * 0.5 / 4.5, 300, 50, "Housing"),
option(doodle::Width / 6.5 + doodle::Width / 3.5 + doodle::Width / 2.5, doodle::Height * 0.5 / 4.5, 300, 50, "Decoration"),
tree_1(doodle::Width * 1.0 / 24.0, doodle::Height * 1.5 / 5.0, 400, 120, Building_list::Tree1),
tree_2(doodle::Width * 8.5 / 24.0, doodle::Height * 1.5 / 5.0, 400, 120, Building_list::Tree2),
tree_3(doodle::Width * 16.0 / 24.0, doodle::Height * 1.5 / 5.0, 400, 120, Building_list::Tree3),
tree_4(doodle::Width * 1.0 / 24.0, doodle::Height * 2.5 / 5.0, 400, 120, Building_list::Tree4),
tree_5(doodle::Width * 8.5 / 24.0, doodle::Height * 2.5 / 5.0, 400, 120, Building_list::Tree5),
tree_6(doodle::Width * 16.0 / 24.0, doodle::Height * 2.5 / 5.0, 400, 120, Building_list::Tree6),
tree_7(doodle::Width * 1.0 / 24.0, doodle::Height * 3.5 / 5.0, 400, 120, Building_list::Tree7),
fence_1(doodle::Width * 8.5 / 24.0, doodle::Height * 3.5 / 5.0, 400, 120, Building_list::Fence1),
	//fountain_1(doodle::Width * 16.0 / 24.0, doodle::Height * 3.5 / 5.0, 400, 120, ""),
fence_2(doodle::Width * 16.0 / 24.0, doodle::Height * 3.5 / 5.0, 400, 120, Building_list::Fence2),
escapeKey(InputKey::Keyboard::Escape)
{
}

void Shop_menu3::Update()
{
	if (escapeKey.IsKeyDown())
	{
		engine().Queue_next_scene(GameScenes::GAME_SCREEN);
		engine().Get_Music().play_BGM(BGM_list::background);
	}

	if (structure.Did_click_button()) {
		Engine::Instance().Queue_next_scene(GameScenes::SHOP_MENU);
		std::cout << "Structure mode!\n";
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
	if (tree_1.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\n tree 1!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree1);
	}
	if (tree_2.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\n tree 2!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree2);
	}
	if (tree_3.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\n tree 3!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree3);
	}
	if (tree_4.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\n tree 4!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree4);
	}
	if (tree_5.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\ntree 5!\n";

		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree5);
	}
	if (tree_6.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\n tree 6!\n";


		// Change after fixed (After add various buildings)
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree6);
	}
	if (tree_7.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\ntree 7!\n";
		Engine::Get_game_manager().Set_current_building_type(Building_list::Tree7);
	}
	if (fence_1.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\nfence 1!\n";

		Engine::Get_game_manager().Set_current_building_type(Building_list::Fence1);
	}
	//if (fountain_1.Did_click_button())
	//{
	//	Engine::Instance().Queue_next_scene(GameScenes::MODE_1);
	//	std::cout << "Mode_1!\n fountain 1!\n";

	//	// Change after fixed (After add various buildings)
	//	Engine::Get_game_manager().Set_current_building_type(15);
	//}
	if (fence_2.Did_click_button())
	{
		Engine::Instance().Queue_next_scene(GameScenes::GAME_SCREEN);
		std::cout << "Mode_1!\nfence 2!\n";

		Engine::Get_game_manager().Set_current_building_type(Building_list::Fence2);
	}
}

void Shop_menu3::Draw() const
{
	clear_background(150);
	push_settings();
	no_outline();
	set_fill_color(HexColor{ 0x50bcdfff });
	draw_rectangle(doodle::Width * 22.0 / 32.0, doodle::Height * 6.5 / 8.0, 405, 100);
	draw_rectangle(doodle::Width * 1.0 / 32.0, doodle::Height * 0.5 / 8.0, doodle::Width * 30.0 / 32.0, doodle::Height * 6.22 / 8.0);
	set_font_size(20);
	draw_text("~ Press 'ESC' to go back ~", doodle::Width * 18.0 / 24.0, doodle::Height * 4.65 / 5.0);
	pop_settings();

	structure.Draw();
	trade.Draw();
	option.Draw();
	tree_1.deco_draw();
	tree_2.deco_draw();
	tree_3.deco_draw();
	tree_4.deco_draw();
	tree_5.deco_draw();
	tree_6.deco_draw();
	tree_7.deco_draw();
	fence_1.deco_draw();
	fence_2.deco_draw();
}
