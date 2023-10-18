#include "walker.h"

#include <cstdlib>
#include <ctime>


Direction* direction = new Direction();

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

bool walker::WillIGetDestroyed(float chanceToBeKaboomed)
{
    //TODO:: Function not thread safe (working on it)
    int random = rand() % 10 + 1;


    if (random < chanceToBeKaboomed * 10)
    {
        return true;
    }

    return false;
}

void walker::ChangeDirection(float chanceToChangeDir)
{
    //TODO:: Still not thread safe. FIX IT
    int random = rand() % 10 + 1;


    if (random < chanceToChangeDir * 10)
    {
        dir = RandomDirection();
    }
}

void walker::MoveWalker()
{
    pos.x += dir.x;
    pos.y += dir.y;
}

