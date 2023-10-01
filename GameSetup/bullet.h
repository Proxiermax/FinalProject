#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bullet {
public:
    Bullet(const sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f target,
        int widthWindow, int heightWindow);
    void move(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool outsideWindow(int widthWindow, int heightWindow);
    const sf::RectangleShape& getBulletShape() const;
private:
    sf::RectangleShape bulletShape;
    sf::Sprite bulletSprite;
    sf::IntRect frameRect;
    sf::Vector2f direction;
    float bulletSpeed = 5000.0f;
    float bulletScale = 36.0f;
};