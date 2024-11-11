
#include "Shop_button.h"
#include "Resource.h"
#include "Engine.h"
#include "GameManager.h"

#include <doodle/drawing.hpp>
#include <doodle/input.hpp>

using namespace doodle;

void Shop_button::Draw() const
{
	///////////////////////////////// Common function (Without Decoration) /////////////////////////////////
	Building_Type* type = Engine::Get_game_manager().Get_building_types()[building];

	push_settings();
	set_frame_of_reference(FrameOfReference::LeftHanded_OriginTopLeft);
	set_outline_color(159);
	double fill_color = 220;
	double label_offset = 0;
	if (mouseIsOver)
	{
		if (doodle::MouseIsPressed)
		{
			fill_color = 200;
			label_offset = 1;
		}
		else
		{
			fill_color = 240;
		}
	}

	set_fill_color(fill_color);
	draw_rectangle(left, top, width, height);

	// Draw lines
	set_outline_color(0);
	draw_line(left + width / 6.0, top, left + width / 6.0, top + height);
	draw_line(left + width * (3.7 / 6.0), top, left + width * (3.7 / 6.0), top + height);

	// Draw building
	set_fill_color(0X000000);
	set_font_size(15);
	draw_text(type->Get_name(), left + doodle::Width * 0.8 / 24.0, top + height * 6.3 / 7.0);
	
	set_font_size(12);

	///////////////////////////////// Production Building /////////////////////////////////
	if (typeid(*type) == typeid(Production_building))
	{
		push_settings();

		set_image_mode(RectMode::Center);
		draw_image(static_cast<Production_building*>(type)->Get_preview_image(), left + doodle::Width * 1.0 / 24.0 + 40, top - height / 40 + 40, 80, 80);

		pop_settings();

		std::string produce_text = "If you build this building, you can get " + std::to_string(static_cast<Production_building*>(type)->Get_product_amount());

		switch (static_cast<Production_building*>(type)->Get_resource())
		{
		case Resource_list::WOOD:
			produce_text += " woods ";
			break;

		case Resource_list::STONE:
			produce_text += " trees ";
			break;

		case Resource_list::FOOD:
			produce_text += " foods ";
			break;
		}
		draw_text(produce_text + "per minute.", left + width * 2.5 / 11 , top + height / 4);

		draw_image(Engine::Get_game_manager().Get_resource(static_cast<Production_building*>(type)->Get_resource()).Get_image(), left + width * 13/44, top + height / 3 , 60, 60);



		push_settings();
		set_fill_color(0X000000);
		set_font_size(50);
		draw_text(" x " + std::to_string(static_cast<Production_building*>(type)->Get_product_amount())
			, left + width * 4 /11, top + height);
	}
	///////////////////////////////// Residential Building /////////////////////////////////
	else if (typeid(*type) == typeid(Residential_building))
	{
		push_settings();

		set_image_mode(RectMode::Center);
		draw_image(static_cast<Residential_building*>(type)->Get_preview_image(), left + doodle::Width * 1.0 / 24.0 + 40, top - height / 40 + 40, 80, 80);

		pop_settings();

		draw_text("If you build this house, you can have " + std::to_string(static_cast<Residential_building*>(type)->Get_population_amount()) + " man"
			, left + width * 2.5 / 11 , top + height / 4);

		// @ After change to get somewhere the image.
		draw_image(Image{ "Assets/Unit.png" }, left + width * 13/44,top + height / 3 , 60, 60);

		push_settings();
		set_fill_color(0X000000);
		set_font_size(50);
		draw_text(" x " + std::to_string(static_cast<Residential_building*>(type)->Get_population_amount())
			, left + width * 4 /11, top + height);
	}

	// Cost resources
	set_font_size(15);
	draw_text("<Resources needed for construction>", left + width * 0.68, top + height / 4 );
	set_font_size(20);

	draw_image(Engine::Get_game_manager().Get_resource(Resource_list::WOOD).Get_image(),left + width * 0.7,top + height * 1 / 3, 50, 50);
	draw_text(" x " + std::to_string(type->Get_wood_cost()) + " + ", left + width * 0.74, top + height * 3/4);

	draw_image(Engine::Get_game_manager().Get_resource(Resource_list::STONE).Get_image(), left + width * 0.81, top + height * 1 / 3, 50, 50);
	draw_text(" x " + std::to_string(type->Get_stone_cost()) + ' ',left + width * 0.86, top + height * 3/4);

	pop_settings();
}

void Shop_button::deco_draw() const
{
	Building_Type* type = Engine::Get_game_manager().Get_building_types()[building];

	push_settings();
	set_frame_of_reference(FrameOfReference::LeftHanded_OriginTopLeft);
	set_outline_color(159);
	double fill_color = 220;
	double label_offset = 0;
	if (mouseIsOver)
	{
		if (doodle::MouseIsPressed)
		{
			fill_color = 200;
			label_offset = 1;
		}
		else
		{
			fill_color = 240;
		}
	}

	set_fill_color(fill_color);
	draw_rectangle(left, top, width, height);

	// Draw building
	draw_image(type->Get_image(), left , top + height / 4, 80, 80);

	set_font_size(12);
	set_fill_color(0);
	draw_text("<Resources needed for construction>", left + width / 6, top + height / 4);
	set_font_size(20);

	draw_image(Engine::Get_game_manager().Get_resource(Resource_list::WOOD).Get_image(), left + width / 3.5, top + height * 1 / 2, 30, 30);
	draw_text(" x " + std::to_string(type->Get_wood_cost()) + " + ", left + width * 0.4, top + height * 3 / 4);

	draw_image(Engine::Get_game_manager().Get_resource(Resource_list::STONE).Get_image(), left + width  * 0.7, top + height * 1 / 2, 30, 30);
	draw_text(" x " + std::to_string(type->Get_stone_cost()) + ' ', left + width * 0.8, top + height * 3 / 4);

	pop_settings();
}
