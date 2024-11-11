#pragma once

#include "Unit.h"
#include "Vec2.h"

#include <unordered_map>
#include <vector>
#include <doodle/drawing.hpp>

using namespace doodle;

class Npc : public Unit
{
public:
	Npc(math::vec2 position_, int width_ = 50, int height_ = 50, int timer_ = 0);
	Npc(const std::filesystem::path& npcIntoFile, math::vec2 position_,
		int width_ = 50, int height_ = 50, int timer_ = 0);
	void Load(const std::filesystem::path& npcIntoFile);
	void Update() override;

	int Get_max_sequence() const { return max_sequence; }
	int Get_chat_count(int sequence) const { return static_cast<int>(conversation.at(sequence).size()); }
	std::string Get_message(int sequence, int index) const { return conversation.at(sequence).at(index); }

private:
	int timer;
	int max_sequence;
	std::unordered_map<int, std::vector<std::string>> conversation;
};