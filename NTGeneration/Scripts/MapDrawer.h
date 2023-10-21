#pragma once
#include <map>
#include <SDL_render.h>
#include <vector>

#include "LevelGenerator.h"

typedef std::vector<std::vector<LevelGenerator::GridSpace>> Matrix;
typedef std::map<std::string,SDL_Texture*> WallDictionary;

class MapDrawer
{
   
public:
    MapDrawer();
    void DrawMap(Matrix &grid_array,int roomWidth, int roomHeight);
    bool LoadTextures(std::string levelPath, int texHeight, int texWidth);
private:
    SDL_Rect src, dest;
    std::pmr::vector<SDL_Texture*> ground_textures_;
    WallDictionary wall_textures_;
    
};
