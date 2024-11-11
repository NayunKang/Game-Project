#pragma once

#include "Camera.h"
#include "Tile.h"
#include "Window.h"
#include "Rect.h"

using namespace doodle;

class Field
{
private:
	static const int field_width = 80;
	static const int field_height = 50;
	static const int window_tile_width = 30;
	static const int window_tile_height = 20;

	Tile* tiles[field_width][field_height] = { };
	math::ivec2* tiles_position[field_width][field_height] = { };
	math::irect2* tiles_area[field_width][field_height] = { };
	
	Camera* camera;

	Tile normal;
	Tile built;
	Tile npc;

public:
	Field();
	~Field();

	int x_interval = window_width / window_tile_width;
	int y_interval = window_height / window_tile_height;

	// Get Field variables
	const int& Get_field_width() const { return field_width; }
	const int& Get_field_height() const { return field_height; }
	const int& Get_window_tile_width() const { return window_tile_width; }
	const int& Get_window_tile_height() const { return window_tile_height; }
	const math::ivec2 Get_field_size() const { return math::ivec2{ window_tile_width* x_interval, window_tile_height* y_interval }; }
	const math::ivec2 Get_field_index_size() const { return math::ivec2{ field_width, field_height }; }

	// Get Tile variables
	const Tile& Get_tile(int x, int y) const { return *tiles[x][y]; }
	const math::ivec2 Get_tile_position(int x, int y) const { return *tiles_position[x][y]; }
	const math::irect2 Get_tile_area(int x, int y) const { return *tiles_area[x][y]; }

	Camera& Get_camera() const { return *camera; }

	void Generate_field();
	void Resize();
	void Draw_field() const;

	// Change after fixed (Make to get tiles)
	void Change_tile(int x, int y, Tiles tile);

};