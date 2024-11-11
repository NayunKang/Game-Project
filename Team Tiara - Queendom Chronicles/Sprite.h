#pragma once

#include <string>
#include <vector>

#include "Vec2.h"
#include "Animation.h"
#include "doodle/drawing.hpp"
#include "Texture.h"

class Sprite
{
public:
	Sprite(const std::filesystem::path& spriteInfoFile);
	~Sprite();
	void Load(const std::filesystem::path& spriteInfoFile);
	void Update();
	void Draw(math::vec2 position);
	void PlayAnimation(int anim);
	int GetCurrentAnim();
	bool IsAnimationDone();

	math::ivec2 GetHotSpot(int index);
	math::ivec2 GetFrameSize() const;

private:
	math::ivec2 GetFrameTexel(int frameNum) const;
	Texture* texturePtr;
	int currFrame;
	math::ivec2 frameSize;
	std::vector<math::ivec2> frameTexel;
	std::vector<Animation*> animations;
	std::vector<math::ivec2> hotSpotList;
};