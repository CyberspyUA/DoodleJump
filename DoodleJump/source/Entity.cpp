#include "Entity.h"

#include <stdexcept>

Entity::Entity(const RectangleF& box, const RectangleF& hitBox)
    : box_(box),
      hitBox_(hitBox) {
    if (box.w <= 0 || box.h <= 0 || hitBox.w < 0 || hitBox_.h < 0) {
        throw std::invalid_argument("Invalid width/height for game object.");
    }
}
Entity::Entity(const RectangleF& box)
    : Entity(box, RectangleF(0, 0, box.w, box.h)) {}

Entity::~Entity() {}

void Entity::translateY(float deltaY) { box_.y += deltaY; }

int Entity::getX() const { return box_.x; }
int Entity::getY() const { return box_.y; }
int Entity::getWidth() const { return box_.w; }
int Entity::getHeight() const { return box_.h; }

int Entity::getHitboxDeltaX() const { return hitBox_.x; }
int Entity::getHitboxDeltaY() const { return hitBox_.y; }
int Entity::getHitboxWidth() const { return hitBox_.w; }
int Entity::getHitboxHeight() const { return hitBox_.h; }

