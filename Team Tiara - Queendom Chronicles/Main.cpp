#include "Window.h"
#include "Field.h"
#include "Engine.h"

#include <stdexcept>
#include <Windows.h>
#include <iostream>
#include <doodle/doodle.hpp>

using namespace doodle;

int main(void)
{
	try {
#if _DEBUG
#else
		HWND hWndConsole = GetConsoleWindow();
		ShowWindow(hWndConsole, SW_HIDE);
#endif

		create_window("Queendom Chronicles", window_width, window_height);
		set_image_mode(RectMode::Corner);

		Engine& engine = Engine::Instance();
		engine.Setup();

		while (!is_window_closed())
		{
			engine.Update();
			engine.Draw();
		}
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		return -1;
	}
}