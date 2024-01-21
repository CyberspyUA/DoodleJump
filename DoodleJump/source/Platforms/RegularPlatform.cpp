#include "RegularPlatform.h"
Entity::CollisionType RegularPlatform::collideType = Entity::CollisionType::pNormal;

void RegularPlatform::update(unsigned deltaTime, Framework* win) {}

void RegularPlatform::draw(Framework* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  RectangleF(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::platform[sprite::Platform::NORMAL]);
}

Entity::CollisionType RegularPlatform::collide(Entity* col, Framework* win) {
    return collideType;
}