#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"

Texture* TextureManager::Load(const std::filesystem::path& filePath)
{
    if (pathToTexture.count(filePath) == 0)  //filePath does not exist in our map
    {
        pathToTexture[filePath] = new Texture(filePath);
    }
    return pathToTexture[filePath];
}