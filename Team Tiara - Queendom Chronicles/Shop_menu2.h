#pragma once

#include "Button.h"
#include "Scene.h"
#include "Building.h"
#include "Input.h"
#include "Shop_button.h"

#include <doodle/input.hpp>
#include <doodle/drawing.hpp>

using namespace doodle;

class Shop_menu2 : public Scene
{
private:
	Shop_button blue_button, green_button, yellow_button;
	Button structure, trade, option;
	InputKey escapeKey;

public:
	Shop_menu2(Engine& game_engine);
	void Update() override;
	void Draw() const override;
};