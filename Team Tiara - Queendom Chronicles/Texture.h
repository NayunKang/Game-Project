#pragma once
#include "Vec2.h"

class Texture
{
	friend class TextureManager;
	friend class SpriteFont;
public:
	Texture() {}
	void Draw();
	void Draw(math::vec2 position, math::ivec2 texelPos, math::ivec2 frameSize);
	math::ivec2 GetSize();

private:
	Texture(const std::filesystem::path& filePath);
	Texture(doodle::Image&& doodleImage);
	doodle::Image image;
};