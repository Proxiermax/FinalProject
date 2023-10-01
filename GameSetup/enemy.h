#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Enemy {
public:
    Enemy(const sf::Texture& texture, sf::Vector2f spawnPosition);
    void move(sf::Vector2f target, int widthWindow, int heightWindow, float deltaTime);
    void draw(sf::RenderWindow& window);
    bool enemyAssault(sf::FloatRect target);
    const sf::RectangleShape& getEnemyShape() const;
    //const sf::Sprite& getEnemySprite() const;
private:
    sf::RectangleShape enemyShape;
    sf::Sprite enemySprite;
    sf::IntRect frameRect;
    float enemySpeed = 100.0f;
    float enemyScale = 50.0f;
    //int currentFrame;
    //int frameCounter;
    //const int switchFrame;
    //const int numFrames;
    void enemyAnimation();
};