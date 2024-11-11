#include "Main_menu.h"
#include "Engine.h"

#include <doodle/environment.hpp>
#include <doodle/drawing.hpp>
#include <iostream>

Main_menu::Main_menu(Engine& game_engine) : Scene(game_engine),
    play_button(window_width * 17 / 20.0f, window_height * 15.0 / 20.0f,
        window_width * 1 / 5.0f, window_height * 1 / 11.0f, "Play Game"),
    credits_button(window_width * 17 / 20.0f, window_height * 18.0 / 20.0f,
        window_width * 1 / 5.0f, window_height * 1 / 11.0f, " Credits")

{
}

void Main_menu::Update()
{
    if (play_button.Did_click_button())
    {
        std::cout << "Play!\n";
        engine().Queue_next_scene(GameScenes::GAME_SCREEN);

    }
    if (credits_button.Did_click_button())
    {
        std::cout << "Credit!\n";
        engine().Queue_next_scene(GameScenes::CREDITS);
    }
}

void Main_menu::Draw() const
{
    const Image main_menu{ "Assets/main_menu.png" };
    doodle::draw_image(main_menu, 0, 0);
    play_button.Draw();
    credits_button.Draw();
}
