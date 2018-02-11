#include "./GuiText.h"

void GuiText::setText(std::string newText) {
    text = newText;
    drawable.setString(text);

    sf::FloatRect boundingRect = drawable.getGlobalBounds();
    drawable.setOrigin(boundingRect.width / 2, boundingRect.height / 2);
}

void GuiText::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    drawable.setPosition(screenWidth * x, screenHeight * y);
}

void GuiText::setScreenDimensions(float newWidth, float newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
}

void GuiText::setSize(float newSize) {
    drawable.setCharacterSize(newSize);
}

void GuiText::setColor(sf::Color newColor) {
    drawable.setFillColor(newColor);
}

void GuiText::setFont(sf::Font * newFont) {
    drawable.setFont(*newFont);
}

sf::Text GuiText::getDrawable() {
    return drawable;
}

std::string GuiText::getText() {
    return text;
}

GuiText::GuiText(std::string startText, float startX, float startY, float newScreenWidth, float newScreenHeight, float characterSize, sf::Color newColor, sf::Font * newFont) {
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    setSize(characterSize);
    setFont(newFont);
    setColor(newColor);
    setText(startText);
    setPosition(startX, startY);
}

GuiText::~GuiText() {}
