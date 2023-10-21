#include "MapDrawer.h"

#include <filesystem>
#include <iostream>

#include "Utilties/TextureManager.h"

void MapDrawer::DrawMap(Matrix& grid_array, int roomWidth, int roomHeight)
{
    for (int x = 0; x < roomWidth; x++)
    {
        for (int y = 0; y < roomHeight; y++)
        {
            //First check to see if ground
            if (grid_array[x][y] == static_cast<LevelGenerator::GridSpace>(2))
            {
                int offsetX = 32 / 2;
                int offsetY = 32 / 2;
                
                //TODO::IT IS NOT 16 YA DUMBASS
                dest.x = x * 1 * offsetX;
                dest.y = y * 1 * offsetY;
                TextureManager::Draw(ground_textures_[0], src, dest);

                //Bottom Wall
                if (grid_array[x][y + 1] == static_cast<LevelGenerator::GridSpace>(3))
                {
                    dest.y = 0;
                    dest.y = (y + 1) * 16;
                    TextureManager::Draw(wall_textures_["center"], src, dest);
                    
                }
                //Top Wall
                if (grid_array[x][y - 1] == static_cast<LevelGenerator::GridSpace>(3))
                {
                   dest.y = 0;
                   dest.y = (y - 1) * 16;
                   TextureManager::Draw(wall_textures_["center"], src, dest);
                }
                //Right Wall
                if (grid_array[x + 1][y] == static_cast<LevelGenerator::GridSpace>(3))
                {
                   dest.x = 0;
                   dest.x = (x + 1) * 16;
                   TextureManager::Draw(wall_textures_["center"], src, dest);

                  
                }
                //Left Wall
                if (grid_array[x - 1][y] == static_cast<LevelGenerator::GridSpace>(3))
                {
                  // dest.x = 0;
                  // dest.x = (x - 1) * 16;
                  // TextureManager::Draw(wall_textures_["center"], src, dest);
                }
            }
        }
    }
}


bool MapDrawer::LoadTextures(std::string levelPath, int texHeight, int texWidth)
{
    //clear the previous vectors for levels
    ground_textures_.clear();
    wall_textures_.clear();


    src.w = texWidth;
    src.h = texHeight;

    dest.w = texWidth;
    dest.h = texHeight;

    //get the file count in the folder
    int count = 0;


    try
    {
        std::cout << levelPath;

        std::string groundtextures_string = levelPath + "/ground";


        const std::filesystem::path p1{groundtextures_string};


        //Loading ground textures
        for (auto& p : std::filesystem::directory_iterator(p1))
        {
            count++;
        }

        std::cout << "File Count: " << count;

        //Grass textures
        for (int x = 0; x < count; x++)
        {
            std::string textureLoc = groundtextures_string + "/";
            textureLoc += std::to_string(x + 1) + ".png";


            if (TextureManager::LoadTexture(textureLoc.c_str()) != nullptr)
            {
                ground_textures_.emplace_back(TextureManager::LoadTexture(textureLoc.c_str()));
            }
            else
            {
                std::cout << "Could not load: " << textureLoc;
                break;
            }
        }


        std::string wall_string = levelPath + "/walls";


        const std::filesystem::path p2{wall_string};

        //Loading ground textures
        for (auto& p : std::filesystem::directory_iterator(p1))
        {
            count++;
        }

        const std::string wallSides[] = {"center", "left", "right", "top", "down"};

        //Level wall textures
        for (int x = 0; x < wallSides->size(); x++)
        {
            std::string textureToLoad = wall_string + "/" + wallSides[x] + ".png";


            const auto texture = TextureManager::LoadTexture(textureToLoad.c_str());
            if (texture != nullptr)
            {
                wall_textures_.insert({wallSides[x], texture});
            }
            else
            {
                std::cout << "\nCould not load: " << textureToLoad;
                break;
            }
        }


        return true;
    }
    catch (...)
    {
        std::cout << "\nCouldn't find folder: " << levelPath;
        return false;
    }
}

MapDrawer::MapDrawer()
{
}
