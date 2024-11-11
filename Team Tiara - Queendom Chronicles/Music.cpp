//-------------------------------------------------------
// File name :  Music.cpp
// Authors   :  Minsu Kim
// Course    :  GAM100F21
//
// All content (C) 2021 DigiPen (USA) Corporation, all rights reserved.
//-------------------------------------------------------

#include "Music.h"
#include <iostream>

void Music::play_BGM(const std::string& file_path)
{
    if (!BGM.openFromFile(file_path))
    {
        throw std::runtime_error("Failed to load the BGM: " + file_path);
    }
    
    BGM.setVolume(BGM_volume);
    BGM.setLoop(true);
    BGM.play();
}