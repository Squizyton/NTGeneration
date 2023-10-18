#include "LevelGenerator.h"

#include <cmath>
#include <ctime>
#include <vector>


Direction* direction = new Direction();


typedef std::vector<std::vector<LevelGenerator::GridSpace>> Matrix;
typedef std::vector<LevelGenerator::GridSpace> Row;

LevelGenerator::LevelGenerator(float worldUnits)
{
    worldUnitsInOneGridCell = worldUnits;
}


Vector2 RandomDirection()
{
    /* initialize random seed: */
    srand(time(nullptr));

    //pick random int between 0 and 3
    int choice = rand() % 4 + 1;
    //use that int to chose a direction
    switch (choice)
    {
    case 0:
        return *Direction::down;
    case 1:
        return *Direction::left;
    case 2:
        return *Direction::up;
    default:
        return *Direction::right;
    }
}


void LevelGenerator::Setup(const int room_width, const int room_height)
{
    //set the room wid
    this->roomWidth = static_cast<int>(std::round(static_cast<float>(room_width) / worldUnitsInOneGridCell));
    this->roomHeight = static_cast<int>(std::round(static_cast<float>(room_height) / worldUnitsInOneGridCell));

    const int height = room_width;


    Matrix gridMatrix;

    for (int x = 0; x < roomWidth; x++)
    {
        Row row(roomHeight);

        for (size_t y = 0; y < roomHeight; y++)
        {
            row[y] = static_cast<GridSpace>(1);
        }

        gridMatrix.push_back(row);
    }


    //TODO:: Maybe move this into it's own thing
    //create the first walker
    auto* walker = new struct walker;
    walker->dir = RandomDirection();


    //Get center of the grid
    auto* spawnPos = new Vector2(round(roomWidth / 2.f), round(roomHeight / 2.f));
    walker->pos = *spawnPos;

    walkers.push_back(walker);


    GenerateFloor(gridMatrix);
}

//TODO start converting things to async later on
void LevelGenerator::GenerateFloor(std::vector<std::vector<LevelGenerator::GridSpace>> gridMatrix)
{
    printf("Generating Floor");

    int iterations = 0;

    do
    {
        //for every walker create
        for (int i = 0; i < walkers.size(); i++)
        {
            walker* walker = walkers[i];


            gridMatrix[static_cast<int>(walker->pos.x)][static_cast<int>(walker->pos.y)] = static_cast<GridSpace>(2);
        }


        iterations++;
    }
    while (iterations < 10000000);
}
