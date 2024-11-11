#include "Player.h"
#include "Engine.h"
#include "Sprite.h"
#include "Animation.h"
#include "Player_Anims.h"

#include <doodle/drawing.hpp>
// @ After Test_NPC_interact modified, delete this.
#include <iostream>

Player::Player(math::vec2 position_, int width_, int height_)
	: Unit(position_, width_, height_, 200),
	right_key(InputKey::Keyboard::D),
	left_key(InputKey::Keyboard::A),
	up_key(InputKey::Keyboard::W),
	down_key(InputKey::Keyboard::S),
	interaction_key(InputKey::Keyboard::Space),
	staring_direction(Direction::STOP),
	sprite("Assets/Player.spt")
{
	currState = &stateIdle;
	currState->Enter(this);
}

void Player::Update()
{
	currState->Update(this);
	sprite.Update();
	currState->TestForExit(this);

	if (interaction_key.IsKeyReleased())
	{
		if (Engine::Get_game_manager().Get_mode() == Moving_mode::PLAYER)
		{
			Test_NPC_interact();
		}
	}
}
void Player::Draw()
{
	sprite.Draw(math::vec2{position.x, position.y});
}

void Player::ChangeState(State* newState)
{
	currState = newState;
	currState->Enter(this);
}

void Player::Test_NPC_interact()
{
	GameManager& game_manager = Engine::Get_game_manager();
	Field& field = game_manager.Get_field();
	// Get 
	switch (staring_direction)
	{
	case Direction::LEFT:
	{
		// Get departure tile index
		staring_tile_index.x = static_cast<int>(position.x / field.x_interval) - 1;
		staring_tile_index.y = static_cast<int>(position.y / field.y_interval);
	}
	break;

	case Direction::RIGHT:
	{
		staring_tile_index.x = static_cast<int>(position.x / field.x_interval) + 1;
		staring_tile_index.y = static_cast<int>(position.y / field.y_interval);
	}
	break;

	case Direction::UP:
	{
		staring_tile_index.x = static_cast<int>(position.x / field.x_interval);
		staring_tile_index.y = static_cast<int>(position.y / field.y_interval) + 1;
	}
	break;

	case Direction::DOWN:
	{
		staring_tile_index.x = static_cast<int>(position.x / field.x_interval);
		staring_tile_index.y = static_cast<int>(position.y / field.y_interval) - 1;
	}
	break;

	default:
		return;
	}

	// Out of Index
	if (staring_tile_index.x < 0 || staring_tile_index.x >= field.Get_field_index_size().x ||
		staring_tile_index.y < 0 || staring_tile_index.y >= field.Get_field_index_size().y)
	{
		std::cout << "You are looking out of Index" << '\n';
		return;
	}

	if (field.Get_tile(staring_tile_index.x, staring_tile_index.y).Get_is_npc())
	{
		// @ Check npc is that position
		for (Unit* unit : game_manager.Get_units())
		{
			if (unit->Get_tile_index() == staring_tile_index && unit != game_manager.Get_current_npc())
			{
				std::cout << "Current Unit is " + unit->GetName() << '\n';
				game_manager.Set_current_npc(game_manager.Get_unit<Npc>(unit));
			}
		}
	}
	else
	{
		std::cout << "No unit detected" << '\n';
	}
}

void Player::State_Idle::Enter(Player* player)
{
	player->moving_direction = Direction::STOP;
	player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Idle_Anim));
}

void Player::State_Idle::Update(Player*) {}

void Player::State_Idle::TestForExit(Player* player)
{
	if (player->is_moved == true && Engine::Get_game_manager().Get_mode() == Moving_mode::PLAYER) 
	{
		if (player->right_key.IsKeyDown() == true)
		{
			player->moving_direction = Direction::RIGHT;
			player->ChangeState(&player->stateMoving);
		}
		if (player->left_key.IsKeyDown() == true)
		{
			player->moving_direction = Direction::LEFT;
			player->ChangeState(&player->stateMoving);
		}
		if (player->up_key.IsKeyDown() == true)
		{
			player->moving_direction = Direction::UP;
			player->ChangeState(&player->stateMoving);
		}
		if (player->down_key.IsKeyDown() == true)
		{
			player->moving_direction = Direction::DOWN;
			player->ChangeState(&player->stateMoving);
		}
	}
}


void Player::State_Moving::Enter(Player* player)
{
	if (player->moving_direction == Direction::LEFT)
	{
		player->staring_direction = Direction::LEFT;
		player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Left_Anim));
	}
	if (player->moving_direction == Direction::RIGHT)
	{
		player->staring_direction = Direction::RIGHT;
		player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Right_Anim));
	}
	if (player->moving_direction == Direction::UP)
	{
		player->staring_direction = Direction::UP;
		player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Up_Anim));
	}
	if (player->moving_direction == Direction::DOWN)
	{
		player->staring_direction = Direction::DOWN;
		player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Down_Anim));
	}
}

void Player::State_Moving::Update(Player* player)
{
	player->Moving();
}

void Player::State_Moving::TestForExit(Player* player)
{
	if (player->is_moved == true)
	{
		switch (player->moving_direction)
		{
		case Direction::LEFT:
			if (player->left_key.IsKeyDown() == false)
			{
				player->ChangeState(&player->stateIdle);
			}
			break;

		case Direction::RIGHT:
			if (player->right_key.IsKeyDown() == false)
			{
				player->ChangeState(&player->stateIdle);
			}
			break;

		case Direction::UP:
			if (player->up_key.IsKeyDown() == false)
			{
				player->ChangeState(&player->stateIdle);
			}
			break;

		case Direction::DOWN:
			if (player->down_key.IsKeyDown() == false)
			{
				player->ChangeState(&player->stateIdle);
			}
			break;
		}
	}
}

