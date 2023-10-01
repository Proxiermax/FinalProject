#include "enemy.h"
#include <iostream>
#include <math.h>

Enemy::Enemy(const sf::Texture& texture, sf::Vector2f spawnPosition)
    //: currentFrame(0), frameCounter(0), switchFrame(100), numFrames(3)
{
    enemyShape.setSize(sf::Vector2f(enemyScale, enemyScale));
    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setOrigin(enemyShape.getSize().x / 2, enemyShape.getSize().y / 2);
    enemyShape.setPosition(spawnPosition);

    enemySprite.setTexture(texture);
    const int frameWidth = 60;
    const int frameHeight = 77.5;

    int enemyRandom = rand() % 5;
    switch (enemyRandom) {
    case 0:
        frameRect = sf::IntRect(0, 310, frameWidth, frameHeight);
        break;
    case 1:
        frameRect = sf::IntRect(180, 310, frameWidth, frameHeight);
        break;
    case 2:
        frameRect = sf::IntRect(360, 310, frameWidth, frameHeight);
        break;
    case 3:
        frameRect = sf::IntRect(540, 310, frameWidth, frameHeight);
        break;
    case 4:
        frameRect = sf::IntRect(360, 0, frameWidth, frameHeight);
        break;
    }
    //frameRect = sf::IntRect(0, 310, frameWidth, frameHeight);
    //frameRect = sf::IntRect(180, 310, frameWidth, frameHeight);
    //frameRect = sf::IntRect(360, 310, frameWidth, frameHeight);
    //frameRect = sf::IntRect(540, 310, frameWidth, frameHeight);
    //frameRect = sf::IntRect(360, 0, frameWidth, frameHeight);
    enemySprite.setTextureRect(frameRect);
    enemySprite.setScale(1.0f, 1.0f);
    enemySprite.setOrigin(frameWidth / 2, frameHeight / 2);
    enemySprite.setPosition(spawnPosition);
}

void Enemy::move(sf::Vector2f target, int widthWindow, int heightWindow, float deltaTime) {
    sf::Vector2f direction = target - enemyShape.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;
    enemyShape.move(direction * enemySpeed * deltaTime);
    enemySprite.move(direction * enemySpeed * deltaTime);

    int currentFrame = 0;
    int frameCounter = 0;
    const int switchFrame = 100;
    const int numFrames = 3;

    frameCounter += 1;
    if (frameCounter >= switchFrame) {
        frameCounter = 0;
        currentFrame += 1;
        if (currentFrame >= numFrames)
            currentFrame = 0;
        frameRect.left = currentFrame * frameRect.width;

        enemySprite.setTextureRect(frameRect);
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemyShape);
    window.draw(enemySprite);
}

bool Enemy::enemyAssault(sf::FloatRect target) {
    return enemyShape.getGlobalBounds().intersects(target);
}

const sf::RectangleShape& Enemy::getEnemyShape() const
{
    return enemyShape;
}

//const sf::Sprite& Enemy::getEnemySprite() const
//{
//    return enemySprite;
//}

void Enemy::enemyAnimation()
{
    int currentFrame = 0;
    int frameCounter = 0;
    const int switchFrame = 100;
    const int numFrames = 3;

    frameCounter += 1;
    if (frameCounter >= switchFrame) {
        frameCounter = 0;
        currentFrame += 1;
        if (currentFrame >= numFrames)
            currentFrame = 0;
        frameRect.left = currentFrame * frameRect.width;

        //enemySprite.setTextureRect(frameRect);
    }

    //enemySprite.setTextureRect(frameRect);
}