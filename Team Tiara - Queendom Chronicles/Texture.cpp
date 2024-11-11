#include <doodle/drawing.hpp>      
#include "Texture.h"

Texture::Texture(doodle::Image&& doodleImage)
{
	image = std::move(doodleImage);
}

Texture::Texture(const std::filesystem::path& filePath)
{
	image = doodle::Image{ filePath };
}

void Texture::Draw(math::vec2 position, math::ivec2 texelPos, math::ivec2 frameSize)
{
	doodle::push_settings();
	doodle::draw_image(image, position.x, position.y, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	doodle::pop_settings();
}

void Texture::Draw()
{
	doodle::push_settings();
	doodle::draw_image(image, 0, 0);
	doodle::pop_settings();
}

math::ivec2 Texture::GetSize()
{
	return { image.GetWidth(), image.GetHeight() };
}
