#pragma once

#include "Scene.h"

class Splash : public Scene {
public:
	Splash(Engine& game_engine);

	void Draw() const override;
	void Update() override;
	void Update(double dt)  ;
	void Unload();

private:
	double time = 0;
};