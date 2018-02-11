#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "./config.h"
#include "./Solid.h"
#include "./Paddle.h"
#include "./Ball.h"
#include "./GuiText.h"

configMap config;
sf::RenderWindow window;
sf::Font * scoreBoardFont = nullptr;

Paddle  * leftPaddle = nullptr;
Paddle  * rightPaddle = nullptr;
Ball    * ball = nullptr;

int leftPaddleScore;
GuiText * leftPaddleScoreBoard = nullptr;

int rightPaddleScore;
GuiText * rightPaddleScoreBoard = nullptr;

void oneTimeInit() {
    config = loadConfig("./config");

    scoreBoardFont = new sf::Font();
    scoreBoardFont ->loadFromFile("./ARCADECLASSIC.TTF");

    float scoreBoardCharacterSize = std::stof(config["scoreBoardFontSize"]);

    leftPaddleScoreBoard = new GuiText("0",
                                       std::stof(config["leftPaddleScoreBoardX"]),
                                       std::stof(config["scoreBoardY"]),
                                       0,
                                       0,
                                       scoreBoardCharacterSize,
                                       sf::Color::Magenta,
                                       scoreBoardFont);

                                       std::cout << "LOADED..." << std::endl;

    rightPaddleScoreBoard = new GuiText("0",
                                        std::stof(config["rightPaddleScoreBoardX"]),
                                        std::stof(config["scoreBoardY"]),
                                        0,
                                        0,
                                        scoreBoardCharacterSize,
                                        sf::Color::Blue,
                                        scoreBoardFont);
}

void init() {
    config = loadConfig("./config");

    window.create(sf::VideoMode(std::stof(config["screenWidth"]), std::stof(config["screenHeight"])), "Pong!", sf::Style::Default);

    float paddleSpeedSlow     = std::stof(config["paddleSpeedSlow"]);
    float paddleSpeedMedium   = std::stof(config["paddleSpeedMedium"]);
    float paddleSpeedFast     = std::stof(config["paddleSpeedFast"]);

    float yVelocityTransfer = std::stof(config["yVelocityTransfer"]);

    float ballSize        = std::stof(config["ballSize"]);
    float ballDrag        = std::stof(config["ballDrag"]);
    float initBallSpeed   = std::stof(config["initBallSpeed"]);
    float ballHitForce    = std::stof(config["ballHitForce"]);

    std::srand(std::time(0));

    rightPaddleScore = 0;
    leftPaddleScore = 0;

    sf::Vector2u windowSize = window.getSize();

    leftPaddleScoreBoard ->setText(std::to_string(leftPaddleScore));
    leftPaddleScoreBoard ->setScreenDimensions(windowSize.x, windowSize.y);
    leftPaddleScoreBoard ->setPosition(std::stof(config["leftPaddleScoreBoardX"]),
                                       std::stof(config["scoreBoardY"]));

    rightPaddleScoreBoard ->setText(std::to_string(rightPaddleScore));
    rightPaddleScoreBoard ->setScreenDimensions(windowSize.x, windowSize.y);
    rightPaddleScoreBoard ->setPosition(std::stof(config["rightPaddleScoreBoardX"]),
                                        std::stof(config["scoreBoardY"]));

    delete leftPaddle;
    delete rightPaddle;

    float paddleWidth = std::stof(config["paddleWidth"]);
    float paddleHeight = std::stof(config["paddleHeight"]);

    leftPaddle = new Paddle(std::stof(config["leftPaddleX"]),
                            std::stof(config["leftPaddleY"]),
                            paddleWidth,
                            paddleHeight,
                            paddleSpeedSlow,
                            paddleSpeedMedium,
                            paddleSpeedFast,
                            ballHitForce,
                            yVelocityTransfer,
                            sf::Keyboard::W,
                            sf::Keyboard::S,
                            sf::Keyboard::A,
                            sf::Keyboard::D,
                            sf::Color::Magenta);

    rightPaddle = new Paddle(std::stof(config["rightPaddleX"]),
                             std::stof(config["rightPaddleY"]),
                             paddleWidth,
                             paddleHeight,
                             paddleSpeedSlow,
                             paddleSpeedMedium,
                             paddleSpeedFast,
                             ballHitForce,
                             yVelocityTransfer,
                             sf::Keyboard::Up,
                             sf::Keyboard::Down,
                             sf::Keyboard::Left,
                             sf::Keyboard::Right,
                             sf::Color::Blue);

     delete ball;

     ball = new Ball(windowSize.x / 2,
                     windowSize.y / 2,
                     ballSize,
                     ballSize,
                     initBallSpeed,
                     ballDrag,
                     sf::Color::Green);
}

int main() {
    oneTimeInit();
    init();

    sf::Clock timer;
    sf::Time deltaTime;
    sf::Event event;

    bool done = false;
    while(!done) {
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    done = true;
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape) done = true;
                    else if(event.key.code == sf::Keyboard::F5) init();
                    break;
            }
        }

        if(done) continue;

        float timeAsSeconds = deltaTime.asSeconds();

        COLLISION_DIRECTION collision;

        ball        ->update(timeAsSeconds);
        leftPaddle  ->update(timeAsSeconds);
        rightPaddle ->update(timeAsSeconds);

        leftPaddle  ->checkScreenCollision(window);
        rightPaddle ->checkScreenCollision(window);

        collision = ball->checkScreenCollision(window);

        if(collision == LEFT) {
            rightPaddleScore++;
            rightPaddleScoreBoard ->setText(std::to_string(rightPaddleScore));
        }
        if(collision == RIGHT) {
            leftPaddleScore++;
            leftPaddleScoreBoard ->setText(std::to_string(leftPaddleScore));
        }

        ball->checkPaddleCollision(*leftPaddle);
        ball->checkPaddleCollision(*rightPaddle);

        window.clear(sf::Color::Black);
        window.draw(leftPaddle->getShape());
        window.draw(rightPaddle->getShape());

        window.draw(leftPaddleScoreBoard ->getDrawable());
        window.draw(rightPaddleScoreBoard ->getDrawable());
        window.draw(ball->getShape());
        window.display();

        deltaTime = timer.restart();
    }

    delete leftPaddle;
    delete leftPaddleScoreBoard;

    delete rightPaddle;
    delete rightPaddleScoreBoard;

    delete ball;

    delete scoreBoardFont;

    return 0;
}
