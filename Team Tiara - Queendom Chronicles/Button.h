#pragma once

#include <string>
#include "Building.h"
#include "Resource.h"

class Button
{
protected: 
    double left{ 0 };
    double top{ 0 };
    double width;
    double height;
    std::string label{ "" };
    bool mouseIsOver{ false };
    bool mouseWasPressed{ false };

public:
    Button(double center_x, double center_y, const std::string& button_label);
    Button(double center_x, double center_y, double width_, double height_, const std::string& button_label = "");

    virtual void Draw() const;

    bool Did_click_button(bool is_game_screen = false);
};
