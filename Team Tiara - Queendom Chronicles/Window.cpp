#include "Window.h"
#include "Engine.h"

void on_window_resized(int new_width, int new_height)
{
    window_width = new_width;
    window_height = new_height;

    Engine::Get_game_manager().Get_field().Resize();
}

