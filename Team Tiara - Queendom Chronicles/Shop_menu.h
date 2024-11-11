#pragma once

#include "Shop_button.h"
#include "Scene.h"
#include "Building.h"
#include "Input.h"

#include <doodle/input.hpp>
#include <doodle/drawing.hpp>

using namespace doodle;

class Shop_menu : public Scene
{
private :   
    Shop_button lumber_camp_button, quarry_button, farm_button;
    Button structure, trade, option;

    InputKey escapeKey;

public:
    Shop_menu(Engine& game_engine);

    void Update() override;
    void Draw() const override;
};
