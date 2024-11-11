/*--------------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Project: CS230
Author: Minsu Kim
Creation date: 3/14/2022
-----------------------------------------------------------------*/

#include "Input.h"
#include "Engine.h"


InputKey::InputKey(InputKey::Keyboard button) : button(button)
{
}

bool InputKey::IsKeyDown() const
{
	return Engine::Get_Input().IsKeyDown(button);
}

bool InputKey::IsKeyReleased() const
{
	return Engine::Get_Input().IsKeyReleased(button);
}

/////////////// Input ///////////////

Input::Input()
{
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
}

void Input::Update()
{
	wasKeyDown = keyDown;
}

bool Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyReleased(InputKey::Keyboard key) const
{
	return ((wasKeyDown[static_cast<int>(key)] == true) 
		&& ((keyDown[static_cast<int>(key)]) == false));
}

void Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}