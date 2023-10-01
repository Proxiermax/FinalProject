#include "bullet.h"
#include <math.h>

Bullet::Bullet(const sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f target,
    int widthWindow, int heightWindow) {
    bulletShape.setSize(sf::Vector2f(bulletScale, bulletScale));
    bulletShape.setFillColor(sf::Color::Transparent);
    bulletShape.setOrigin(bulletShape.getSize().x / 2, bulletShape.getSize().y / 2);
    bulletShape.setPosition(startPosition);

    bulletSprite.setTexture(texture);
    const int frameWidth = 120;
    const int frameHeight = 120;
    frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    bulletSprite.setTextureRect(frameRect);
    bulletSprite.setScale(0.25f, 0.25f);
    bulletSprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
    bulletSprite.setPosition(startPosition);

    direction = target - startPosition;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;
}

void Bullet::move(float deltaTime) {
    bulletShape.move(bulletSpeed * direction * deltaTime);
    bulletSprite.move(bulletSpeed * direction * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(bulletShape);
    window.draw(bulletSprite);
}

bool Bullet::outsideWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    sf::Vector2f position = bulletShape.getPosition();
    return (position.x < 0 || position.x > WINDOW_WIDTH || position.y < 0 || position.y > WINDOW_HEIGHT);
}

const sf::RectangleShape& Bullet::getBulletShape() const
{
    return bulletShape;
}