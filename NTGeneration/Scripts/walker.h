#pragma once
#include "Utilties/Utils.h"


class walker
{

    
public:
    Vector2 dir;
    Vector2 pos;
    bool WillIGetDestroyed(float chanceToBeKaboomed);
    void ChangeDirection(float chanceToChangeDir);
    void MoveWalker();
};
    