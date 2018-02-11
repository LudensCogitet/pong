#ifndef GUITEXT_H
#define GUITEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
class GuiText {
    public:
        GuiText(std::string startText,
                float startX,
                float startY,
                float newScreenWidth,
                float newScreenHeight,
                float characterSize,
                sf::Color newColor,
                sf::Font * newFont);
        ~GuiText();

        void setText(std::string newText);
        void setPosition(float newX, float newY);
        void setScreenDimensions(float newWidth, float newHeight);
        void setSize(float characterSize);
        void setColor(sf::Color newColor);
        void setFont(sf::Font * newFont);

        std::string getText();
        sf::Text getDrawable();

    private:
        std::string text;
        sf::Text drawable;

        float x;
        float y;
        float screenWidth;
        float screenHeight;
};

#endif
