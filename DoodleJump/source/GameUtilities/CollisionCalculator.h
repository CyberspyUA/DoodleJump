#pragma once
#include "..\\Entity.h"
#include "...\\FrameworkExtended\\FrameworkRemake.h"
class Point;
class Entity;

bool collided(const Point& mousePos, const Entity* a)
{
    if (a->getX() + a->getHitboxDeltaX() <= mousePos.x &&
        a->getX() + a->getHitboxDeltaX() + a->getHitboxWidth() >= mousePos.x &&
        a->getY() + a->getHitboxDeltaY() <= mousePos.y &&
        a->getY() + a->getHitboxDeltaY() + a->getHitboxHeight() >= mousePos.y)
        return true;
    return false;
}
bool collided(const Entity* a, const Entity* b)
{
    if (a->getX() + a->getHitboxDeltaX() > b->getX() + b->getHitboxDeltaX() + b->getHitboxWidth() ||
        b->getX() + b->getHitboxDeltaX() > a->getX() + a->getHitboxDeltaX() + a->getHitboxWidth())
        return false;

    if (a->getY() + a->getHitboxDeltaY() > b->getY() + b->getHitboxDeltaY() + b->getHitboxHeight() ||
        b->getY() + b->getHitboxDeltaY() > a->getY() + a->getHitboxDeltaY() + a->getHitboxHeight())
        return false;

    return true;
}