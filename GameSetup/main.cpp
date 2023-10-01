#include "game.h"
#include <iostream>

int main() {
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("Textures/rayquaza.jpg")) {
        //handle error
        return -1;
    }
    sf::Texture inputTexture;
    if (!inputTexture.loadFromFile("Textures/forest.jpg")) {
        //handle error
        return -1;
    }
    sf::Texture inGameTexture;
    if (!inGameTexture.loadFromFile("Textures/grass.jpg")) {
        //handle error
        return -1;
    }
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Textures/Pokemon_Unit.png")) {
        //handle error
        return -1;
    }
    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("Textures/Pokemon_Ball.png")) {
        //handle error
        return -1;
    }
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("Textures/Pokemon_Unit.png")) {
        //handle error
        return -1;
    }
    Game game;
    game.run();
    return 0;
}