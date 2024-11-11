#pragma once

#include "Vec2.h"
#include "Sprite.h"


#include <doodle/drawing.hpp>
#include <doodle/input.hpp>

using namespace doodle;

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
};

class Unit
{
protected:
	//Image image;
	math::vec2 position;
	int width;
	int height;
	int speed;

	std::string name;

	math::ivec2 tile_index;

	Direction moving_direction;
	bool is_moved;

public:
	Sprite Npc1;

	Unit(math::vec2 position_, int width_ = 50, int height_ = 50, int speed_ = 100);

	void SetName(std::string name_) { name = name_; }
	std::string GetName() const { return name; }

	virtual void Update();
	virtual void Draw();

	void Moving();

	math::ivec2 Get_tile_index();
};