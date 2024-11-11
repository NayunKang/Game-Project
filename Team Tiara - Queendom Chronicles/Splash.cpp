#include "Splash.h"
#include "Engine.h"

#include <doodle/environment.hpp>
#include <doodle/drawing.hpp>
#include <iostream>

Splash::Splash(Engine& game_engine) : Scene(game_engine)
{ }

void Splash::Draw() const
{
	doodle::clear_background(0x000000FF);
	const Image splash{"Assets/DigiPen_BLACK_1024px.png" };
	doodle::draw_image(splash, doodle::Width / 8, doodle::Height / 4);
}
void Splash::Update(){
	time += doodle::DeltaTime;
		if (time >= 3) {
			engine().Queue_next_scene(GameScenes::MAIN_MENU);
		}
}

void Splash::Unload() {}

