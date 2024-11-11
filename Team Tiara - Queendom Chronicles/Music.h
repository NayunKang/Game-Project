//-------------------------------------------------------
// File name :  Music.h
// Authors   :  Minsu Kim
// Course    :  GAM100F21
//
// All content (C) 2021 DigiPen (USA) Corporation, all rights reserved.
//-------------------------------------------------------

#pragma once

#include <SFML/Audio.hpp>

namespace BGM_list
{
    const std::string background{ "Assets/background.ogg" };
    const std::string store{ "Assets/store.ogg" };
}

class Music
{
private:
    sf::Music                    BGM;

    float BGM_volume{ 30 };

public:
    void play_BGM(const std::string& file_path);
};
