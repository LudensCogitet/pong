#ifndef SOLID_H
#define SOLID_H

#include <SFML/Graphics.hpp>

enum COLLISION_DIRECTION { NO_COLLISION, LEFT, RIGHT, TOP, BOTTOM, COLLISION };

class Solid {
    public:
        Solid(float xPos,
              float yPos,
              float width,
              float height,
              sf::Color color);

        ~Solid();

        COLLISION_DIRECTION         collidedWithScreenBoundary(sf::RenderWindow & window);
        COLLISION_DIRECTION         collidedWithSolid(Solid & otherSolid);
        void                        setToScreenBoundary(COLLISION_DIRECTION collisionDir, sf::RenderWindow & window);
        void                        setToSolidBoundary(COLLISION_DIRECTION collisionDir, Solid & other);
        sf::RectangleShape &        getShape();

    protected:
        sf::RectangleShape shape;
};
#endif
