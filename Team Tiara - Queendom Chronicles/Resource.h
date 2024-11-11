#pragma once

#include <array>
#include <doodle/drawing.hpp>

using namespace doodle;

enum class Resource_list
{
	WOOD,
	STONE,
	FOOD,
};

class Resource
{
private:
	Image image;
	double reserve{ 5000 };
	int max_reserve{ 10000 };

public:
	Resource(Image image_)
		: image(image_)
	{}
	Resource(Image image_, int reserve_, int max_reserve_)
		: image(image_), reserve(reserve_), max_reserve(max_reserve_)
	{}

	Image Get_image() const { return image; }
	double Get_reserve() const { return reserve; }
	void Update_reserve(double reserve_amount);
	int Get_max_reserve() const { return max_reserve; }
};