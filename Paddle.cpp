#include "./Paddle.h"

Paddle::Paddle(float xPos,
               float yPos,
               float width,
               float height,
               float newSlowSpeed,
               float newMediumSpeed,
               float newFastSpeed,
               float newHitForce,
               float newVelocityTransfer,
               sf::Keyboard::Key newUp,
               sf::Keyboard::Key newDown,
               sf::Keyboard::Key newLeft,
               sf::Keyboard::Key newRight,
               sf::Color color): Solid(xPos, yPos, width, height, color) {
    slowSpeed   = newSlowSpeed;
    mediumSpeed = newMediumSpeed;
    fastSpeed   = newFastSpeed;

    up          = newUp;
    down        = newDown;
    left        = newLeft;
    right       = newRight;

    speed       = mediumSpeed;
    deltaY      = 0;
    hitForce    = newHitForce;
    velocityTransfer = newVelocityTransfer;
}

Paddle::~Paddle() {}

void Paddle::update(float dt) {
    speed = mediumSpeed;
    deltaY = 0;

    if(sf::Keyboard::isKeyPressed(left)) {
        speed = slowSpeed;
    }
    if(sf::Keyboard::isKeyPressed(right)) {
        speed = fastSpeed;
    }
    if(sf::Keyboard::isKeyPressed(up)) {
        deltaY = -1 * speed;
        shape.move(0, deltaY * dt);
    }
    if(sf::Keyboard::isKeyPressed(down)) {
        deltaY = 1 * speed;
        shape.move(0, deltaY * dt);
    }
}

float Paddle::getHitForce() {
    return hitForce;
}

float Paddle::getVelocityTransfer() {
    return velocityTransfer;
}

float Paddle::getDeltaY() {
    return deltaY;
}

COLLISION_DIRECTION Paddle::checkScreenCollision(sf::RenderWindow & window) {
    COLLISION_DIRECTION collision;
    collision = collidedWithScreenBoundary(window);
    if(collision != NO_COLLISION) setToScreenBoundary(collision, window);

    return collision;
}
