#pragma once

class Utils
{
public:
    
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