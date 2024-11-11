#include "Button.h"

#include <doodle/drawing.hpp>
#include <doodle/input.hpp>

using namespace doodle;

Button::Button(double center_x, double center_y, const std::string& button_label)
	: width(100), height(35), left(center_x - 100 / 2.0), top(center_y - 35 / 2.0), label(button_label)
{
}

Button::Button(double center_x, double center_y, double width_, double height_, const std::string& button_label)
	: width(width_), height(height_), left(center_x - width_ / 2.0), top(center_y - height_ / 2.0), label(button_label)
{
}

void Button::Draw() const
{
	push_settings();
	set_frame_of_reference(FrameOfReference::LeftHanded_OriginTopLeft);
	set_outline_color(159);
	double tint_color = 255;
	double label_offset = 0;
	if (this->mouseIsOver)
	{
		if (doodle::MouseIsPressed)
		{
			tint_color = 200;
			label_offset = 2;
		}
		else
		{
			tint_color = 255;
		}
	}
	set_tint_color(tint_color);
	apply_translate(this->left, this->top);
	draw_image(Image{ "Assets/small_button.png" }, 0, 0, width, height);

	set_fill_color(0);
	no_outline();
	set_font_size(height * 0.3);
	set_font_backdrop_fade_out_interval(0.7, 0.7);
	draw_text(this->label, width / 8.0, height * 0.75 + label_offset);

	pop_settings();
}

bool Button::Did_click_button(bool is_game_screen)
{
	const auto the_left = this->left;
	const auto the_top = this->top;
	const auto the_right = the_left + width;
	const auto the_bottom = the_top + height;
	push_settings();

	if (is_game_screen == false)
	{
		set_frame_of_reference(FrameOfReference::LeftHanded_OriginTopLeft);
	}
	else
	{
		set_frame_of_reference(FrameOfReference::RightHanded_OriginBottomLeft);
	}
	const double mouse_x = doodle::get_mouse_x();
	const double mouse_y = doodle::get_mouse_y();
	pop_settings();

	const bool within_x = mouse_x > the_left && mouse_x < the_right;
	const bool within_y = mouse_y > the_top && mouse_y < the_bottom;
	mouseIsOver = within_x && within_y;
	const bool clicked_it = mouseIsOver && mouseWasPressed && !doodle::MouseIsPressed;
	mouseWasPressed = doodle::MouseIsPressed;

	return clicked_it;
}