#include "Game.h"

#include <future>
#include <SDL_image.h>
#include <iostream>

#include "LevelGenerator.h"
#include "MapDrawer.h"
#include "Utilties/TextureManager.h"


SDL_Renderer* Game::renderer = nullptr;
LevelGenerator* generator = new LevelGenerator();
MapDrawer* drawer = new MapDrawer();
Matrix gen_matrix;

typedef std::vector<std::vector<LevelGenerator::GridSpace>> Matrix;


Matrix Atest(LevelGenerator generator);

bool texturesLoaded = false;


//DEBUG
bool showNumbers = true;

bool LoadTextures(std::string filePath, int width, int height)
{
    return drawer->LoadTextures(filePath,width,height);
}


bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Crashed";
        return false;
    }


    //Create the window
    window_ = SDL_CreateWindow("NT Generation",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1270, 800, 0);


    //if Window failed to recreate
    if (!window_)
    {
        return false;
    }

    // Create the renderer: Pass in the window : he index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags : Special Flags - Use Hardware Acceleration, And VSync
    renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    if (!renderer)
    {
        return false;
    }


    gen_matrix = generator->Setup(30, 30);
    std::future<bool> async_function = std::async(LoadTextures, "assets/level1", 16, 16);

    if (async_function.get())
    {
      texturesLoaded = true;
    }

    return true;
}


void Game::GameLoop()
{
    while (isRunning)
    {
        HandleEvents();
        Update();
        Draw();
    }
}


void Game::Update()
{
}

void Game::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        //Get All keys by using null
        const Uint8* keystates = SDL_GetKeyboardState(nullptr);

        if (keystates[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
    }
}


void Game::Draw()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 30, 130, 76, 1);
    if(texturesLoaded)
        drawer->DrawMap(gen_matrix,30,30);

    if(showNumbers)
        drawer->DrawDebugValues(gen_matrix,30,30);
    
    SDL_RenderPresent(renderer);
}


void Game::ShutDown()
{
    //Destroys the renderer
    SDL_DestroyRenderer(renderer);
    //Destroys the window
    SDL_DestroyWindow(window_);
    ///Clean up all initialized subsystems. You should call this function even if you have already shutdown each initialized subsystem with SDL_QuitSubSystem().
    ///It is safe to call this function even in the case of errors in initialization.
    SDL_Quit();
}
