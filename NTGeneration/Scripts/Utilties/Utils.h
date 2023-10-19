#pragma once
#include <random>
#include <thread>

class Utils
{
public:
    //While this is Technically slower...It's A)Thread safe and won't crash anything...B) Random. 
    static int intRand(const int & min, const int & max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std:: uniform_int_distribution<> distr(min,max);

        return distr(gen);
    }
};


class Vector2
{
public:
    Vector2(float newX = 0, float newY = 0);
    float x,y;
};

static class Direction
{
public:
   inline static Vector2* up = new Vector2(0,-1.f);
   inline static Vector2* down = new Vector2(0,1.f);
   inline static Vector2* left = new Vector2(-1.f,0);
   inline static Vector2* right = new Vector2(1.f,0);
};

