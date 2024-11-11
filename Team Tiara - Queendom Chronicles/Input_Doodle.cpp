#include <doodle/input.hpp>	
#include "Input.h"
#include "Engine.h"

InputKey::Keyboard DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return InputKey::Keyboard::Enter;
	}
	else if (button == doodle::KeyboardButtons::Escape) {
		return InputKey::Keyboard::Escape;
	}
	else if (button == doodle::KeyboardButtons::Space) {
		return InputKey::Keyboard::Space;
	}
	else if (button == doodle::KeyboardButtons::Left) {
		return InputKey::Keyboard::Left;
	}
	else if (button == doodle::KeyboardButtons::Right) {
		return InputKey::Keyboard::Right;
	}
	else if (button == doodle::KeyboardButtons::Up) {
		return InputKey::Keyboard::Up;
	}
	else if (button == doodle::KeyboardButtons::Down) {
		return InputKey::Keyboard::Down;
	}
	else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != InputKey::Keyboard::None) {
		Engine::Get_Input().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) {
	InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != InputKey::Keyboard::None) {
		Engine::Get_Input().SetKeyDown(button, false);
	}
}

///////////////////////////////////////////////////////////////////////////

// Mouse
void on_mouse_pressed([[maybe_unused]] MouseButtons button)
{

}

void on_mouse_released([[maybe_unused]] MouseButtons button)
{

}