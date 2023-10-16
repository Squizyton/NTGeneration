// NTGeneration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Scripts/Game.h"

int main()
{
   Game game;

   if(game.Init())
   {
      game.GameLoop();
   }

   game.ShutDown();

   return 0;
   
}
