#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Field.h"
#include "Input.h"
#include "GameScenes.h"
#include "TextureManager.h"
#include "Music.h"

#include <map>
#include <memory>
#include <doodle/color.hpp>
#include <doodle/input.hpp>

class Engine
{
private:
	Scene* currentScene{ nullptr };
	Scene* queuedScene{ nullptr };
	std::map<GameScenes, std::unique_ptr<Scene>> scenes{};

    GameManager game_manager;
    TextureManager textureManager;
    Input input;
	Music music;

	int mouseX{ 0 };
	int mouseY{ 0 };

public:
	Engine() = default;

    static Engine& Instance() { static Engine instance; return instance; }
    static GameManager& Get_game_manager() { return Instance().game_manager; }
    static Input& Get_Input() { return Instance().input; }
    static TextureManager& GetTextureManager() { return Instance().textureManager; }
	static Music& Get_Music() { return Instance().music; }

	void          Setup();
	void          Update();
	void          Draw() const;
	int           GetMouseX() const;
	int           GetMouseY() const;
	doodle::HexColor Background_color{ 0x38C0FFFF };
	void          Queue_next_scene(GameScenes scene);
};