#pragma once

#include "Button.h"
#include "Scene.h"

class Main_menu : public Scene
{
private:
    Button play_button;
    Button credits_button;

public:
    Main_menu(Engine& game_engine);

    void Update() override;
    void Draw() const override;
};
