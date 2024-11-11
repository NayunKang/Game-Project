#pragma once

#include "Vec2.h"
#include "Unit.h"
#include "Input.h"
#include "Sprite.h"

#include <doodle/drawing.hpp>

using namespace doodle;

class Player : public Unit
{
public:	
	Player(math::vec2 position_, int width_ = 70, int height_ = 90);
	void Update() override;
	void Draw() override;

private:
	class State {
	public:
		virtual void Enter(Player* player) = 0;
		virtual void Update(Player* player) = 0;
		virtual void TestForExit(Player* player) = 0;
		virtual std::string GetName() = 0;
	};

	class State_Idle : public State
	{
	public:
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player) override;
		virtual void TestForExit(Player* player) override;
		std::string GetName() override { return "Idle"; }
	};

	class State_Moving : public State
	{
	public:
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player) override;
		virtual void TestForExit(Player* player) override;
		std::string GetName() override { return "Running"; }
	};
	State* currState;
	State_Idle stateIdle;
	State_Moving stateMoving;

	void ChangeState(State* newState);

	Sprite sprite;
	InputKey right_key;
	InputKey left_key;
	InputKey up_key;
	InputKey down_key;

	InputKey interaction_key;

	Direction staring_direction;

	math::ivec2 staring_tile_index;

	void Test_NPC_interact();
};