#pragma once
#include <SDL2/SDL.h>

class CollisionHandler
{
private:
    
public:
    CollisionHandler();
    ~CollisionHandler();
    bool CheckCollision(SDL_Rect src,SDL_Rect dst);
    bool MapCollision(SDL_Rect a);
};

