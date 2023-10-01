#include "player.h"

Player::Player(const sf::Texture& texture, int widthWindow, int heightWindow)
    : currentFrame(0), frameCounter(0), switchFrame(100), numFrames(3)
{
    playerShape.setSize(sf::Vector2f(playerScale, playerScale));
    playerShape.setFillColor(sf::Color::Transparent);
    playerShape.setOrigin(playerShape.getGlobalBounds().width / 2,
        playerShape.getGlobalBounds().height / 2);
    playerShape.setPosition(widthWindow / 2, heightWindow / 2);

    playerSprite.setTexture(texture);
    const int frameWidth = 60;
    const int frameHeight = 77.5;
    frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    playerSprite.setTextureRect(frameRect);
    playerSprite.setScale(1.0f, 1.0f);
    playerSprite.setOrigin(frameWidth / 2, frameHeight / 2);
    playerSprite.setPosition(widthWindow / 2, heightWindow / 2);
}

void Player::move(int widthWindow, int heightWindow, float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);
    bool moveActivated = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerShape.getPosition().y > 0) {
        frameRect.top = 232.5;
        movement.y -= playerSpeed * deltaTime;
        moveActivated = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerShape.getPosition().x > 0) {
        frameRect.top = 77.5;
        movement.x -= playerSpeed * deltaTime;
        moveActivated = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerShape.getPosition().y < heightWindow) {
        frameRect.top = 0;
        movement.y += playerSpeed * deltaTime;
        moveActivated = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerShape.getPosition().x < widthWindow) {
        frameRect.top = 155;
        movement.x += playerSpeed * deltaTime;
        moveActivated = true;
    }

    if (moveActivated) {
        playerAnimation();
    }
    else {
        currentFrame = 1;
        frameRect.left = currentFrame * frameRect.width;
    }

    playerShape.move(movement);
    playerSprite.move(movement);
    playerSprite.setTextureRect(frameRect);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(playerShape);
    window.draw(playerSprite);
}

void Player::resetPosition(int widthWindow, int heightWindow)
{
    playerShape.setPosition(widthWindow / 2, heightWindow / 2);
    playerSprite.setPosition(widthWindow / 2, heightWindow / 2);
}

const sf::RectangleShape& Player::getPlayerShape() const
{
    return playerShape;
}

const sf::Sprite& Player::getPlayerSprite() const
{
    return playerSprite;
}

void Player::playerAnimation() {
    if (playerShape.getPosition().x != 0 || playerShape.getPosition().y != 0) {
        frameCounter += 1;
        if (frameCounter >= switchFrame) {
            frameCounter = 0;
            currentFrame += 1;
            if (currentFrame >= numFrames)
                currentFrame = 0;
            frameRect.left = currentFrame * frameRect.width;
        }
    }
}