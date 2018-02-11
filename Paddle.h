#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "./Solid.h"

class Paddle : public Solid {
    public:
        Paddle(float xPos,
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
               sf::Color color);
        ~Paddle();

        float                   getHitForce();
        float                   getVelocityTransfer();
        float                   getDeltaY();
        void                    update(float delta);
        COLLISION_DIRECTION     checkScreenCollision(sf::RenderWindow & window);

    private:
        float speed;

        float slowSpeed;
        float mediumSpeed;
        float fastSpeed;

        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;

        float deltaY;
        float hitForce;
        float velocityTransfer;
};
#endif
