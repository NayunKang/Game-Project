
#include "window.h"
#include "field.h"

#include <doodle/doodle.hpp>
#include "Field.h"

using namespace doodle;

Field::Field()
	: normal{ Tile(Image{ "Assets/grass.jpg" }, true) },
	built{ Tile(Image{ "Assets/grass.jpg" }, false) },
	npc{ Tile(Image{ "Assets/grass.jpg" }, false, true) },
	camera{ new Camera({ field_width / 2.0 * x_interval, field_height / 2.0 * y_interval }, 
		math::ivec2{ field_width * x_interval - window_width, field_height * y_interval - (window_height / 2) }) }
{
	Generate_field();
}
Field::~Field()
{
	delete camera;
}

void Field::Generate_field()
{
	for (int x = 0; x < field_width; x++)
	{
		for (int y = 0; y < field_height; y++)
		{
			tiles[x][y] = &normal;
			tiles_position[x][y] = new math::ivec2{
				x * x_interval + x_interval / 2, y * y_interval + y_interval / 2 };
			tiles_area[x][y] = new math::irect2{
				{x * x_interval, y * y_interval}, {(x + 1) * x_interval, (y + 1) * y_interval} };
		}
	}
}

void Field::Resize()
{
	x_interval = window_width / window_tile_width;
	y_interval = window_height / window_tile_height;

	camera->Set_movable_max_position({ field_width * x_interval - window_width, 
		field_height * y_interval - (window_height * 2 / 3) });

	for (int x = 0; x < field_width; x++)
	{
		for (int y = 0; y < field_height; y++)
		{
			*tiles_position[x][y] = { x * x_interval + x_interval / 2, y * y_interval + y_interval / 2 };
			*tiles_area[x][y] = math::irect2{ { x * x_interval, y * y_interval }, { (x + 1) * x_interval, (y + 1) * y_interval } };
		}
	}
}

void Field::Draw_field() const
{
	// Draw Tiles
	for (int x = 0; x < field_width; x++)
	{
		for (int y = 0; y < field_height; y++)
		{
			if (camera->Get_show_area().Is_intersects(static_cast<math::rect2>(Get_tile_area(x, y))))
			{
				draw_image(Get_tile(x, y).Get_image(),
					Get_tile_position(x, y).x - x_interval / 2.0, Get_tile_position(x, y).y - y_interval / 2.0,
					x_interval, y_interval);
			}
		}
	}

	// Draw tile grid lines
	// Draw Red dot when tile is not movable
#if _DEBUG
	push_settings();
	set_outline_width(1);

	// Fill with red where is not movable
	set_fill_color(200, 0, 0);
	for (int x = 0; x < field_width; x++)
	{
		for (int y = 0; y < field_height; y++)
		{
			if (tiles[x][y]->Get_is_movable() == false)
			{
				draw_rectangle(
					Get_tile_position(x, y).x - x_interval / 2.0, Get_tile_position(x, y).y - y_interval / 2.0,
					x_interval, y_interval);
			}
		}
	}
	pop_settings();
#endif
}

// Change after fixed (Make to get tiles)
void Field::Change_tile(int x, int y, Tiles tile)
{
	switch (tile)
	{
	case Tiles::normal:
		tiles[x][y] = &normal;
		break;

	case Tiles::built:
		tiles[x][y] = &built;
		break;

	case Tiles::npc:
		tiles[x][y] = &npc;
		break;
	}
}