#pragma once

#include "Rect.h"
#include "Input.h"

#include <doodle/environment.hpp>

using namespace doodle;

class Camera
{
private:
	math::vec2 position;
	math::ivec2 movable_max_position;
	math::rect2 show_area;

	InputKey moveLeftKey;
	InputKey moveRightKey;
	InputKey moveUpKey;
	InputKey moveDownKey;

public:
	//Camera();
	Camera(math::vec2 position_, math::ivec2 movable_max_position_);

	const math::vec2& Get_position() const { return position; }
	const math::ivec2& Get_movable_max_position() const { return movable_max_position; }
	const math::rect2& Get_show_area() const { return show_area; }

	void Set_movable_max_position(math::ivec2 new_max_position);

	void Update();
	void beginDraw();
	void stopDraw();
};