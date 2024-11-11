#include "Engine.h"
#include "Unit.h"
#include "Sprite.h"
#include "Npc_Anims.h"

#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <doodle/random.hpp>

Unit::Unit(math::vec2 position_, int width_, int height_, int speed_)
	: position(position_), width(width_), height(height_), speed(speed_),
	moving_direction(Direction::STOP), is_moved(true), Npc1("Assets/Npc_blue.spt")
{
	tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
	tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);
	Npc1.PlayAnimation(static_cast<int>(Npc_Anim::state_Idle));

	Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::npc);
}

void Unit::Update()
{
	if (is_moved == true)
	{
		moving_direction = static_cast<Direction>(
			random(static_cast<int>(Direction::LEFT), static_cast<int>(Direction::STOP)));
	}

	Moving();
}

void Unit::Draw()
{
	push_settings();

	set_image_mode(RectMode::Center);
	Npc1.Draw(math::vec2{ position.x, position.y });
	//draw_image(position.x, position.y, width, height);

	pop_settings();
}

void Unit::Moving()
{
	// Commented to only LEFT, others have all same algorithm.
	switch (moving_direction)
	{
	case Direction::LEFT:
	{
		if (is_moved == true)
		{
			Npc1.PlayAnimation(static_cast<int>(Npc_Anim::state_Left));
			// Get departure tile index
			tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
			tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);

			// Check destination index is valid
			if (tile_index.x - 1 < 0)
				break;

			// Check Get_is_movable is false
			if (Engine::Get_game_manager().Get_field().Get_tile(tile_index.x - 1, tile_index.y).Get_is_movable() == false)
				break;

			// Change departure and destination is_movable to false
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::npc);
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x - 1, tile_index.y, Tiles::npc);

			is_moved = false;
		}



		if (position.x >= Engine::Get_game_manager().Get_field().Get_tile_position(tile_index.x - 1, tile_index.y).x)
		{
			// Change position
			position.x -= speed * doodle::DeltaTime;
		}
		else
		{
			// Change departure is_movable to true
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::normal);

			is_moved = true;
		}
	}
	break;

	case Direction::RIGHT:
	{
		if (is_moved == true)
		{
			Npc1.PlayAnimation(static_cast<int>(Npc_Anim::state_Right));
			tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
			tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);

			if (tile_index.x + 1 >= Engine::Get_game_manager().Get_field().Get_field_index_size().x)
				break;

			if (Engine::Get_game_manager().Get_field().Get_tile(tile_index.x + 1, tile_index.y).Get_is_movable() == false)
				break;


			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x + 1, tile_index.y, Tiles::npc);
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::npc);

			is_moved = false;
		}



		if (position.x <= Engine::Get_game_manager().Get_field().Get_tile_position(tile_index.x + 1, tile_index.y).x)
		{
			position.x += speed * doodle::DeltaTime;
		}
		else
		{
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::normal);

			is_moved = true;
		}
	}
	break;

	case Direction::UP:
	{
		if (is_moved == true)
		{
			Npc1.PlayAnimation(static_cast<int>(Npc_Anim::state_Up));
			tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
			tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);

			if (tile_index.y + 1 >= Engine::Get_game_manager().Get_field().Get_field_index_size().y)
				break;

			if (Engine::Get_game_manager().Get_field().Get_tile(tile_index.x, tile_index.y + 1).Get_is_movable() == false)
				break;

			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y + 1, Tiles::npc);
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::npc);

			is_moved = false;
		}



		if (position.y <= Engine::Get_game_manager().Get_field().Get_tile_position(tile_index.x, tile_index.y + 1).y)
		{
			position.y += speed * doodle::DeltaTime;
		}
		else
		{
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::normal);

			is_moved = true;
		}
	}
	break;

	case Direction::DOWN:
	{
		if (is_moved == true)
		{
			Npc1.PlayAnimation(static_cast<int>(Npc_Anim::state_Down));
			tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
			tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);

			if (tile_index.y - 1 < 0)
				break;

			if (Engine::Get_game_manager().Get_field().Get_tile(tile_index.x, tile_index.y - 1).Get_is_movable() == false)
				break;

			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y - 1, Tiles::npc);
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::npc);

			is_moved = false;
		}



		if (position.y >= Engine::Get_game_manager().Get_field().Get_tile_position(tile_index.x, tile_index.y - 1).y)
		{
			position.y -= speed * doodle::DeltaTime;
		}
		else
		{
			Engine::Get_game_manager().Get_field().Change_tile(tile_index.x, tile_index.y, Tiles::normal);

			is_moved = true;
		}
	}
	break;

	case Direction::STOP:
		// Stop Moving
		break;
	}
}

math::ivec2 Unit::Get_tile_index()
{
	tile_index.x = static_cast<int>(position.x / Engine::Get_game_manager().Get_field().x_interval);
	tile_index.y = static_cast<int>(position.y / Engine::Get_game_manager().Get_field().y_interval);

	return tile_index;
}