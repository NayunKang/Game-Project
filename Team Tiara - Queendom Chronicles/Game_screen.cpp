#include "Game_screen.h"
#include "Engine.h"
#include "Unit.h"
#include "Npc.h"
#include "Building_list.h"

#include <doodle/environment.hpp>
#include <doodle/input.hpp>
#include <iostream>

using namespace doodle;

Game_screen::Game_screen(Engine& game_engine) : Scene(game_engine),
	shop_button(window_width * 9 / 10.0f, window_height * 9.0 / 10.0f,
	window_width * 1 / 8.0f, window_height * 1 / 15.0f, "Shop Menu"),
	edit_button(window_width * 9 / 10.0f, window_height * 8.0 / 10.0f,
		window_width * 1 / 8.0f, window_height * 1 / 15.0f, "Edit Mode"),
	change_button(window_width * 1 / 10.0f, window_height * 9.0 / 10.0f,
		window_width * 1 / 8.0f, window_height * 1 / 15.0f, "Change Mode"),
	escape_key(InputKey::Keyboard::Escape),
	chat_key(InputKey::Keyboard::Space),
	rotate_key(InputKey::Keyboard::R)
{
}

void Game_screen::Update()
{
	camera.Update();

	// Update mouse
	mouse_x = engine().GetMouseX() + static_cast<int>(camera.Get_position().x);
	mouse_y = engine().GetMouseY() + static_cast<int>(camera.Get_position().y);
	mouse_tile_x = mouse_x / field.x_interval;
	mouse_tile_y = mouse_y / field.y_interval;
	is_clicked = is_mouse_was_pressed && !MouseIsPressed;
	is_mouse_was_pressed = MouseIsPressed;

	// Unit Update
	for (Unit* unit : game_manager.Get_units())
	{
		if (current_game_status != Game_status::CONVERSATION)
		{
			unit->Update();
		}
	}
	
	// Building Update
	for (Building* building : game_manager.Get_buildings())
	{
		building->Update();
	}

	// Update Game_status
	switch (current_game_status)
	{
	case Game_status::INSTALL:

		// Installing building
		if (is_clicked)
		{
			game_manager.Change_mode(Moving_mode::CAMERA);
			Install_building(mouse_tile_x, mouse_tile_y, game_manager.Get_current_building_type());

			// Used all resource
			if (game_manager.Get_resource(Resource_list::WOOD).Get_reserve() < game_manager.Get_current_building_type()->Get_wood_cost() ||
				game_manager.Get_resource(Resource_list::STONE).Get_reserve() < game_manager.Get_current_building_type()->Get_stone_cost())
			{
				game_manager.Set_current_building_type(Building_list::None);
				current_game_status = Game_status::NORMAL;
			}
		}

		if (escape_key.IsKeyDown())
		{
			game_manager.Set_current_building_type(Building_list::None);
			current_game_status = Game_status::NORMAL;
		}

		break;

	case Game_status::EDIT:

		if (is_clicked)
		{
			if (game_manager.Get_current_building_type() == nullptr)
			{
				auto building_iter = game_manager.Get_buildings().begin();
				Building_Type* type = nullptr;
				for (; building_iter != game_manager.Get_buildings().end(); building_iter++)
				{
					if ((*building_iter)->GetArea().Is_intersects({ mouse_x, mouse_y }))
					{
						type = (*building_iter)->Get_type();
						break;
					}
				}

				if (type != nullptr)
				{
					for (int i = 0; i < type->Get_width(); i++)
					{
						for (int j = 0; j < type->Get_height(); j++)
						{
							field.Change_tile((*building_iter)->GetXY().x - (type->Get_width() / 2) + i, (*building_iter)->GetXY().y + j, Tiles::normal);
						}
					}
					game_manager.Set_current_building_type(type);
					game_manager.Get_buildings().erase(building_iter);
				}
			}
			else
			{
				if(Install_building(mouse_tile_x, mouse_tile_y, game_manager.Get_current_building_type()) == true)
					game_manager.Set_current_building_type(Building_list::None);
			}
		}

		// Escape Key
		if (escape_key.IsKeyDown())
		{
			if (game_manager.Get_current_building_type() == nullptr)
				current_game_status = Game_status::NORMAL;
		}
		break;

	case Game_status::CONVERSATION:
	{
		Npc* npc = game_manager.Get_current_npc();
		if (chat_count < npc->Get_chat_count(game_manager.Get_sequence(npc->GetName())))
		{
			if (chat_key.IsKeyReleased())
				chat_count++;

			else if (escape_key.IsKeyDown())
				game_manager.Set_current_npc(nullptr);
		}
		else
		{
			game_manager.Set_current_npc(nullptr);
		}

		// TestForExit
		if (game_manager.Get_current_npc() == nullptr)
		{
			if(game_manager.Get_sequence(npc->GetName()) < npc->Get_max_sequence() - 1)
				game_manager.Increment_sequence(npc->GetName());

			current_game_status = Game_status::NORMAL;
		}
	}
		break;

	case Game_status::NORMAL:

		// Update Buttons (& TestForExit for buttons)
		if (shop_button.Did_click_button())
		{
			std::cout << "Shop_menu!\n";
			engine().Queue_next_scene(GameScenes::SHOP_MENU);

			engine().Get_Music().play_BGM(BGM_list::store);
		}
		else if (edit_button.Did_click_button() )
		{
			std::cout << "Edit_mode!\n";
			current_game_status = Game_status::EDIT; 
			game_manager.Change_mode(Moving_mode::CAMERA);
		}
		else if (change_button.Did_click_button())
		{
			switch (game_manager.Get_mode())
			{
			case Moving_mode::CAMERA: game_manager.Change_mode(Moving_mode::PLAYER);
				break;
			case Moving_mode::PLAYER: game_manager.Change_mode(Moving_mode::CAMERA);
				break;
			}
		}

		// TestForExit
		if (game_manager.Get_current_building_type() != nullptr)
		{
			current_game_status = Game_status::INSTALL;
		}
		if (game_manager.Get_current_npc() != nullptr)
		{
			std::cout << "Conversation mode!\n";
			chat_count = 0;
			current_game_status = Game_status::CONVERSATION;
		}

		break;
	}

}
void Game_screen::Draw() const
{
	// Begin Draw Camera
	camera.beginDraw();

	// Draw field
	field.Draw_field();

	// Draw Building
	for (Building* building : game_manager.Get_buildings())
	{
		if (camera.Get_show_area().Is_intersects(static_cast<math::rect2>(building->GetArea())))
		{
			building->Draw();
		}
	}

	// Draw Units
	for (Unit* unit : game_manager.Get_units())
	{
		unit->Draw();
	}

	// Draw building when install mode
	push_settings();
	switch (current_game_status)
	{
	case Game_status::EDIT:

		set_outline_color(0);
		set_outline_width(1);
		for (int i = 1; i < field.Get_field_width(); i++)
		{
			draw_line(i * x_interval_, 0, i * x_interval_, field.Get_field_size().y * y_interval_);
		}
		for (int j = 1; j < field.Get_field_height(); j++)
		{
			draw_line(0, j * y_interval_, field.Get_field_size().x * x_interval_, j * y_interval_);
		}
		[[fallthrough]];

	case Game_status::INSTALL:

		if (game_manager.Get_current_building_type() != nullptr)
		{
			set_tint_color(HexColor{ 0xFFFFFF80 });		// Make building transparent
			for (int i = 0; i < game_manager.Get_current_building_type()->Get_width(); i++)
			{
				for (int j = 0; j < game_manager.Get_current_building_type()->Get_height(); j++)
				{
					if (&field.Get_tile(mouse_tile_x - (game_manager.Get_current_building_type()->Get_width() / 2) + i, mouse_tile_y + j) != nullptr)
					{
						if (field.Get_tile(
							mouse_tile_x - (game_manager.Get_current_building_type()->Get_width() / 2) + i,
							mouse_tile_y + j).Get_is_movable() == false)
						{
							set_tint_color(Color(255, 0, 0));
						}
					}
				}
			}
			game_manager.Get_current_building_type()->Draw(
				(mouse_tile_x - (game_manager.Get_current_building_type()->Get_width() / 2)) * x_interval_,
				mouse_tile_y * y_interval_);
		}
		
		set_outline_width(1);
		for (int i = 1; i < field.Get_field_width(); i++)
		{
			draw_line(i * x_interval_, 0, i * x_interval_, field.Get_field_size().y * y_interval_);
		}
		for (int j = 1; j < field.Get_field_height(); j++)
		{
			draw_line(0, j * y_interval_, field.Get_field_size().x * x_interval_, j * y_interval_);
		}

		break;

	case Game_status::CONVERSATION:
	{
		Npc* npc = game_manager.Get_current_npc();
		push_settings();
		camera.stopDraw();

		draw_image(Image{ "Assets/blue_interface.png" }, window_width * 1 / 20.0f, window_height * 6 / 10.0f, window_width * 9 / 10.0f, window_height * 1 / 3.0f);
		set_font_size(window_height * 1 / 25.0f);

		if (chat_count < npc->Get_chat_count(game_manager.Get_sequence(npc->GetName())))
			draw_text(npc->Get_message(game_manager.Get_sequence(npc->GetName()), chat_count), 
				window_width * 1 / 8.0f, window_height * 4 / 5.0f);

		camera.beginDraw();
		pop_settings();
	}
		break;

	default:
		
		break;
	}
	pop_settings();

	// Stop Draw Camera
	camera.stopDraw();

	// Draw interface
	if(current_game_status != Game_status::CONVERSATION)
	{
		push_settings();

		// Wood
		set_fill_color(100);
		set_font_size(15);
		draw_image(interface_box, window_width * 1 / 24.0f, window_height * 15 / 16.0f - 5, 
			window_width * 1 / 8.0f, window_height * 1 / 20.0f);
		draw_image(game_manager.Get_resource(Resource_list::WOOD).Get_image(), 
			window_width * 1 / 21.0f, window_height * 47 / 50.0f, 30, 30);
		draw_text(std::to_string(static_cast<int>(game_manager.Get_resource(Resource_list::WOOD).Get_reserve()))
			+ "/" + std::to_string(game_manager.Get_resource(Resource_list::WOOD).Get_max_reserve()),
			window_width * 3 / 40.0f, window_height * 151 / 160.0);

		// Stone
		draw_image(interface_box, window_width * 1 / 24.0f, window_height * 17 / 20.0f,
			window_width * 1 / 8.0f, window_height * 1 / 20.0f);
		draw_image(game_manager.Get_resource(Resource_list::STONE).Get_image(), 
			window_width * 1 / 21.0, window_height * 43 / 50.0f, 30, 30);
		draw_text(std::to_string(static_cast<int>(game_manager.Get_resource(Resource_list::STONE).Get_reserve()))
			+ "/" + std::to_string(game_manager.Get_resource(Resource_list::STONE).Get_max_reserve()),
			window_width * 3 / 40.0, window_height * 137 / 160.0);

		// Food
		draw_image(interface_box, window_width * 1 / 24.0, window_height * 15 / 20.0 + 10,
			window_width * 1 / 8.0f, window_height * 1 / 20.0f);
		draw_image(game_manager.Get_resource(Resource_list::FOOD).Get_image(), 
			window_width * 1 / 21.0, window_height * 38.5 / 50.0, 30, 30);
		draw_text(std::to_string(static_cast<int>(game_manager.Get_resource(Resource_list::FOOD).Get_reserve()))
			+ "/" + std::to_string(game_manager.Get_resource(Resource_list::FOOD).Get_max_reserve()),
			window_width * 3 / 40.0, window_height * 123 / 160.0);

		// Draw Level
		set_fill_color(255);
		set_font_size(35);
		set_outline_width(7);
		draw_image(Image{ "Assets/blue_interface.png" }, window_width * 3 / 10.0f, window_height * 109 / 120.0f,
			window_width * 2 / 5.0f, window_height * 1 / 14.0f);
		draw_text("Level : " + std::to_string(game_manager.Get_level()),
			window_width * 17 / 40.0f, window_height * 145 / 160.0f);
		pop_settings();

		// Draw Buttons
		if (current_game_status == Game_status::NORMAL)
		{
			shop_button.Draw();
			edit_button.Draw();
			change_button.Draw();
		}
	}
}
Game_status Game_screen::Get_game_status() const
{
	return current_game_status;
}
void Game_screen::Set_game_status(Game_status status)
{
	current_game_status = status;
}