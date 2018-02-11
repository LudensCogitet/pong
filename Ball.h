#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "./Solid.h"
#include "./Paddle.h"

class Ball : public Solid {
    public:
        Ball(float xPos,
             float yPos,
             float width,
             float height,
             float newInitSpeed,
             float newDrag,
             sf::Color Color);
        ~Ball();

        void update(float dt);
        void reset();
        void setDelta(float dx, float dy);
        void changeDelta(float dx, float dy);
        COLLISION_DIRECTION checkScreenCollision(sf::RenderWindow & window);
        COLLISION_DIRECTION checkPaddleCollision(Paddle & paddle);

    private:
        float drag;
        float initSpeed;
        float initX;
        float initY;
        sf::Vector2f moveDelta;
};
#endif
