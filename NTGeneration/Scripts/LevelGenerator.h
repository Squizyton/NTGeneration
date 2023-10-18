#pragma once
#include <vector>

#include "walker.h"
#include "Utilties/Utils.h"


class LevelGenerator
{
public:
    LevelGenerator(float worldUnits = 1.f);
    void Setup(int room_width, int room_height);

    enum GridSpace { null, empty, ground, wall };

private:
    //What is this spot


    float worldUnitsInOneGridCell = 1;
    int roomHeight, roomWidth;


    std::pmr::vector<walker*> walkers;


    //Generation Variables
    float chanceWalkerChangeDir = .5f;
    float chanceWalkerSpawn = 0.05f;
    float chanceWalkerDestroy = .05f;
    const int maxWalkers = 10;
    float percentToFill = .2f;


    //functions
    void GenerateFloor(std::vector<std::vector<LevelGenerator::GridSpace>> gridArray);
    void SpawnNewWalker();
};
