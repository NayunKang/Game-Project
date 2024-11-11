#pragma once

#include "Button.h"
#include "Building_list.h"
#include "Engine.h"

class Shop_button : public Button
{
public:
	Shop_button(double corner_x, double corner_y, double width_, double height_, Building_list building_)
		: Button(corner_x + width_/2, corner_y + height_ /2, width_, height_), building(building_)
	{
	}

	void Draw() const override;
	void deco_draw() const;
private:
	Building_list building;
};
