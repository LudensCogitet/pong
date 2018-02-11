#include "./Ball.h"

Ball::Ball(float xPos,
           float yPos,
           float width,
           float height,
           float newInitSpeed,
           float newDrag,
           sf::Color Color): Solid(xPos, yPos, width, height, Color) {
               drag = newDrag;
               initSpeed = newInitSpeed;
               initX = xPos;
               initY = yPos;

               reset();
           }

Ball::~Ball() {}

void Ball::reset() {
    shape.setPosition(initX, initY);

    if(rand() % 2 == 1) {
        moveDelta.x = initSpeed;
    } else {
        moveDelta.x = -initSpeed;
    }

    if(rand() % 2 == 1) {
        moveDelta.y = initSpeed;
    } else {
        moveDelta.y = -initSpeed;
    }
}

void Ball::update(float dt) {
    moveDelta.x -= (moveDelta.x * drag) * dt;
    moveDelta.y -= (moveDelta.y * drag) * dt;

    shape.move(moveDelta * dt);
}

void Ball::setDelta(float dx, float dy) {
    moveDelta = sf::Vector2f(dx, dy);
}

void Ball::changeDelta(float dx, float dy) {
    moveDelta.x += dx;
    moveDelta.y += dy;
}

COLLISION_DIRECTION Ball::checkScreenCollision(sf::RenderWindow & window) {
    COLLISION_DIRECTION collision = collidedWithScreenBoundary(window);
    if(collision != NO_COLLISION) {
        setToScreenBoundary(collision, window);

        if(collision == TOP || collision == BOTTOM)
            moveDelta.y = -moveDelta.y;

        if(collision == LEFT || collision == RIGHT) {
            reset();
        }
    }

    return collision;
}

COLLISION_DIRECTION Ball::checkPaddleCollision(Paddle & paddle) {
    COLLISION_DIRECTION collision = collidedWithSolid(paddle);

    if(collision != NO_COLLISION) {
        setToSolidBoundary(collision, paddle);

        if(collision == RIGHT)  moveDelta.x = paddle.getHitForce();
        if(collision == LEFT)   moveDelta.x = -paddle.getHitForce();

        if(collision == TOP || collision == BOTTOM)
            moveDelta.y = -moveDelta.y;

        moveDelta.y += paddle.getDeltaY() * paddle.getVelocityTransfer();
    }
    return collision;
}
