#include "TextureManager.h"

#include <iostream>
#include <SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    //Create a surface
    SDL_Surface* tmpSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);


    if (tex != nullptr)
    {
        std::cout << "Loaded Texture:" << fileName;
    }

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, nullptr, &dest);
}
