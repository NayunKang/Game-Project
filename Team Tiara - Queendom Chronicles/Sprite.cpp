#include "Sprite.h"
#include "Engine.h"
#include "TextureManager.h"
#include <fstream>

Sprite::Sprite(const std::filesystem::path& spriteInfoFile)
    : currFrame(0)
{
    Sprite::Load(spriteInfoFile);
}

Sprite::~Sprite() {
    for (Animation* anim : animations)
    {
        delete anim;
    }
    animations.clear();
}

void Sprite::Load(const std::filesystem::path& spriteInfoFile)
{
	animations.clear();
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt")
	{
		throw std::runtime_error("Bad Filetype. " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;

	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();

	inFile >> text;
    while (inFile.eof() == false)
    {
        if (text == "FrameSize")
        {
            inFile >> frameSize.x;
            inFile >> frameSize.y;
        }
        else if (text == "NumFrames")
        {
            int numFrames;
            inFile >> numFrames;
            for (int i = 0; i < numFrames; i++) {
                frameTexel.push_back({ frameSize.x * i, 0 });
            }
        }
        else if (text == "Frame")
        {
            int frameLocationX, frameLocationY;
            inFile >> frameLocationX;
            inFile >> frameLocationY;
            frameTexel.push_back({ frameLocationX, frameLocationY });
        }
        else if (text == "HotSpot")
        {
            int hotSpotX, hotSpotY;
            inFile >> hotSpotX;
            inFile >> hotSpotY;
            hotSpotList.push_back({ hotSpotX, hotSpotY });
        }
        else if (text == "Anim")
        {
            inFile >> text;
            animations.push_back(new Animation(text));
        }
        inFile >> text;
    }
    if (frameTexel.empty() == true)
    {
        frameTexel.push_back({ 0,0 });
    }
    if (animations.empty() == true)
    {
        animations.push_back(new Animation());
        PlayAnimation(0);
    }
}

void Sprite::Update()
{
    animations[currFrame]->Update();
}

void Sprite::Draw(math::vec2 position)
{
    texturePtr->Draw(position - static_cast<math::vec2>(GetHotSpot(0)), GetFrameTexel(animations[currFrame]->GetDisplayFrame()), frameSize);
}

void Sprite::PlayAnimation(int anim)
{
    if (anim < 0 || anim > static_cast<int>(animations.size()) - 1)
    {
		//Engine::GetLogger().LogError("Animation" + std::to_string(anim));
        currFrame = 0;
    }
    else {
        currFrame = anim;
        animations[currFrame]->ResetAnimation();
    }
}

int Sprite::GetCurrentAnim()
{
    return currFrame;
}

bool Sprite::IsAnimationDone()
{
	return animations[currFrame]->IsAnimationDone();
}

math::ivec2 Sprite::GetHotSpot(int index)
{
	if (index >= static_cast<int>(hotSpotList.size())) {
		//Engine::GetLogger().LogError("Hotspot error");
		return math::ivec2(0, 0);
	}
	return hotSpotList[index];
}

math::ivec2 Sprite::GetFrameSize() const
{
	return frameSize;
}

math::ivec2 Sprite::GetFrameTexel(int frameNum) const
{
    if (frameNum < 0 || frameNum >= static_cast<int>(frameTexel.size())) 
    {
        //Engine::GetLogger().LogError("Bad frame request" + std::to_string(frameNum));
        return math::ivec2{ 0, 0 };
    }
    return frameTexel[frameNum];
}
