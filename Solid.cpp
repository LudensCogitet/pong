#include "./Solid.h"

Solid::Solid(float xPos,
             float yPos,
             float width,
             float height,
             sf::Color color) {
     shape.setSize(sf::Vector2f(width, height));
     shape.setOrigin(sf::Vector2f(width / 2, height / 2));

     shape.setFillColor(color);
     shape.setPosition(xPos, yPos);
 }

Solid::~Solid() {}

COLLISION_DIRECTION Solid::collidedWithScreenBoundary(sf::RenderWindow & window) {
    sf::FloatRect boundingRect  = shape.getGlobalBounds();
    sf::Vector2u windowSize     = window.getSize();

    if(boundingRect.left < 0) return LEFT;
    if(boundingRect.left + boundingRect.width > windowSize.x) return RIGHT;
    if(boundingRect.top < 0) return TOP;
    if(boundingRect.top + boundingRect.height > windowSize.y) return BOTTOM;

    return NO_COLLISION;
}

void Solid::setToScreenBoundary(COLLISION_DIRECTION collisionDir, sf::RenderWindow & window) {
    sf::Vector2f shapeSize = shape.getSize();
    sf::Vector2f shapePos = shape.getPosition();

    if(collisionDir == TOP) {
        shape.setPosition(shapePos.x, shapeSize.y / 2);
    }

    if(collisionDir == BOTTOM) {
        shape.setPosition(shapePos.x, window.getSize().y - shapeSize.y / 2);
    }

    if(collisionDir == LEFT) {
        shape.setPosition(shapeSize.x / 2, shapePos.y);
    }

    if(collisionDir == RIGHT) {
        shape.setPosition(window.getSize().x - shapeSize.x / 2, shapePos.y);
    }
}

COLLISION_DIRECTION Solid::collidedWithSolid(Solid & otherSolid) {
    sf::FloatRect collider = shape.getGlobalBounds();
    sf::FloatRect collidee = otherSolid.getShape().getGlobalBounds();

    if(!collider.intersects(collidee)) return NO_COLLISION;

    float bottomDiff    = (collider.top + collider.height) - collidee.top;
    float topDiff       = (collidee.top + collidee.height) - collider.top;
    float leftDiff      = (collider.left + collider.width) - collidee.left;
    float rightDiff     = (collidee.left + collidee.width) - collider.left;

    if(bottomDiff == topDiff    &&
       bottomDiff == leftDiff   &&
       bottomDiff == rightDiff) {
           return COLLISION;
    }

    float diffs[4] = {bottomDiff, topDiff, leftDiff, rightDiff};

    float minDiff = diffs[0];

    for(int i = 1; i < 4; i++) {
        if(diffs[i] < minDiff)
            minDiff = diffs[i];
    }

    if(minDiff == bottomDiff)   return BOTTOM;
    if(minDiff == topDiff)      return TOP;
    if(minDiff == leftDiff)     return LEFT;
    if(minDiff == rightDiff)    return RIGHT;

    return COLLISION;
}

void Solid::setToSolidBoundary(COLLISION_DIRECTION collisionDir, Solid & other) {
    sf::RectangleShape & otherShape = other.getShape();

    sf::Vector2f colliderSize = shape.getSize();
    sf::Vector2f colliderPos = shape.getPosition();
    sf::Vector2f collideeSize = otherShape.getSize();
    sf::Vector2f collideePos = otherShape.getPosition();

    if(collisionDir == TOP) {
        shape.setPosition(colliderPos.x, (collideePos.y + collideeSize.y / 2) + colliderSize.y / 2);
    }

    if(collisionDir == BOTTOM) {
        shape.setPosition(colliderPos.x, (collideePos.y - collideeSize.y / 2) - colliderSize.y / 2);
    }

    if(collisionDir == RIGHT) {
        shape.setPosition((collideePos.x + collideeSize.x / 2) + colliderSize.x / 2, colliderPos.y);
    }

    if(collisionDir == LEFT) {
        shape.setPosition((collideePos.x - collideeSize.x / 2) - colliderSize.x / 2, colliderPos.y);
    }
}

sf::RectangleShape & Solid::getShape() {
    return shape;
}
