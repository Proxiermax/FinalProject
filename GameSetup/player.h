#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Player
{
public:
    Player(const sf::Texture& texture, int widthWindow, int heightWindow);
    void move(int widthWindow, int heightWindow, float deltaTime);
    void draw(sf::RenderWindow& window);
    void resetPosition(int widthWindow, int heightWindow);
    const sf::RectangleShape& getPlayerShape() const;
    const sf::Sprite& getPlayerSprite() const;
private:
    sf::RectangleShape playerShape;
    sf::Sprite playerSprite;
    sf::IntRect frameRect;
    float playerSpeed = 500.0f;
    float playerScale = 50.0f;
    int currentFrame;
    int frameCounter;
    const int switchFrame;
    const int numFrames;
    void playerAnimation();
};