#include <fstream>
#include <filesystem>
#include <iostream>
#include "Npc.h"
#include "Engine.h"

#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <doodle/random.hpp>

Npc::Npc(const std::filesystem::path& npcIntoFile, math::vec2 position_,
	int width_, int height_, int timer_)
	: Unit(position_, width_, height_), timer(timer_), max_sequence(0)
{
	Load(npcIntoFile);
}
Npc::Npc(math::vec2 position_, int width_, int height_, int timer_)
	: Unit(position_, width_, height_), timer(timer_), max_sequence(0)
{
}
void Npc::Load(const std::filesystem::path& npcIntoFile)
{
	if (npcIntoFile.extension() != ".npc")
	{
		throw std::runtime_error("Bad Filetype. " + npcIntoFile.generic_string() + " not a npc info file (.npc)");
	}

	std::ifstream inFile(npcIntoFile);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to load " + npcIntoFile.generic_string());
	}

	std::string text;
	inFile >> text;

	std::vector<std::string> message_vector{};

	int sequence_count{ 0 };
	while (inFile.eof() == false)
	{
		if (text == "Name")
		{
			inFile >> name;
		}
		else if (text == "Conversation")
		{
			message_vector.clear();
			std::string message;
			std::getline(inFile, message);
			while (message != "ConvEnd")
			{
				if (message != "")
					message_vector.push_back(message);

				std::getline(inFile, message);
			}
			conversation.insert({ sequence_count++, message_vector });
		}
		else
		{
			std::cout << "Unknown command in " + npcIntoFile.generic_string() << std::endl;
		}
		inFile >> text;
	}
	max_sequence = sequence_count;

}
void Npc::Update()
{
	timer++;
	if (timer < 10)
	{
		if (is_moved == true)
		{
			moving_direction = static_cast<Direction>(
				random(static_cast<int>(Direction::LEFT), static_cast<int>(Direction::STOP)));
		}
	}
	if (timer > 20)
	{
		//is_moved = false;
		if (is_moved == true)
		{
			moving_direction = Direction::STOP;
		}
	}
	if (timer > 120)
	{
		timer = 0;
	}

	Moving();
}
