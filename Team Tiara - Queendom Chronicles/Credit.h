#pragma once
#include "Engine.h"
#include "Scene.h"

class Credit_screen : public Scene
{
public:
	Credit_screen(Engine& game_engine);
	void Update() override;
	void Draw() const override;


private:
	Game_status current_game_status{};

	InputKey escape_key;
	InputKey chat_key;
	InputKey rotate_key;

	int down_scoll = 70;
	double credit_y = -7500.0;
};