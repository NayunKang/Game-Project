#pragma once

#include "Shop_button.h"
#include "Button.h"
#include "Scene.h"
#include "Building.h"
#include "Input.h"

#include <doodle/input.hpp>
#include <doodle/drawing.hpp>

using namespace doodle;


class Shop_menu3 : public Scene
{
private:
	Shop_button tree_1, tree_2, tree_3, tree_4, tree_5, tree_6, tree_7, fence_1, fence_2;
	Button structure, trade, option;
	//const doodle::Image tree1{ "Assets/tree1.png" };
	//const doodle::Image tree2{ "Assets/tree2.png" };
	//const doodle::Image tree3{ "Assets/tree3.png" };
	//const doodle::Image tree4{ "Assets/tree4.png" };
	//const doodle::Image tree5{ "Assets/tree5.png" };
	//const doodle::Image tree6{ "Assets/tree6.png" };
	//const doodle::Image tree7{ "Assets/tree7.png" };
	//const doodle::Image wood{ "Assets/Wood.png" };
	//const doodle::Image stone{ "Assets/stone1.png" };
	//const doodle::Image fence{ "Assets/fence.png" };
	//const doodle::Image fence2{ "Assets/fence_rightBottom.png" };
	InputKey escapeKey;
public:
	Shop_menu3(Engine& game_engine);

	void Update() override;
	void Draw() const override;
};