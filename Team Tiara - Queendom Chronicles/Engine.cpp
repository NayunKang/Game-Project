#include "Engine.h"
#include "Scene.h"
#include "Main_menu.h"
#include "Splash.h"
#include "Credit.h"
#include "Game_screen.h"
#include "Shop_menu.h"
#include "Shop_menu2.h"
#include "Shop_menu3.h"

#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

using namespace std;

void Engine::Setup()
{
	doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);

	// Put Scenes in scenes map
	scenes[GameScenes::SPLASH_SCREEN] = std::make_unique<Splash>(*this);
	scenes[GameScenes::MAIN_MENU] = std::make_unique<Main_menu>(*this);
	scenes[GameScenes::CREDITS] = std::make_unique<Credit_screen>(*this);
	scenes[GameScenes::GAME_SCREEN] = std::make_unique<Game_screen>(*this);
	scenes[GameScenes::SHOP_MENU] = std::make_unique<Shop_menu>(*this);
	scenes[GameScenes::SHOP_MENU2] = std::make_unique<Shop_menu2>(*this);
	scenes[GameScenes::SHOP_MENU3] = std::make_unique<Shop_menu3>(*this);

	currentScene = scenes[GameScenes::SPLASH_SCREEN].get();
	queuedScene = scenes[GameScenes::SPLASH_SCREEN].get();

	game_manager.Setup();

	music.play_BGM(BGM_list::background);
}

void Engine::Update()
{
	update_window();

	if (queuedScene != currentScene)
		currentScene = queuedScene;

	currentScene->Update();

	mouseX = get_mouse_x();
	mouseY = get_mouse_y();

	input.Update();
}

void Engine::Draw() const
{
	doodle::clear_background(Background_color);
	currentScene->Draw();
}

int Engine::GetMouseX() const
{
	return mouseX;
}
int Engine::GetMouseY() const
{
	return mouseY;
}
void Engine::Queue_next_scene(GameScenes scene)
{
	queuedScene = scenes[scene].get();
}
