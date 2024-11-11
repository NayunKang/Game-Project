
#include "Engine.h"
#include "Window.h"
#include "Camera.h"

using namespace doodle;

Camera::Camera(math::vec2 position_, math::ivec2 movable_max_position_)
	: position(position_), movable_max_position(movable_max_position_),
	show_area(math::rect2{ position, 
		{ position_.x + window_width, position_.y + window_height } }),
	moveLeftKey(InputKey::Keyboard::A), moveRightKey(InputKey::Keyboard::D),
	moveUpKey(InputKey::Keyboard::W), moveDownKey(InputKey::Keyboard::S)
{}

void Camera::Set_movable_max_position(math::ivec2 new_max_position)
{
	movable_max_position = new_max_position;
}

void Camera::Update()
{
	if (Engine::Get_game_manager().Get_mode() == Moving_mode::CAMERA)
	{
		// Camera Moving
		if (moveLeftKey.IsKeyDown())
			position.x -= 1000 * doodle::DeltaTime;
		if (moveRightKey.IsKeyDown())
			position.x += 1000 * doodle::DeltaTime;
		if (moveUpKey.IsKeyDown())
			position.y += 1000 * doodle::DeltaTime;
		if (moveDownKey.IsKeyDown())
			position.y -= 1000 * doodle::DeltaTime;
	}

	// Camera movable boundary check
	if (position.x > movable_max_position.x)
		position.x = movable_max_position.x;
	if (position.y > movable_max_position.y)
		position.y = movable_max_position.y;
	if (position.x < 0)
		position.x = 0;
	if (position.y < 0)
		position.y = 0;

	show_area.bottomLeft = position;
	show_area.topRight = { position.x + window_width, position.y + window_height };
}

void Camera::beginDraw()
{
	doodle::apply_translate(-position.x, -position.y);
}

void Camera::stopDraw()
{
	doodle::apply_translate(position.x, position.y);
}
