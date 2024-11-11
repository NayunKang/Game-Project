
#include "Building.h"
#include "Engine.h"

#include <iostream>
#include <doodle/drawing.hpp>

Building::Building(int x_, int y_, Building_Type* type_)
	: x(x_), y(y_), type(type_), position(0, 0), area({ 0, 0 }, { 0, 0 })
{}
void Building::Update()
{
	type->Update();
}
void Building::Draw() const
{
	Field& field = Engine::Get_game_manager().Get_field();
	type->Draw((x - type->Get_width() / 2) * field.x_interval, y * field.y_interval);

	// if Debug, Draw area rectangle and center position
#if _DEBUG
	push_settings();
	no_fill();
	set_outline_color(255, 255, 0);
	set_outline_width(5);
	draw_rectangle(area.Left(), area.Bottom(), area.Size().x, area.Size().y);
	pop_settings();
#endif

	// Draw producing resource (postponed)
	//if (time >= 20)
	//{
	//	double half_width = type->Get_width() * Engine::Get_game_manager().Get_field().x_interval / 2.0;
	//	double half_height = type->Get_height() * Engine::Get_game_manager().Get_field().y_interval / 2.0;
	//
	//	push_settings();
	//	set_image_mode(RectMode::Center);
	//	draw_image(Engine::Get_game_manager().Get_resource(Resource_list::WOOD).Get_image(),
	//		((x - type->Get_width() / 2.0) * Engine::Get_game_manager().Get_field().x_interval) + half_width,
	//		(y * Engine::Get_game_manager().Get_field().y_interval) + half_height + DeltaTime * 200,
	//		resource_image_size, resource_image_size);
	//	pop_settings();
	//}
}
void Building::SetPosition(math::ivec2 pos)
{
	position = pos;
}
void Building::SetArea(math::irect2 rect)
{
	area = rect;
}

Building_Type::Building_Type(std::string name_, int width_, int height_, Image image_)
	: name(name_), width(width_), height(height_), image(image_)
{}
Building_Type::Building_Type(std::string name_, int width_, int height_, int wood_cost_, int stone_cost_, Image image_)
	: name(name_), width(width_), height(height_), wood_cost(wood_cost_), stone_cost(stone_cost_), image(image_)
{}

void Building_Type::Draw(int x_, int y_) const
{
	draw_image(image, x_, y_,
		width * Engine::Get_game_manager().Get_field().x_interval,
		height * Engine::Get_game_manager().Get_field().y_interval);
}

bool Install_building(int x, int y, Building_Type* type)
{
	Field& field = Engine::Get_game_manager().Get_field();

	for (int i = 0; i < type->Get_width(); i++)
	{
		for (int j = 0; j < type->Get_height(); j++)
		{
			if (&field.Get_tile(x - (type->Get_width() / 2) + i, y + j) == nullptr)
			{
				return false;
			}
			else if (field.Get_tile(x - (type->Get_width() / 2) + i, y + j).Get_is_movable() == false)
			{
				return false;
			}
		}  
	}

	std::cout << "Install Building!\n";

	Engine::Get_game_manager().Get_resource(Resource_list::WOOD).Update_reserve(-type->Get_wood_cost());
	Engine::Get_game_manager().Get_resource(Resource_list::STONE).Update_reserve(-type->Get_stone_cost());

	Building* installing_building = new Building(x, y, type);
	installing_building->SetPosition( field.Get_tile_position(x, y) );
	installing_building->SetArea(
		{ math::ivec2{ field.Get_tile_position(x, y).x - (type->Get_width() / 2 * field.x_interval) - (field.x_interval / 2), 
			field.Get_tile_position(x, y).y - (field.y_interval / 2)},
		math::ivec2{ field.Get_tile_position(x, y).x + ((type->Get_width() / 2 + type->Get_width() % 2) * field.x_interval - (field.x_interval / 2)),
			field.Get_tile_position(x, y).y + type->Get_height() * field.y_interval - (field.y_interval / 2)} });
	
	Engine::Get_game_manager().Get_buildings().push_back(installing_building);

	for (int i = 0; i < type->Get_width(); i++)
	{
		for (int j = 0; j < type->Get_height(); j++)
		{
			field.Change_tile(x - (type->Get_width() / 2) + i, y + j, Tiles::built);
		}
	}
	return true;
}

void Production_building::Update()
{
	Engine::Get_game_manager().Get_resource(resource).Update_reserve(product_amount * DeltaTime);
}