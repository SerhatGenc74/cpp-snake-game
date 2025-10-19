#include "CollisionHandler.h"


CollisionHandler::CollisionHandler(){}

CollisionHandler::~CollisionHandler(){}

bool CollisionHandler::MapCollision(SDL_Rect a){
    return true;
}

bool CollisionHandler::CheckCollision(SDL_Rect src,SDL_Rect dst)
{
    bool x_overlaps = (src.x < dst.x + dst.w) && (src.x + src.w > dst.x);
    bool y_overlaps = (src.y < dst.y + dst.h) && (src.y + src.h > dst.y);

    return (x_overlaps && y_overlaps);
}