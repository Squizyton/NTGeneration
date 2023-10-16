#pragma once


#include <SDL.h>

class Game
{
public:
    bool Init();
    void GameLoop();
    void ShutDown();

    static SDL_Renderer* renderer;

private:
    bool isRunning = true;
    void HandleEvents();
    void Update();
    void Draw();


    //Get window as a pointer so we have direct access to it
    SDL_Window* window = nullptr;
};
