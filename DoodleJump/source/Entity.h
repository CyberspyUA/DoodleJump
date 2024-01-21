#pragma once
#include <Framework.h>
#include "GameUtilities/Rechtangle.h"

class Entity
{
protected:
    RectangleF box_;
    RectangleF hitBox_;
public:
    Entity(const RectangleF& box, const RectangleF& hitBox);
    Entity(const RectangleF& box);
    virtual ~Entity();

    enum class CollisionType {
        pNormal,
        pBreakable,
        pMovable,
        enemyNormal,
        spring,
        none
    };

    virtual void update(unsigned deltaTime, Framework* win) = 0;
    virtual void draw(Framework* win, const PointF& offset = {0, 0}) const = 0;
    virtual CollisionType collide(Entity* col, Framework* win) = 0;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    int getHitboxDeltaX() const;
    int getHitboxDeltaY() const;
    int getHitboxWidth() const;
    int getHitboxHeight() const;

    void translateY(float deltaY);


};

