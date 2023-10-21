#pragma once
#include <map>
#include <SDL_render.h>
#include <vector>

#include "LevelGenerator.h"

typedef std::vector<std::vector<LevelGenerator::GridSpace>> Matrix;
typedef std::map<std::string,SDL_Texture*> WallDictionary;
typedef std::map<int,SDL_Texture*> DebugDictionary;

class MapDrawer
{
   
public:
    MapDrawer();
    void DrawMap(Matrix &grid_array,int roomWidth, int roomHeight);
    bool LoadTextures(std::string levelPath, int texHeight, int texWidth);
    void DrawDebugValues(Matrix &grid, int roomWidth, int roomHeight);
    void LoadDebugNumbers(bool value);
private:
    SDL_Rect src, dest;
    std::pmr::vector<SDL_Texture*> ground_textures_;
    WallDictionary wall_textures_;
    DebugDictionary debugValues;
};
