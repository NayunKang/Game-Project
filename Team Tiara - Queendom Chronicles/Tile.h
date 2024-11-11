#pragma once

#include <doodle/drawing.hpp>

using namespace doodle;

enum class Tiles
{
	normal,
	built,
	npc
};

class Tile
{
private:
	Image image;
	bool is_movable;
	bool is_npc;

public:
	Tile(Image image_, bool isMovable_, bool is_npc_ = false)
		: image(image_), is_movable(isMovable_), is_npc(is_npc_)
	{}

	Image Get_image() const { return image; }
	bool Get_is_movable() const { return is_movable; }
	bool Get_is_npc() const { return is_npc; }
};