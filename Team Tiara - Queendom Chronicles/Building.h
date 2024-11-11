#pragma once

#include "Resource.h"
#include "Rect.h"

#include <doodle/drawing.hpp>

using namespace doodle;

class Building_Type;
enum class Building_list;

class Building
{
public:
	Building(int x_, int y_, Building_Type* type_);
	void Update();
	void Draw() const;

	const math::ivec2 GetXY() const { return  { x, y }; }
	const math::ivec2 GetPosition() const { return position; }
	const math::irect2 GetArea() const { return area; }
	Building_Type* Get_type() const { return type; }

	void SetPosition(math::ivec2 pos);
	void SetArea(math::irect2 rect);

private:
	int x;
	int y;
	math::ivec2 position;
	math::irect2 area;

	Building_Type* type;
};

bool Install_building(int x, int y, Building_Type* type);

class Building_Type
{
public:
	Building_Type(std::string name_, int width_, int height_, Image image_);
	Building_Type(std::string name_, int width_, int height_, int wood_cost_, int stone_cost_, Image image_);

	virtual void Update() {};
	virtual void Draw(int x_, int y_) const;

	Image Get_image() const { return image; }
	const int Get_width() const { return width; }
	const int Get_height() const { return height; }
	const int Get_wood_cost() const { return wood_cost; }
	const int Get_stone_cost() const { return stone_cost; }
	const std::string Get_name() const { return name; }

private:
	std::string name;
	int width;
	int height;
	Image image;
	Image preview_image;

	int wood_cost{ 0 };
	int stone_cost{ 0 };
};

class Production_building : public Building_Type
{
private:
	Resource_list resource;
	int product_amount{ 10 };
	int resource_image_size{ 70 };

	Image preview_image;

public:
	Production_building(std::string name_, int width_, int height_, int wood_cost_, int stone_cost_, Image image_, Image preview_image_, Resource_list resource_, int product_amount_)
		: Building_Type(name_, width_, height_, wood_cost_, stone_cost_, image_), preview_image(preview_image_), resource(resource_), product_amount(product_amount_)
	{}
	
	Resource_list Get_resource() const { return resource; }
	int Get_product_amount() const { return product_amount; }
	Image Get_preview_image() const { return preview_image; }

	void Update() override;
}; 

class Residential_building : public Building_Type
{
private:
	int population_amount;

	Image preview_image;

public:
	Residential_building(std::string name_, int width_, int height_, int wood_cost_, int stone_cost_, Image image_, Image preview_image_, int population_amount_ = 1)
		: Building_Type(name_, width_, height_, wood_cost_, stone_cost_, image_), preview_image(preview_image_), population_amount(population_amount_)
	{}

	int Get_population_amount() const { return population_amount; }

	Image Get_preview_image() const { return preview_image; }
};