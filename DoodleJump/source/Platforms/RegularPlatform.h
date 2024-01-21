#pragma once
#include "Platform.h"

class RegularPlatform : public Platform
{
    static CollisionType collideType;
public:
    using Platform::Platform;

    void update(unsigned deltaTime, Framework* win) override;
    void draw(Framework* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(Framework* col, Framework* win) override;

};

