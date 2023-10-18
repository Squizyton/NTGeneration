#include "LevelGenerator.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>


typedef std::vector<std::vector<LevelGenerator::GridSpace>> Matrix;
typedef std::vector<LevelGenerator::GridSpace> Row;

LevelGenerator::LevelGenerator(float worldUnits)
{
    worldUnitsInOneGridCell = worldUnits;
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
    auto* walker = new class walker;
    walker->ChangeDirection(1);


    //Get center of the grid
    auto* spawnPos = new Vector2(round(roomWidth / 2.f), round(roomHeight / 2.f));
    walker->pos = *spawnPos;

    walkers.push_back(walker);


    GenerateFloor(gridMatrix);
}


void LevelGenerator::SpawnNewWalker()
{
}


//TODO start converting things to async later on
void LevelGenerator::GenerateFloor(std::vector<std::vector<LevelGenerator::GridSpace>> gridMatrix)
{
    printf("Generating Floor");

    int iterations = 0;

    do
    {
        //for every walker create a floor tile under them
        for (int i = 0; i < walkers.size(); i++)
        {
            walker* walker = walkers[i];


            gridMatrix[static_cast<int>(walker->pos.x)][static_cast<int>(walker->pos.y)] = static_cast<GridSpace>(2);
        }


        //See if we are destroying a walker
        int numberChecks = walkers.size();
        for (int x = 0; x < numberChecks; x++)
        {
            if (walkers[x]->WillIGetDestroyed(chanceWalkerDestroy) && walkers.size() > 1)
            {
                //remove walker then break so we only remove one
                walkers.erase(walkers.begin() + x);
                break;
            }
        }

        //Change Direction
        for (int x = 0; x < numberChecks; x++)
        {
            walkers[x]->ChangeDirection(chanceWalkerChangeDir);
        }


        //Spawn new walker
        numberChecks = walkers.size();
        for (int i = 0; i < numberChecks; i++)
        {
            if (rand() % 10 + 1 < chanceWalkerChangeDir * 10 && numberChecks < maxWalkers)
            {
                walker* walker = new class walker;
                walker->ChangeDirection(1);
                walker->pos = walkers[i]->pos;
                walkers.push_back(walker);
            }
        }

        //move the walkers
        for (int i = 0; i < numberChecks; i++)
        {
            walkers[i]->MoveWalker();
        }


        //check boundries
        for (int i = 0; i < numberChecks; i++)
        {
            walker thisWalker = *walkers[i];

            thisWalker.pos.x = std::clamp(thisWalker.pos.x, 1.f, static_cast<float>(roomWidth - 2));
            thisWalker.pos.y = std::clamp(thisWalker.pos.y, 1.f, static_cast<float>(roomWidth - 2));

            walkers[i] = &thisWalker;
        }


        // if ((float)NumberOfFloors() / (float)grid.Length > percentToFill){
        //     break;


        iterations++;
        printf("%d",iterations);
    }
    while (iterations < 100);


    printf("done");
}
